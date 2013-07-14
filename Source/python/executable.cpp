#include "executable.hpp"
#include "target.hpp"
#include "../cmAddExecutableCommand.h"

using namespace cm::py;

namespace {
	class Executable : public target::CommandTarget<cmAddExecutableCommand> {
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
		nullptr, // tp_traverse
		nullptr, // tp_clear
		nullptr, // tp_richcompare
		0      , // tp_weaklistoffset
		nullptr, // tp_iter
		nullptr, // tp_iternext
		nullptr, // tp_methods
		nullptr, // tp_members
		nullptr, // tp_getset
		&target::Target_type, // tp_base
		nullptr, // tp_dict
		nullptr, // tp_descr_get
		nullptr, // tp_descr_set
		0      , // tp_dictoffset
		nullptr, // tp_init
		nullptr, // tp_alloc
		nullptr, // tp_new
		nullptr, // tp_free
		nullptr, // tp_is_gc
		nullptr, // tp_bases
		nullptr, // tp_mro
		nullptr, // tp_cache
		nullptr, // tp_subclasses
		nullptr, // tp_weaklist
		nullptr, // tp_del

		1 // tp_version_tag
	};
} // namespace

PyObject*
cm::py::add_executable( PyObject* self, PyObject* args, PyObject* keywords ) {

	const char* name;
	const char* library_type = nullptr;
	int exclude_from_all = 0;
	PyObject* sources;

	static const char* kw_list[] = { "type", "sources", "exclude_from_all", nullptr };

	if( !PyArg_ParseTupleAndKeywords(args, keywords, "s|$ZO!isp",
	// ugly workaround for messed up interface approaching
									 const_cast<char**>(kw_list),
	// ugly workaround done
									 &name, &library_type, &PyList_Type,
									 &sources, &exclude_from_all) )
		return nullptr;

	auto arguments = [&]() {
		auto strArgs = cm::arg_type{ {name} };
		{
			auto stringType = [&]() -> std::string {
				if( library_type )
					return { library_type };
				else
					return {};
			}();

			if( stringType == "STATIC" || stringType == "SHARED"
			 || stringType == "MODULE" )
				strArgs.push_back( std::move(stringType) );
		}

		if( exclude_from_all == 1 )
			strArgs.emplace_back( "EXCLUDE_FROM_ALL" );

		auto listCount = PyList_Size( sources );

		for( auto i = 0; i < listCount; ++i ) {
			// grab the string object from the next element of the list
			auto listItem = PyList_GetItem( sources, i); // Can't fail
			// make it a string
			strArgs.emplace_back( PyUnicode_AsUTF8( listItem ) );
		}

		return strArgs;
	}();

	auto executable = CM_PY_NEW( Executable );
	executable->init( *self, arguments );
	return executable;
}

