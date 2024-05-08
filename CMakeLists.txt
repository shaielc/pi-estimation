cmake_minimum_required(VERSION 3.12) # Ensure you're using CMake 3.12 or newer for GLOB_RECURSE
project(MyProject)

# Set the output directory for the executables
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# Glob all.cpp files in the current directory and subdirectories
file(GLOB_RECURSE CPP_FILES "*.cpp")

# Loop over each.cpp file and create an executable
foreach(CPP_FILE ${CPP_FILES})
    # Extract the filename without extension
    get_filename_component(FILE_NAME ${CPP_FILE} NAME_WE)
    
    # Extract the directory path from the.cpp file path
    get_filename_component(DIRECTORY_PATH ${CPP_FILE} DIRECTORY)
    
    file(RELATIVE_PATH RELATIVE_DIRECTORY_PATH ${CMAKE_CURRENT_SOURCE_DIR} ${DIRECTORY_PATH})
    file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${RELATIVE_DIRECTORY_PATH}")
    message(RELATIVE_DIRECTORY_PATH="${RELATIVE_DIRECTORY_PATH}")
    
    # Combine the directory path with the filename to create a unique executable name
    set(EXECUTABLE_NAME "${FILE_NAME}")
    
    # Create an executable with the unique name
    add_executable(${EXECUTABLE_NAME} ${CPP_FILE})
    set_target_properties(${EXECUTABLE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${RELATIVE_DIRECTORY_PATH}")

endforeach()