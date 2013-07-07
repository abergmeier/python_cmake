#include "library.hpp"
#include "target.hpp"
#include "../cmAddLibraryCommand.h"

using namespace cm::py;

namespace {
	struct Library : public PyObject {
	};

	auto Library_type = PyTypeObject{
#if 0
		PyObject_HEAD_INIT(NULL)
		0,
		"Executable",
		sizeof(Library),
		0,
		PyObject_Del, /*tp_dealloc*/
		0,          /*tp_print*/
		0,          /*tp_getattr*/
		0,          /*tp_setattr*/
		0,          /*tp_compare*/
		0,          /*tp_repr*/
		0,          /*tp_as_number*/
		0,          /*tp_as_sequence*/
		0,          /*tp_as_mapping*/
		0,          /*tp_hash */
#endif
	};
}

PyObject*
add_library( PyObject*, PyObject* args ) {

	return static_cast<PyObject*>( PyObject_New(Library, &Library_type) );
}

