#include "libconfig.h++"
#include <string>
#include "./headers/config.h"
#include <iostream>


Config::Config() {};

void Config::readConfigFile(const std::string& configFile, libconfig::Config& cfg) {
    try {
        cfg.readFile(configFile.c_str());
    } catch(const libconfig::FileIOException &fioex) {
        std::cerr << "Failed to read the configuration file." << std::endl;
        throw std::exception();
    } catch(const libconfig::ParseException &pex) {
        std::cerr << "Failed to parse the configuration file. Line " << pex.getLine() << ": " << pex.getError() << std::endl;
        throw std::exception();
    }
};

void Config::extractServerConfig(const libconfig::Config& cfg, std::string& hostname, int& port) {
    const libconfig::Setting& root = cfg.getRoot();

    try {
        const libconfig::Setting& server = root["server"];
        server.lookupValue("hostname", hostname);
        server.lookupValue("port", port);
    } catch(const libconfig::SettingNotFoundException &nfex) {
        std::cerr << "Failed to load configuration file." << std::endl;
        throw std::exception();
    }
};