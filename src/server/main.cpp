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

using namespace cv;

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

    //file to recognise
    std::string filename = "testImg3.jpeg";
    std::string filepath = (root_dir + "/static/jpg/" + filename).c_str();

    // recognise lines
    Mat src = imread( samples::findFile( filepath ), IMREAD_GRAYSCALE );
    resize(src, src, Size(0, 0), 0.8, 0.8, INTER_LINEAR);
    Recogniser recogniser;
    Table tableList = recogniser.recognise(src);

    // test for recogniser
    Tests testApp;
    testApp.runTests(tableList, Images::testImg3);

    while(1) {

    }

    api.join(); // to append arguments to a restThread function

    return 0;
}