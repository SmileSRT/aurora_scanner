set(OpenCV_DIR /path/to/opencv_install_dir/lib/cmake/opencv4)

include(FetchContent)

FetchContent_Declare(cpp-httplib
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib
    GIT_TAG v0.15.3
)

FetchContent_Populate(cpp-httplib)

find_package(OpenCV REQUIRED core highgui imgproc)

add_executable(${PROJECT_NAME} src/server/main.cpp)
add_executable(${PROJECT_NAME} src/server/server.cpp)

include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
target_include_directories(${PROJECT_NAME} PUBLIC "${cpp-httplib_SOURCE_DIR}")