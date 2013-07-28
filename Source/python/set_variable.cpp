#include "set_variable.hpp"
#include "../cmSetCommand.h"

using namespace cm::py;

PyObject*
cm::py::set_variable( PyObject*, PyObject* args ) {

	const char* name;
	const char* value;

	if( !PyArg_ParseTuple( args, "ss",
	                       &name,
	                       &value ) )
		return nullptr;

	auto cmdArgs = cm::arg_type{ name, value };

	auto cmd = cmSetCommand();
	cmExecutionStatus status;
	cmd.InitialPass( cmdArgs, status );
	return nullptr;
}

