find_package(PythonLibs REQUIRED)

set(PYTHON_SRCS
	${CMake_SOURCE_DIR}/Source/python/include.cpp
	${CMake_SOURCE_DIR}/Source/python/module.cpp
	${CMake_SOURCE_DIR}/Source/python/project.cpp
	${CMake_SOURCE_DIR}/Source/python/set_variable.cpp
	${CMake_SOURCE_DIR}/Source/python/target.cpp
	${CMake_SOURCE_DIR}/Source/python/global.cpp

)

add_library(PythonCMakeLib MODULE ${PYTHON_SRCS})
target_compile_definitions(PythonCMakeLib PUBLIC "${PYTHON_DEFINITIONS}" )
# include dirs buggy in module
#target_include_directories(PythonCMakeLib PUBLIC "${PYTHON_INCLUDE_DIRS}")
target_include_directories(PythonCMakeLib PUBLIC /usr/include/python3.3m /usr/include/x86_64-linux-gnu/python3.3m)
target_link_libraries     (PythonCMakeLib "${PYTHON_LIBRARIES}"             )
set_target_properties     (PythonCMakeLib PROPERTIES COMPILE_FLAGS -std=c++11)
