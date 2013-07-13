#ifndef _CMAKE_PYTHON_TARGET_HPP_
#define _CMAKE_PYTHON_TARGET_HPP_

#include "includes.hpp"
#include "../cmCommand.h"

namespace cm {
	namespace py {

		template <typename T>
		T* make_pointer( PyTypeObject& type ) {
			auto obj = PyObject_New( T, &type );
			new (obj) T();
			return obj;
		}

		extern std::vector<std::string> to_vector( PyObject* list );

		namespace target {
			extern PyObject* compile_definitions( PyObject* self, PyObject* args );
			extern PyObject* compile_options    ( PyObject* self, PyObject* args );
			extern PyObject* depend             ( PyObject* self, PyObject* args );
			extern PyObject* include_directories( PyObject* self, PyObject* args );
			extern PyObject* link_libraries     ( PyObject* self, PyObject* args );
			extern PyObject* set_properties     ( PyObject* self, PyObject* args );

			struct Target : public PyObject {
			public:
				Target( cmCommand& command );
				void init( PyObject& cmake, const cm::arg_type& args );
			protected:
				cmCommand& _command;
			};
		} // namespace target
	} // namespace py
} // namespace cm

#define	CM_PY_NEW( xxx ) \
	[&]() { \
		auto obj = PyObject_New( xxx, &xxx##_type );\
		new (obj) xxx(); \
		obj->init( *self, arguments );\
		return obj; \
	}()

#endif //_CMAKE_PYTHON_TARGET_HPP_

