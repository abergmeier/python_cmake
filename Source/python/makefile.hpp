#ifndef _CMAKE_PYTHON_MAKEFILE_HPP_
#define _CMAKE_PYTHON_MAKEFILE_HPP_

#include "includes.hpp"
#include "../cmMakefile.h"

namespace cm {
	namespace py {

		class Build : public cmMakefile {
		public:
			bool ReadListFile( const char* filename_in, const char *external_in,
							   std::string* fullPath );
			bool configure( const char* filename_in, const char *external_in,
							std::string* fullPath );
		};

		struct Makefile : public PyObject {
			Build file;
			static PyTypeObject create_type();
		};
	} // namespace py
} // namespace cm

#endif //_CMAKE_PYTHON_MAKEFILE_HPP_

