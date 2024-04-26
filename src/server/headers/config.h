#pragma once

#include "libconfig.h++"
#include <string>


class Config: public libconfig::Config {
    private:

    public:
        Config();
        void readConfigFile(const std::string& configFile, libconfig::Config& cfg);
        void extractServerConfig(const libconfig::Config& cfg, std::string& hostname, int& port);
};