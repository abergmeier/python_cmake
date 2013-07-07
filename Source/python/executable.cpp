#include "executable.hpp"
#include "target.hpp"
#include "../cmAddExecutableCommand.h"

using namespace cm::py;

namespace {
	struct Executable : public PyObject {
	};

	auto Executable_type = PyTypeObject{
#if 0
		PyObject_HEAD_INIT(NULL)
		0,
		"Executable",
		sizeof(Executable),
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
} // namespace

PyObject*
add_executable( PyObject*, PyObject* args ) {

	return static_cast<PyObject*>( PyObject_New(Executable, &Executable_type) );
}

