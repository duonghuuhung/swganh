
#ifndef ANH_EVENT_DISPATCHER_H_
#define ANH_EVENT_DISPATCHER_H_

#include <cstdint>
#include <functional>
#include <memory>

#include <boost/asio/strand.hpp>

#include <tbb/concurrent_unordered_map.h>
#include <tbb/concurrent_vector.h>

#include "hash_string.h"

namespace boost {
    namespace asio {
        class io_service;
    }  // namespace asio

    template<class R>
    class unique_future;
}  // namespace boost

namespace anh {

    class EventInterface;

    typedef uint32_t CallbackId;
    typedef HashString EventType;
    typedef std::function<void (const std::shared_ptr<EventInterface>&)> EventHandlerCallback;

    class EventInterface
    {
    public:
        virtual ~EventInterface() = 0 {}

        virtual EventType Type() const = 0;
    };

    class BaseEvent : public EventInterface
    {
    public:
        explicit BaseEvent(EventType type);

        EventType Type() const;

    private:
        EventType type_;
    };
    
    class EventDispatcher
    {
    public:
        EventDispatcher(boost::asio::io_service& io_service);

        CallbackId Subscribe(EventType type, EventHandlerCallback callback);
        void Unsubscribe(EventType type, CallbackId identifier);

        boost::unique_future<std::shared_ptr<EventInterface>> Dispatch(const std::shared_ptr<EventInterface>& dispatch_event);

    private:
        struct EventHandler
        {
            EventHandler(CallbackId id, EventHandlerCallback callback)
                : id(id)
                , callback(callback)
            {}

            CallbackId id;
            EventHandlerCallback callback;
        };
        
        typedef tbb::concurrent_vector<EventHandler> EventHandlerList;
        
        typedef tbb::concurrent_unordered_map<
            EventType, 
            EventHandlerList
        > EventHandlerMap;

        CallbackId GenerateCallbackId();
        void InvokeCallbacks(const std::shared_ptr<EventInterface>& dispatch_event);
                
        EventHandlerMap event_handlers_;
        boost::asio::strand strand_;
    };

}  // namespace anh

#endif  // ANH_EVENT_DISPATCHER_H_
