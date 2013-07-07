#ifndef _CMAKE_PYTHON_INCLUDES_HPP_
#define _CMAKE_PYTHON_INCLUDES_HPP_

#include <vector>
#include <string>
// Make sure we use the new safe argument
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#undef HAVE_UNSETENV

namespace cm {
	typedef std::vector<std::string> arg_type;
} // namespace cm

#endif //_CMAKE_PYTHON_INCLUDES_HPP_

