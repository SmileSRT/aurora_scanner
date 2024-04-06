cmake_minimum_required(VERSION 3.29)
project(aurora_scanner)

set(OpenCV_DIR /path/to/opencv_install_dir/lib/cmake/opencv4)
set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL
    https://github.com/google/googletest/archive/03597a01ee50ed33e9df
    d640b249b4be3799d395.zip
)

include(FetchContent)

FetchContent_Declare(cpp-httplib
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib
    GIT_TAG v0.15.3
)
FetchContent_Populate(cpp-httplib)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

# Initialize targets
add_executable(${PROJECT_NAME} 
    src/server/main.cpp 
    src/server/server.cpp
    src/server/application.cpp
    src/server/recogniser.cpp
    src/server/table.cpp
)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBRARIES})

target_include_directories(${PROJECT_NAME} PUBLIC "${cpp-httplib_SOURCE_DIR}")
target_include_directories(${PROJECT_NAME} PUBLIC "${cpp-httplib_SOURCE_DIR}")