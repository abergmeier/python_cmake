#include "include.hpp"
#include "set_variable.hpp"
#include "project.hpp"
#include "library.hpp"
#include "executable.hpp"
#include "target.hpp"
#include "makefile.hpp"

namespace cm {
	namespace py {
		namespace module {
			PyMethodDef METHODS[] = {

				{ "project"   , create_project    , METH_VARARGS, "Create a new project."},
				{ "include"   , include_cmake_file, METH_VARARGS, "Include a CMake script file."},
				{ "set"       , set_variable      , METH_VARARGS, "Set a variable."},
				{ "library"   , reinterpret_cast<PyCFunction>(add_library), METH_VARARGS | METH_KEYWORDS, "Add a library."},
				{ "executable", add_executable    , METH_VARARGS, "Add a executable."},

				{ nullptr, nullptr, 0, nullptr } // Sentinel
			};

			auto INTERFACE = PyModuleDef{
				PyModuleDef_HEAD_INIT,
				"cmake",
				nullptr,
				-1,
				METHODS,
				nullptr,
				nullptr,
				nullptr,
				nullptr
			};
		} // namespace module
	} // namespace py
} // namespace cm

namespace {

	PyObject* init_makefile(_typeobject* arg1, PyObject* arg2, PyObject* arg3) {
		auto obj = PyType_GenericNew( arg1, arg2, arg3 );
		// We have to construct allocated object
		new ( &static_cast<cm::py::Makefile*>(obj)->file ) cm::py::Makefile();
		return obj;
	}

	void destroy_makefile( PyObject* object ) {
		static_cast<cm::py::Makefile*>( object )->file.~cmMakefile();
	}

	auto Makefile_type = PyTypeObject{
			PyVarObject_HEAD_INIT(NULL, 0)
			"cmake.Makefile", // tp_name For printing, in format "<module>.<name>"
			sizeof(cm::py::Makefile), // tp_basicsize
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
			"CMake Makefile objects", // tp_doc Documentation string
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
			init_makefile , // tp_new
			nullptr , // tp_free
			nullptr , // tp_is_gc
			nullptr , // tp_bases
			nullptr , // tp_mro
			nullptr , // tp_cache
			nullptr , // tp_subclasses
			nullptr , // tp_weaklist
			destroy_makefile , // tp_del

			1 // tp_version_tag
		};

}


PyMODINIT_FUNC
PyInit_cmake() {
#if 0
	if( PyType_Ready(&NoddyType) < 0 )
		return NULL;
#endif

	auto module = PyModule_Create( &cm::py::module::INTERFACE );

	if( !module )
		return nullptr;

	auto makefile = PyObject_New( cm::py::Makefile, &Makefile_type );

	assert( PyModule_AddObject( module, "makefile", makefile) == 0 );
#if 0
	Py_INCREF(&NoddyType);
	PyModule_AddObject(m, "Noddy", (PyObject *)&NoddyType);
#endif
	return module;
}

