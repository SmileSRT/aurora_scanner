#include <rapidjson/document.h>
#include <vector>
#include "httplib.h"
#include "./headers/server.h"
#include "./headers/application.h"
#include "./headers/tests.h"
#include <libconfig.h++>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <filesystem>
#include "./headers/recogniser.h"
#include "./headers/table.h"
#include "./headers/config.h"


void restThread(std::string hostname, int port) {
    RestServer api(hostname, port);
    api.process();
}

int main(int, char**) {
    // setting up the root directory
    std::filesystem::path filePath(__FILE__);
    std::filesystem::path rootPath = filePath.parent_path().parent_path().parent_path();
    std::string root_dir = rootPath.string();

    std::string hostname;
    int port;
    // setting up configuration file
    
    Config cfg;
    cfg.readConfigFile((root_dir + "/src/server/config.cfg").c_str(), cfg);
    cfg.extractServerConfig(cfg, hostname, port);

    // creating a server thread
    std::thread api(restThread, hostname, port);


    Application app;
    // handler.start();

    std::string file = (root_dir + "/static/jpg/attendant_list.jpg").c_str();
    cv::Mat lines = app.applyHoughLinesToJPG(file);

    Recogniser recg;
    Table myTab = recg.recognise(lines);

    Tests testApp;
    cv::Mat testFrame = cv::imread( cv::samples::findFile(file), cv::IMREAD_GRAYSCALE);
    testApp.runTests(testFrame, 0);

    while(1) {

    }

    api.join(); // to append arguments to a restThread function

    return 0;
}