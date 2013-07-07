#include "target.hpp"
#include "../cmTargetCompileDefinitionsCommand.h"
#include "../cmTargetCompileOptionsCommand.h"
#include "../cmTargetDepend.h"
#include "../cmTargetExport.h"
#include "../cmTargetIncludeDirectoriesCommand.h"
#include "../cmTargetLinkLibrariesCommand.h"

using namespace cm::py::target;

PyObject*
compile_definitions( PyObject* self, PyObject* args ) {
#if 0
	const char* name;
	PyObject* languageList;

	if( !PyArg_ParseTuple(args, "sO!is", &name, &PyList_Type, &languageList) )
		return nullptr;

	auto cmdArgs = [&]() {

		auto strArgs = cm::arg_type{{
			name
		}};

		auto listCount = PyList_Size( languageList );

		for( auto i = 0; i < listCount; ++i ) {
			// grab the string object from the next element of the list
			auto listItem = PyList_GetItem( languageList, i); // Can't fail
			// make it a string
			strArgs.emplace_back( PyUnicode_AsUTF8( listItem ) );
		}

		return strArgs;
	}();

	auto cmd = cmProjectCommand();
	cmExecutionStatus status;
	bool success = cmd.InitialPass( cmdArgs, status );

	return Py_BuildValue("i", success);
#endif
	return nullptr;
}

PyObject*
compile_options( PyObject* self, PyObject* args ) {
	return nullptr;
}

PyObject*
depend( PyObject* self, PyObject* args ) {
	return nullptr;
}

PyObject*
include_directories( PyObject* self, PyObject* args ) {
	return nullptr;
}

PyObject*
link_libraries( PyObject* self, PyObject* args ) {
	return nullptr;
}

PyObject*
set_target_libraries( PyObject* self, PyObject* args ) {
	return nullptr;
}

#if 0
	{ "compile_definitions", target::compile_definitions, METH_VARARGS, "" },
	{ "compile_options"    , target::compile_options    , METH_VARARGS, "" },
	{ "depend"             , target::depend             , METH_VARARGS, "" },
	{ "include_directories", target::include_directories, METH_VARARGS, "" },
	{ "link_libraries"     , target::link_libraries     , METH_VARARGS, "" },
	{ "set_target_properties", target::set_target_properties, METH_VARARGS, "" },
#endif



