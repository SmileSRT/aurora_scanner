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
    // handler.start();

    std::string file = "/home/rodion/Docs/hl/aurora_scanner/static/jpg/attendant_list.jpg";
    app.applyHoughLinesToJPG(file);

    while(1) {

    }
    return 0;
}