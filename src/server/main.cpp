#include "opencv2/opencv.hpp"
#include <rapidjson/document.h>
#include <vector>
#include "httplib.h"
#include "./headers/server.h"
#include "./headers/video_handler.h"

using namespace cv;

void restThread() {
    RestServer test;
    test.start();
}

int main(int, char**) {
    // creating a server thread
    std::thread server(restThread);

    VideoHandler handler;
    handler.start();

    return 0;
}