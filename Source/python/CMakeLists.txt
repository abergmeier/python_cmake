find_package(PythonLibs REQUIRED)

set(PYTHON_SRCS_TEMPLATE
	include
	project
	set_variable
	target
	global
	executable
	library
	makefile
)

foreach( src ${PYTHON_SRCS_TEMPLATE} )
	set( PYTHON_SRCS ${PYTHON_SRCS} ${CMake_SOURCE_DIR}/Source/python/${src}.cpp )
	set( PYTHON_SRCS ${PYTHON_SRCS} ${CMake_SOURCE_DIR}/Source/python/${src}.hpp )
endforeach()

set( PYTHON_SRCS ${PYTHON_SRCS} ${CMake_SOURCE_DIR}/Source/python/includes.hpp )
set( PYTHON_SRCS ${PYTHON_SRCS} ${CMake_SOURCE_DIR}/Source/python/module.cpp )

add_library(PythonCMakeLib SHARED ${PYTHON_SRCS})
target_compile_definitions(PythonCMakeLib PUBLIC "${PYTHON_DEFINITIONS}" )
# include dirs buggy in module
#target_include_directories(PythonCMakeLib PUBLIC "${PYTHON_INCLUDE_DIRS}")
target_include_directories(PythonCMakeLib PUBLIC /usr/include/python3.3m /usr/include/x86_64-linux-gnu/python3.3m)
target_link_libraries     (PythonCMakeLib "${PYTHON_LIBRARIES}"             )
set_target_properties     (PythonCMakeLib PROPERTIES COMPILE_FLAGS -std=c++11)

# Main library
set( PYTHON_SRCS
	${CMake_SOURCE_DIR}/Source/python/includes.hpp
	${CMake_SOURCE_DIR}/Source/python/main_module.cpp
)
add_library( PythonMainLib MODULE ${PYTHON_SRCS} )
target_compile_definitions( PythonMainLib PUBLIC "${PYTHON_DEFINITIONS}"       )
target_include_directories( PythonMainLib PUBLIC /usr/include/python3.3m /usr/include/x86_64-linux-gnu/python3.3m)
target_link_libraries     ( PythonMainLib "${PYTHON_LIBRARIES}" PythonCMakeLib )
set_target_properties     ( PythonMainLib PROPERTIES COMPILE_FLAGS -std=c++11  )

