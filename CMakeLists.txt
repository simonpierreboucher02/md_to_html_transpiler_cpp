cmake_minimum_required(VERSION 3.10)
project(MarkdownToHTMLTranspiler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/main.cpp
    src/lexer.cpp
    src/parser.cpp
    src/generator.cpp
)

# Header files
set(HEADERS
    include/transpiler.hpp
)

# Create executable
add_executable(markdown-transpiler ${SOURCES} ${HEADERS})

# Compiler flags
if(MSVC)
    target_compile_options(markdown-transpiler PRIVATE /W4)
else()
    target_compile_options(markdown-transpiler PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Install target
install(TARGETS markdown-transpiler DESTINATION bin) 