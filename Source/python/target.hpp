#ifndef _CMAKE_PYTHON_TARGET_HPP_
#define _CMAKE_PYTHON_TARGET_HPP_

#include "includes.hpp"
#include "makefile.hpp"
#include "../cmCommand.h"

namespace cm {
	namespace py {

		extern std::vector<std::string> to_vector( PyObject* list );

		extern void execute( cmMakefile& makefile, cmCommand& command, const cm::arg_type& arguments );

		template <typename Command>
		void execute( cmMakefile& makefile, const cm::arg_type& arguments ) {

			auto command = Command{};

			execute( makefile, command, arguments );
		}

		namespace target {
			extern PyObject* compile_definitions( PyObject* self, PyObject* args );
			extern PyObject* compile_options    ( PyObject* self, PyObject* args );
			extern PyObject* depend             ( PyObject* self, PyObject* args );
			extern PyObject* include_directories( PyObject* self, PyObject* args );
			extern PyObject* link_libraries     ( PyObject* self, PyObject* args, PyObject* keywords );
			extern PyObject* set_properties     ( PyObject* self, PyObject* args );

			struct Target : public PyObject {
			protected:
				Target() noexcept = default;
			public:
				virtual ~Target() noexcept = default;
				virtual std::string name() = 0;
				virtual cmMakefile& makefile() = 0;
			};

			template <typename Command>
			struct CommandTarget : public Target {
			protected:
				CommandTarget() = default;
			public:
				virtual ~CommandTarget() noexcept = default;
				void init( PyObject& cmake, const cm::arg_type& args );

			protected:
				Command command;
			public:
				virtual std::string name() override {
					return command.GetName();
				}

				virtual cmMakefile& makefile() override {
					return *command.GetMakefile();
				}
			};

			template <typename Command>
			void
			CommandTarget<Command>::init( PyObject& cmake, const cm::arg_type& args ) {

				auto& cmakeFile = [&]() -> cmMakefile& {
					auto makefileWrapper = PyObject_GetAttr( &cmake, PyUnicode_FromString("makefile") );
					return static_cast<cm::py::Makefile*>(makefileWrapper)->file;
				}();

				execute( cmakeFile, command, args );
			}

			extern PyTypeObject Target_type;

		} // namespace target
	} // namespace py
} // namespace cm

#define CM_PY_NEW( xxx ) \
	cm::py::make_pointer<xxx>( xxx##_type )

#endif //_CMAKE_PYTHON_TARGET_HPP_

