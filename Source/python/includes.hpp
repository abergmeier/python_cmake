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

	namespace py {
		template <typename T>
		T* make_pointer( PyTypeObject& type ) {
			auto obj = PyObject_New( T, &type );
			new (obj) T();
			return obj;
		}
	} // namespace py

	template <typename C1, typename C2>
	void
	merge( C1& to, C2&& from ) {
		to.insert( to.end(),
				   std::make_move_iterator(from.begin()),
				   std::make_move_iterator(from.end())
		);
	}
} // namespace cm

#endif //_CMAKE_PYTHON_INCLUDES_HPP_

