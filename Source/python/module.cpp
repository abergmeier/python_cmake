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
				{ "library"   , add_library       , METH_VARARGS, "Add a library."},
				{ "executable", add_executable    , METH_VARARGS, "Add a executable."},

				{ nullptr, nullptr, 0, nullptr }        /* Sentinel */
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

		PyMODINIT_FUNC
		initcmake() {
			return PyModule_Create( &module::INTERFACE );
		}
	} // namespace py
} // namespace cm


