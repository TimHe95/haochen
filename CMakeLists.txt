project(tainter)
cmake_minimum_required(VERSION 2.8)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# Needed to use support library

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fno-rtti -std=c++14")

message(STATUS "Found LLVM_INCLUDE_DIRS ${LLVM_INCLUDE_DIRS}")
include_directories(${LLVM_INCLUDE_DIRS})
message(STATUS "Found LLVM_DEFINITIONS ${LLVM_DEFINITIONS}")
add_definitions(${LLVM_DEFINITIONS})


set(LLVM_LINK_COMPONENTS
    Core
    ExecutionEngine
    Interpreter
    MC
    Support
    nativecodegen
    mcjit
    X86
    asmparser
    objcarcopts
    scalaropts
    transformutils
    irreader
)


add_executable(tainter
    tainter.cpp
    #    explore.cpp
)

llvm_map_components_to_libnames(llvm_libs ${LLVM_LINK_COMPONENTS})



#link llvm component
message(STATUS "Found llvm_libs ${llvm_libs}")
target_link_libraries(tainter ${llvm_libs})

target_link_libraries(tainter
    pthread
    # tinfo
    dl
    ${llvm_libs}
)
