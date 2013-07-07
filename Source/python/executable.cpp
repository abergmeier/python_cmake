#include "executable.hpp"
#include "target.hpp"
#include "../cmAddExecutableCommand.h"

using namespace cm::py;

namespace {
	struct Executable : public target::Target {
	};

	auto Executable_type = PyTypeObject{
		PyVarObject_HEAD_INIT(NULL, 0)
		"cmake.Executable", // tp_name For printing, in format "<module>.<name>"
		sizeof(Executable), // tp_basicsize
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
		"CMake Executable objects", // tp_doc Documentation string
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
} // namespace

PyObject*
add_executable( PyObject*, PyObject* args ) {

	return static_cast<PyObject*>( PyObject_New(Executable, &Executable_type) );
}

