cmake_minimum_required(VERSION 3.8)

# Be nice to visual studio
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Set default install location to dist folder in build dir we do not want to install to /usr by default
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set (CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/dist" CACHE PATH "Install path prefix, prepended onto install directories." FORCE )
endif()

project(SortingVisualisation VERSION 0.1.0)
add_executable(${PROJECT_NAME})

message(STATUS "")
message(STATUS "    == ${PROJECT_NAME} Project configuration ==")
message(STATUS "")

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# Enable good warnings
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /WX /W3)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -pedantic-errors)
endif()

# Set the folder where the executable is created
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

# piksel
add_subdirectory(lib/piksel)
target_link_libraries(${PROJECT_NAME} piksel)
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE lib/piksel/src)

# other lib
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE "lib")

# Get sources files
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "src/*")
target_sources(${PROJECT_NAME} PRIVATE ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE src)

message(STATUS "")
message(STATUS "    == ${PROJECT_NAME} Buill overview ==")
message(STATUS "Compiler:             ${CMAKE_CXX_COMPILER}")
message(STATUS "CMAKE_BUILD_TYPE:     ${CMAKE_BUILD_TYPE}")