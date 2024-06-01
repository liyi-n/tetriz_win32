cmake_minimum_required(VERSION 3.22)

project(tetriz_win32)

set(CMAKE_CXX_STANDARD 20)

configure_file( ${PROJECT_SOURCE_DIR}/tetriz.map ${PROJECT_BINARY_DIR})
aux_source_directory(. src)
add_executable(tetriz_win32 ${src})

if(MSVC)
    target_compile_options(tetriz_win32 PRIVATE "/utf-8")
    #runtime dll /MT /MTd /MD /MDd
    set_property(TARGET tetriz_win32 PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()