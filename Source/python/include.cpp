#include "include.hpp"
#include "../cmIncludeCommand.h"

using namespace cm::py;

PyObject*
include_cmake_file( PyObject*, PyObject* args ) {

	PyObject* optional;
	PyObject* no_scope;
	const char* result_variable;

	if( !PyArg_ParseTuple( args, "OOz",
	                       &optional,
	                       &no_scope,
	                       &result_variable ) )
		return nullptr;

	auto cmdArgs = [&]() {

		auto stringArgs = cm::arg_type{};

		if( PyObject_IsTrue( optional ) )
			stringArgs.emplace_back( "OPTIONAL" );

		if( PyObject_IsTrue( no_scope ) )
			stringArgs.emplace_back( "NO_POLICY_SCOPE" );
	
		if( result_variable != nullptr ) {
			stringArgs.emplace_back( "RESULT_VARIABLE" );
			stringArgs.emplace_back( result_variable );
		}
	
		return stringArgs;
	}();

	auto cmd = cmIncludeCommand{};
	cmExecutionStatus status;
	cmd.InitialPass( cmdArgs, status );
	return nullptr;
}

