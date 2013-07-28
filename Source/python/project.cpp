#include "project.hpp"
#include "../cmProjectCommand.h"

using namespace cm::py;

namespace {
	struct Project : public PyObject {
	};

	auto Project_type = PyTypeObject{
		PyVarObject_HEAD_INIT(NULL, 0)
		"cmake.Project", // tp_name For printing, in format "<module>.<name>"
		sizeof(Project), // tp_basicsize
		0                 , // tp_itemsize /* For allocation */
		nullptr           , // tp_dealloc
		nullptr           , // tp_print
		nullptr           , // tp_getattr
		nullptr           , // tp_setattr
		nullptr           , // tp_reserved formerly known as tp_compare
		nullptr           , // tp_repr
		nullptr           , // tp_as_number
		nullptr           , // tp_as_sequence
		nullptr           , // tp_as_mapping
		nullptr           , // tp_hash
		nullptr           , // tp_call
		nullptr           , // tp_str
		nullptr           , // tp_getattro
		nullptr           , // tp_setattro
		nullptr           , // tp_as_buffer
		Py_TPFLAGS_DEFAULT, // tp_flags
		"CMake Project objects", // tp_doc Documentation string
		nullptr , // tp_traverse
		nullptr , // tp_clear
		nullptr , // tp_richcompare
		0       , // tp_weaklistoffset
		nullptr , // tp_iter
		nullptr , // tp_iternext
		nullptr , // tp_methods
		nullptr , // tp_members
		nullptr , // tp_getset
		nullptr , // tp_base;
		nullptr , // tp_dict
		nullptr , // tp_descr_get
		nullptr , // tp_descr_set
		0       , // tp_dictoffset
		nullptr , // tp_init
		nullptr , // tp_alloc
		nullptr , // tp_new
		nullptr , // tp_free
		nullptr , // tp_is_gc
		nullptr , // tp_bases
		nullptr , // tp_mro
		nullptr , // tp_cache
		nullptr , // tp_subclasses
		nullptr , // tp_weaklist
		nullptr , // tp_del

		1 // tp_version_tag
	};
}

PyObject*
cm::py::create_project( PyObject*, PyObject* args ) {

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

	if( success )
		return PyObject_New( Project, &Project_type );
	else
		return nullptr;
}







//project_env[ 'VERSION_MAJOR' ] = 0
//project_env[ 'VERSION_MINOR' ] = 1



