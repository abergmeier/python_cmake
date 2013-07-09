#include "include.hpp"
#include "set_variable.hpp"
#include "project.hpp"
#include "library.hpp"
#include "executable.hpp"
#include "target.hpp"

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


PyMODINIT_FUNC
PyInit_cmake() {
#if 0
	if( PyType_Ready(&NoddyType) < 0 )
		return NULL;
#endif

	auto module = PyModule_Create( &cm::py::module::INTERFACE );

	if( !module )
		return nullptr;
#if 0
	Py_INCREF(&NoddyType);
	PyModule_AddObject(m, "Noddy", (PyObject *)&NoddyType);
#endif
	return module;
}

