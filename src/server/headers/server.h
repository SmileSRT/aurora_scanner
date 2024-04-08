#pragma once

#include <string>
#include <libconfig.h>

class RestServer {
    std::string hostname;
    int port;
    
    public:
        RestServer(std::string hostname, int port);
        void process();
};