#include "opencv2/opencv.hpp"
#include <rapidjson/document.h>
#include <vector>
#include "httplib.h"
#include "./headers/server.h"
#include "./headers/application.h"

using namespace cv;

void restThread() {
    RestServer server;
    server.process();
}

int main(int, char**) {
    // creating a server thread
    std::thread server(restThread);

    Application app;
    app.start();
    // handler.start();

    std::string file = "/home/smile/projects/aurora_scanner/static/jpg/testImg0.jpg";
    app.applyHoughLinesToJPG(file);
    return 0;
}