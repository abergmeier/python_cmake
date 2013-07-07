#ifndef _CMAKE_PYTHON_TARGET_HPP_
#define _CMAKE_PYTHON_TARGET_HPP_

#include "includes.hpp"

namespace cm {
	namespace py {
		namespace target {
			extern PyObject* compile_definitions  ( PyObject* self, PyObject* args );
			extern PyObject* compile_options      ( PyObject* self, PyObject* args );
			extern PyObject* depend               ( PyObject* self, PyObject* args );
			extern PyObject* include_directories  ( PyObject* self, PyObject* args );
			extern PyObject* link_libraries       ( PyObject* self, PyObject* args );
			extern PyObject* set_target_properties( PyObject* self, PyObject* args );
		} // namespace target
	} // namespace py
} // namespace cm

#endif //_CMAKE_PYTHON_TARGET_HPP_

