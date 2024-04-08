#include "opencv2/opencv.hpp"
#include <rapidjson/document.h>
#include <vector>
#include "httplib.h"
#include "./headers/server.h"
#include "./headers/application.h"
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
    

    // creating a server thread
    std::thread api(restThread, hostname, port);
    api.join(); // to append arguments to a restThread function

    Application app;
    // handler.start();

    std::string file = (root_str + "/static/jpg/attendant_list.jpg").c_str();
    app.applyHoughLinesToJPG(file);

    while(1) {

    }

    return 0;
}