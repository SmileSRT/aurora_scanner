#include "opencv2/opencv.hpp"
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


void restThread(std::string hostname, int port) {
    RestServer api(hostname, port);
    api.process();
}

void getApplicationConfig() {

}

// setup func

int main(int, char**) {
    // setting up the root directory
    std::filesystem::path filePath(__FILE__);
    std::filesystem::path rootPath = filePath.parent_path().parent_path().parent_path();
    std::string root_str = rootPath.string();

    std::string hostname;
    int port;

    // setting up configuration file
    libconfig::Config cfg;

    try {
        cfg.readFile((root_str + "/src/server/config.cfg").c_str());
    } catch(const libconfig::FileIOException &fioex) {
        std::cerr << "Failed to read the configuration file." << std::endl;
        return -1;
    } catch(const libconfig::ParseException &pex) {
        std::cerr << "Failed to parse the configuration file. Line " << pex.getLine() << ": " << pex.getError() << std::endl;
        return -1;
    }

    // assign server to root
    const libconfig::Setting& root = cfg.getRoot();

    try {
        const libconfig::Setting& server = root["server"];
        server.lookupValue("hostname", hostname);
        server.lookupValue("port", port);
    } catch(const libconfig::SettingNotFoundException &nfex) {
        std::cerr << "Ошибка при извлечении значений из файла конфигурации." << std::endl;
        return -1;
    }

    Application app;
    app.start();
    // handler.start();

    std::string file = "/home/smile/projects/aurora_scanner/static/jpg/attendant_list.jpg";
    app.applyHoughLinesToJPG(file);

    std::string testFile = "/home/smile/projects/aurora_scanner/static/jpg/testImg0.jpg";

    Tests testApp;
    cv::Mat testFrame = cv::imread( cv::samples::findFile(file), cv::IMREAD_GRAYSCALE);
    testApp.runTests(testFrame, 0);

    while(1) {

    }

    // creating a server thread
    std::thread api(restThread, hostname, port);
    api.join(); // to append arguments to a restThread function

    return 0;
}