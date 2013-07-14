#include "include.hpp"
#include "set_variable.hpp"
#include "project.hpp"
#include "library.hpp"
#include "executable.hpp"
#include "target.hpp"
#include "makefile.hpp"

namespace cm {
	namespace py {
		namespace module {
			PyMethodDef METHODS[] = {

				{ "project"   , create_project    , METH_VARARGS, "Create a new project."},
				{ "include"   , include_cmake_file, METH_VARARGS, "Include a CMake script file."},
				{ "set"       , set_variable      , METH_VARARGS, "Set a variable."},
				{ "library"   , reinterpret_cast<PyCFunction>(add_library)   , METH_VARARGS | METH_KEYWORDS, "Add a library."},
				{ "executable", reinterpret_cast<PyCFunction>(add_executable), METH_VARARGS | METH_KEYWORDS, "Add a executable."},

				{ nullptr, nullptr, 0, nullptr } // Sentinel
			};

			auto INTERFACE = PyModuleDef{
				PyModuleDef_HEAD_INIT, // m_base
				"cmake", // m_name
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
} // namespace cm

using namespace cm::py;

namespace {

	auto Makefile_type = Makefile::create_type();
}


PyMODINIT_FUNC
PyInit_cmake() {
#if 0
	if( PyType_Ready(&NoddyType) < 0 )
		return NULL;
#endif

	auto module = PyModule_Create( &cm::py::module::INTERFACE );

	if( !module )
		return nullptr;

#if 0
	Py_INCREF(&NoddyType);
	PyModule_AddObject(m, "Noddy", (PyObject *)&NoddyType);
#endif
	return module;
}

template <typename Collection>
struct pushed_entry {
private:
	Collection& _collection;
public:
	template <typename Value>
	pushed_entry( Collection& collection, Value& value ) :
		_collection( collection )
	{
		_collection.push_back( value );
	}

	~pushed_entry() noexcept {
		_collection.pop_back();
	}
};

template <typename Collection, typename Value>
pushed_entry<Collection>
push( Collection& collection, Value& value ) {
	return pushed_entry<Collection>{ collection, value };
}

//----------------------------------------------------------------------------
// Parse the given CMakeLists.txt file executing all commands
//
bool
Build::ReadListFile( const char* filename_in, const char *external_in,
                     std::string* fullPath ) {
	return configure( filename_in, external_in, fullPath );
}

bool
Build::configure( const char* filename_in, const char *external_in,
                  std::string* fullPath ) {
	auto currentParentFile
		= std::string{ GetSafeDefinition("CMAKE_PARENT_LIST_FILE") };
	auto currentFile
		= std::string{ GetSafeDefinition("CMAKE_CURRENT_LIST_FILE") };

	auto AddUsedDefinition = [&]( const char* variable_name, const char* value ) {
		AddDefinition     ( variable_name, value );
		MarkVariableAsUsed( variable_name );
	};

	AddUsedDefinition( "CMAKE_PARENT_LIST_FILE", filename_in );

	const char* external = nullptr;
	std::string external_abs;

	auto filename = filename_in;
	std::string filename_abs;

	auto CollapseFullPath = []( const char* path, const char* base ) {
		return cmSystemTools::CollapseFullPath( path, base );
	};

	auto GetFilenamePath = []( const std::string& path ) {
		return cmSystemTools::GetFilenamePath( path );
	};

	auto GetFilenameName = []( const std::string& path  ) {
		return cmSystemTools::GetFilenameName( path );
	};

	if( external_in ) {
		external_abs = CollapseFullPath( external_in,
		                                 cmStartDirectory.c_str() );
		external = external_abs.c_str();
		if( filename_in ) {
			filename_abs = CollapseFullPath( filename_in,
			                                 cmStartDirectory.c_str());
			filename = filename_abs.c_str();
		}
	}

	// keep track of the current file being read
	if( filename && cmCurrentListFile != filename )
		cmCurrentListFile = filename;

	// Now read the input file
	auto filenametoread = filename;

	if( external)
		filenametoread= external;

	AddUsedDefinition( "CMAKE_CURRENT_LIST_FILE", filenametoread );
	AddUsedDefinition( "CMAKE_CURRENT_LIST_DIR",
	                   GetFilenamePath(filenametoread).c_str() );


	// try to see if the list file is the top most
	// list file for a project, and if it is, then it
	// must have a project command.   If there is not
	// one, then cmake will provide one via the
	// cmListFileCache class.
	bool requireProjectCommand = false;
	if( !external && cmStartDirectory == cmHomeDirectory ) {
		auto name = GetFilenameName( filename );
		if( cmSystemTools::LowerCase(name) == "cmakelists.txt")
			requireProjectCommand = true;
	}

	// push the listfile onto the stack
	ListFileStack.push_back( filenametoread );

	if( fullPath!=0 )
		*fullPath = filenametoread;

#if 0 // not applicable
	cmListFile cacheFile;
	if( !cacheFile.ParseFile(filenametoread, requireProjectCommand, this) ) {
		// pop the listfile off the stack
		ListFileStack.pop_back();
		if(fullPath!=0)
			*fullPath = "";

		AddUsedDefinition( "CMAKE_PARENT_LIST_FILE", currentParentFile.c_str() );
		AddUsedDefinition( "CMAKE_CURRENT_LIST_FILE", currentFile.c_str() );
		AddUsedDefinition( "CMAKE_CURRENT_LIST_DIR",
		                   GetFilenamePath(currentFile).c_str());
		return false;
	}
#endif
	// add this list file to the list of dependencies

	{
		auto pushedEntry = push( ListFiles, filenametoread );

		{ // Run the commands.
			auto object = PyImport_Import( PyUnicode_FromString(filenametoread) );
			PyObject_Del( object );
		}

		// If this is the directory-level CMakeLists.txt file then perform
		// some extra checks.
		if(ListFileStack.size() == 1)
			EnforceDirectoryLevelRules();

		AddUsedDefinition( "CMAKE_PARENT_LIST_FILE" , currentParentFile.c_str() );
		AddUsedDefinition( "CMAKE_CURRENT_LIST_FILE", currentFile.c_str()      );
		AddUsedDefinition( "CMAKE_CURRENT_LIST_DIR" ,
						   GetFilenamePath(currentFile).c_str() );

		// pop the listfile off the stack
	}

	// Check for unused variables
	CheckForUnusedVariables();

	return true;
}

