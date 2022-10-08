# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

# Set the project name
project (hello_headers)

set(CMAKE_BUILD_TYPE DEBUG)


# Create a sources variable with a link to all cpp files to compile
set(SOURCES
        src/doublePoint.cpp
        src/main.cpp
        src/MutliThread.cpp
        src/thread_test.cpp
        src/async_test.cpp
        src/time_chrono_signal_test.cpp
        )


set(CMAKE_CXX_FLAGS "${CAMKE_CXX_FLAGS} -std=c++11 -pthread")
#[[set(CMAKE_CXX_STANDARD 11)]]


#IF (WIN32)
#    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fexec-charset=GBK")
#ENDIF ()

# Add an executable with the above sources
add_executable(hello_headers ${SOURCES})

# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
target_include_directories(hello_headers
        PRIVATE   #表示私有传播，而在cmake中共有三种传播
        ${PROJECT_SOURCE_DIR}/include
        )

add_compile_options(
        /std:c++latest
)


# bar调用了一下foo的函数   bar  继承关系 foo

