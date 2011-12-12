
#include "python_script.h"

#include <cstdio>
#include <fstream>
#include <iterator>

#include <glog/logging.h>

#include <boost/python.hpp>
#include <Python.h>

using namespace boost::python;
using namespace std;
using namespace swganh::scripting;

PythonScript::PythonScript(const string& filename)
        : filename_(filename)
{
    ReadFileContents();

    Py_Initialize();
    
	try
    {
        object main = import("__main__");
        globals_ = main.attr("__dict__");

        globals_["context"] = dict();
    } 
    catch (error_already_set &) 
    {
        PyErr_Print();
    }
}

void PythonScript::Run()
{
	try
    {
#ifdef _DEBUG
        ReadFileContents();
#endif

        file_object_ = exec(filecontents_.c_str(), globals_, globals_);
    } 
    catch (error_already_set &) 
    {
        PyErr_Print();
    }   
}

void PythonScript::ReadFileContents()
{
    ifstream filestream(filename_);
    filestream >> noskipws;
    
    filecontents_ = string(
        (istreambuf_iterator<char>(filestream)),
        istreambuf_iterator<char>());
}
