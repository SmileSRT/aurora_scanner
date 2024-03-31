#pragma once

#include <string>

class RestServer {
    std::string hostname = "0.0.0.0";
    int port = 8080;
    
    public:
        RestServer();
        
        void start();
};