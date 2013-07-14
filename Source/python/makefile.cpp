#include "makefile.hpp"

using namespace cm::py;

namespace {
	PyObject*
	init_makefile(_typeobject* arg1, PyObject* arg2, PyObject* arg3) {
		auto obj = PyType_GenericNew( arg1, arg2, arg3 );
		// We have to construct allocated object
		new ( &static_cast<Makefile*>(obj)->file ) Makefile();
		return obj;
	}

	void
	destroy_makefile( PyObject* object ) {
		static_cast<Makefile*>( object )->file.~cmMakefile();
	}
}

PyTypeObject
Makefile::create_type() {
	return {
		PyVarObject_HEAD_INIT(NULL, 0)
		"cmake.Makefile", // tp_name For printing, in format "<module>.<name>"
		sizeof(Makefile), // tp_basicsize
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

