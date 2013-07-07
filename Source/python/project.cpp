#include "project.hpp"
#include "../cmProjectCommand.h"

using namespace cm::py;

PyObject*
create_project( PyObject*, PyObject* args ) {

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
}







//project_env[ 'VERSION_MAJOR' ] = 0
//project_env[ 'VERSION_MINOR' ] = 1



