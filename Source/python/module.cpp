#include "include.hpp"
#include "set_variable.hpp"
#include "project.hpp"
#include "target.hpp"

namespace cm {
	namespace py {
		namespace module {
			PyMethodDef METHODS[] = {

				{ "project", create_project    , METH_VARARGS, "Execute a shell command."},
				{ "include", include_cmake_file, METH_VARARGS, ""},
				{ "set"    , set_variable      , METH_VARARGS, ""},
				{ "compile_definitions", target::compile_definitions, METH_VARARGS, "" },
				{ "compile_options"    , target::compile_options    , METH_VARARGS, "" },
				{ "depend"             , target::depend             , METH_VARARGS, "" },
				{ "include_directories", target::include_directories, METH_VARARGS, "" },
				{ "link_libraries"     , target::link_libraries     , METH_VARARGS, "" },

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


