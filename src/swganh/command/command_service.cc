
#include "swganh/command/command_service.h"

#include <cctype>

#include "anh/app/kernel_interface.h"

#include <cppconn/exception.h>
#include <cppconn/connection.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/sqlstring.h>
#include <glog/logging.h>

#include "anh/crc.h"
#include "anh/database/database_manager_interface.h"
#include "anh/service/service_manager.h"

#include "swganh/messages/controllers/command_queue_enqueue.h"
#include "swganh/messages/controllers/command_queue_remove.h"

#include "swganh/object/object.h"
#include "swganh/object/object_controller.h"

#include "python_command.h"
#include "swganh/simulation/simulation_service.h"

using namespace anh::app;
using namespace anh::service;
using namespace std;
using namespace swganh::command;
using namespace swganh::messages;
using namespace swganh::messages::controllers;
using namespace swganh::object;
using namespace swganh::scripting;
using namespace swganh::simulation;

CommandService::CommandService(KernelInterface* kernel)
: BaseService(kernel)
{}

ServiceDescription CommandService::GetServiceDescription()
{
    ServiceDescription service_description(
        "CommandService",
        "command",
        "0.1",
        "127.0.0.1", 
        0, 
        0, 
        0);

    return service_description;
}

void CommandService::AddCommandHandler(uint32_t command_crc, CommandHandler&& handler)
{
    handlers_[command_crc] = move(handler);
}

void CommandService::EnqueueCommand(
    uint64_t object_id, 
    CommandQueueEnqueue command)
{
    command_queues_[object_id].push(command);    
}

void CommandService::HandleCommandQueueEnqueue(
    const shared_ptr<ObjectController>& controller, 
    const ObjControllerMessage& message)
{
    CommandQueueEnqueue enqueue;
    enqueue.Deserialize(message.data);

    EnqueueCommand(controller->GetObject()->GetObjectId(), enqueue);
}

void CommandService::HandleCommandQueueRemove(
    const shared_ptr<ObjectController>& controller, 
    const ObjControllerMessage& message)
{}

void CommandService::ProcessNextCommand()
{
    for_each(
        begin(command_queues_),
        end(command_queues_),
        [this] (CommandQueueMap::value_type& object_commands)
    {
        CommandQueueEnqueue command; 
        if (!object_commands.second.try_pop(command))
        {
            return;
        }

        auto find_iter = handlers_.find(command.command_crc);

        if (find_iter != handlers_.end())
        {
            find_iter->second(
                object_commands.first,
                command.target_id,
                command.command_options);
        }
    });
}

void CommandService::onStart()
{
    LoadProperties();

    auto simulation_service = kernel()->GetServiceManager()
        ->GetService<SimulationService>("SimulationService");
    
    simulation_service->RegisterControllerHandler(0x00000116, [this] (
        const std::shared_ptr<ObjectController>& controller, 
        const swganh::messages::ObjControllerMessage& message) 
    {
        HandleCommandQueueEnqueue(controller, message);
    });
    
    simulation_service->RegisterControllerHandler(0x00000117, [this] (
        const std::shared_ptr<ObjectController>& controller, 
        const swganh::messages::ObjControllerMessage& message) 
    {
        HandleCommandQueueRemove(controller, message);
    });

    active().AsyncRepeated(boost::posix_time::milliseconds(0),
        [=] ()
    {
        ProcessNextCommand();
    });
}

void CommandService::LoadProperties()
{    
    try {
        auto db_manager = kernel()->GetDatabaseManager();

        auto conn = db_manager->getConnection("galaxy");
        auto statement = shared_ptr<sql::PreparedStatement>(conn->prepareStatement("CALL sp_LoadCommandProperties();"));

        auto result = shared_ptr<sql::ResultSet>(statement->executeQuery());
               
        while (result->next())
        {
            CommandProperties properties;
            
            properties.name = result->getString("name");

            string tmp = properties.name;
            transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
            properties.name_crc = anh::memcrc(tmp);

            properties.ability = result->getString("ability");
            properties.ability_crc = anh::memcrc(properties.ability);
            properties.deny_in_states = result->getUInt64("deny_in_states");
            properties.script_hook = result->getString("script_hook");
            properties.fail_script_hook = result->getString("fail_script_hook");
            properties.default_time = result->getUInt64("default_time");
            properties.command_group = result->getUInt("command_group");
            properties.max_range_to_target = result->getDouble("max_range_to_target");
            properties.add_to_combat_queue = result->getUInt("add_to_combat_queue");
            properties.health_cost = result->getUInt("health_cost");
            properties.health_cost_multiplier = result->getUInt("health_cost_multiplier");
            properties.action_cost = result->getUInt("action_cost");
            properties.action_cost_multiplier = result->getUInt("action_cost_multiplier");
            properties.mind_cost = result->getUInt("mind_cost");
            properties.mind_cost_multiplier = result->getUInt("mind_cost");
            properties.damage_multiplier = result->getDouble("damage_multiplier");
            properties.delay_multiplier = result->getDouble("delay_multiplier");
            properties.force_cost = result->getUInt("force_cost");
            properties.force_cost_multiplier = result->getUInt("force_cost_multiplier");
            properties.animation_crc = result->getUInt("animation_crc");
            properties.required_weapon_group = result->getUInt("required_weapon_group");
            properties.combat_spam = result->getString("combat_spam");
            properties.trail1 = result->getUInt("trail1");
            properties.trail2 = result->getUInt("trail2");
            properties.allow_in_posture = result->getUInt("allow_in_posture");
            properties.health_hit_chance = result->getDouble("health_hit_chance");
            properties.action_hit_chance = result->getDouble("action_hit_chance");
            properties.mind_hit_chance = result->getDouble("mind_hit_chance");
            properties.knockdown_hit_chance = result->getDouble("knockdown_chance");
            properties.dizzy_hit_chance = result->getDouble("dizzy_chance");
            properties.blind_chance = result->getDouble("blind_chance");
            properties.stun_chance = result->getDouble("stun_chance");
            properties.intimidate_chance = result->getDouble("intimidate_chance");
            properties.posture_down_chance = result->getDouble("posture_down_chance");
            properties.extended_range = result->getDouble("extended_range");
            properties.cone_angle = result->getDouble("cone_angle");
            properties.deny_in_locomotion = result->getUInt64("deny_in_locomotion");
            
            command_properties_map_.insert(make_pair(anh::memcrc(properties.name), move(properties)));

            RegisterCommandScript(properties);
        }

        DLOG(WARNING) << "Loaded (" << command_properties_map_.size() << ") Commands";
    }
    catch(sql::SQLException &e)
    {
        DLOG(ERROR) << "SQLException at " << __FILE__ << " (" << __LINE__ << ": " << __FUNCTION__ << ")";
        DLOG(ERROR) << "MySQL Error: (" << e.getErrorCode() << ": " << e.getSQLState() << ") " << e.what();
    }
}

void CommandService::RegisterCommandScript(const CommandProperties& properties)
{
    if (properties.script_hook.length() == 0)
    {
        return;
    }
    
    AddCommandHandler(properties.name_crc, PythonCommand(properties));
}
