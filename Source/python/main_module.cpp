#include "makefile.hpp"

using namespace cm::py;

namespace {
	auto Makefile_type = Makefile::create_type();

	PyMethodDef METHODS[] = {

		{ nullptr, nullptr, 0, nullptr } // Sentinel
	};

	namespace py {
		namespace module {
			auto INTERFACE = PyModuleDef{
				PyModuleDef_HEAD_INIT, // m_base
				"cmake_main", // m_name
				nullptr, // m_doc
				-1,      // m_size
				METHODS, // m_methods
				nullptr, // m_reload
				nullptr, // m_traverse
				nullptr, // m_clear
				nullptr  // m_free
			};
		} // namespace module
	} // namespace py
}

PyMODINIT_FUNC
PyInit_cmake_main() {
	auto module = PyModule_Create( &py::module::INTERFACE );

	if( !module )
		return nullptr;

	auto makefile = make_pointer<Makefile>( Makefile_type );
	assert( PyModule_AddObject( module, "makefile", makefile) == 0 );

	return module;
}
