#include "target.hpp"
#include "makefile.hpp"
#include "../cmTargetCompileDefinitionsCommand.h"
#include "../cmTargetCompileOptionsCommand.h"
#include "../cmTargetDepend.h"
#include "../cmTargetExport.h"
#include "../cmTargetIncludeDirectoriesCommand.h"
#include "../cmTargetLinkLibrariesCommand.h"

using namespace cm::py::target;

PyObject*
cm::py::target::compile_definitions( PyObject* self, PyObject* args ) {
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
cm::py::target::compile_options( PyObject* self, PyObject* args ) {
	return nullptr;
}

PyObject*
cm::py::target::depend( PyObject* self, PyObject* args ) {
	return nullptr;
}

PyObject*
cm::py::target::include_directories( PyObject* self, PyObject* args ) {
	return nullptr;
}

PyObject*
cm::py::target::link_libraries( PyObject* self, PyObject* args, PyObject* keywords ) {
	return nullptr;
}

PyObject*
cm::py::target::set_properties( PyObject* self, PyObject* args ) {
	return nullptr;
}

namespace {
	PyMethodDef METHODS[] = {
		{ "compile_definitions", compile_definitions, METH_VARARGS, "Add compile definitions to Target"     },
		{ "compile_options"    , compile_options    , METH_VARARGS, "Add compile options to Target"         },
		{ "depend"             , depend             , METH_VARARGS, "Add dependencies for Target"           },
		{ "include_directories", include_directories, METH_VARARGS, "Add include directories for Target"    },
		{ "link_libraries"     , reinterpret_cast<PyCFunction>(link_libraries) , METH_VARARGS, "Link additional libraries with Target" },
		{ "set_properties"     , set_properties     , METH_VARARGS, "Add properties to Target"              }
	};

	auto Library_type = PyTypeObject{
		PyVarObject_HEAD_INIT(NULL, 0)
		"cmake.Target", // tp_name For printing, in format "<module>.<name>"
		sizeof(Target), // tp_basicsize
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
		Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, // tp_flags
		"CMake Target objects", // tp_doc Documentation string
		nullptr , // tp_traverse
		nullptr , // tp_clear
		nullptr , // tp_richcompare
		0       , // tp_weaklistoffset
		nullptr , // tp_iter
		nullptr , // tp_iternext
		METHODS , // tp_methods
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
} // namespace
std::vector<std::string>
cm::py::to_vector( PyObject* list ) {

	auto result = std::vector<std::string>{};

	auto listCount = PyList_Size( list );

	// Prevent multiple allocations
	result.reserve( result.size() + listCount );

	for( Py_ssize_t i = 0; i < listCount; ++i ) {
		// grab the string object from the next element of the list
		auto listItem = PyList_GetItem( list, i); // Can't fail
		// make it a string
		result.emplace_back( PyUnicode_AsUTF8( listItem ) );
	}

	return std::move( result );
}

void
Target::init( PyObject& cmake, const cm::arg_type& args ) {
	cmExecutionStatus status;

	auto& makefile = [&]() -> cmMakefile& {
		auto makefileWrapper = PyObject_GetAttr( &cmake, PyUnicode_FromString("makefile") );
		return static_cast<cm::py::Makefile*>(makefileWrapper)->file;
	}();

	if( _command.IsDiscouraged() )
		return; // Ignore for now

	_command.SetMakefile( &makefile );

	// We are not expanding input for now
	// bool success = _command.InvokeInitialPass( args, status );

	auto success = _command.InitialPass( args, status );
	if( _command.HasFinalPass() )
		_command.FinalPass();
}


