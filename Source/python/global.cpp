#include "global.hpp"
#include "../cmAddDefinitionsCommand.h"

using namespace cm::py::global;

PyObject*
add_definitions( PyObject*, PyObject* args ) {

	PyObject* definitions;

	if( !PyArg_ParseTuple(args, "O!is", &PyList_Type, &definitions) )
		return nullptr;

	auto cmdArgs = [&]() {

		auto strArgs = cm::arg_type{};

		auto listCount = PyList_Size( definitions );

		for( auto i = 0; i < listCount; ++i ) {
			// grab the string object from the next element of the list
			auto listItem = PyList_GetItem( definitions, i); // Can't fail
			// make it a string
			strArgs.emplace_back( PyUnicode_AsUTF8( listItem ) );
		}

		return strArgs;
	}();

	auto cmd = cmAddDefinitionsCommand{};
	cmExecutionStatus status;
	/*auto success =*/
	cmd.InitialPass( cmdArgs, status );

	return nullptr;
}








//project_env[ 'VERSION_MAJOR' ] = 0
//project_env[ 'VERSION_MINOR' ] = 1



