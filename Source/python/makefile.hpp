#ifndef _CMAKE_PYTHON_MAKEFILE_HPP_
#define _CMAKE_PYTHON_MAKEFILE_HPP_

#include "includes.hpp"
#include "../cmMakefile.h"

namespace cm {
	namespace py {
		struct Makefile : public PyObject {
			cmMakefile file;
			static PyTypeObject create_type();
		};
	} // namespace py
} // namespace cm

#endif //_CMAKE_PYTHON_MAKEFILE_HPP_

