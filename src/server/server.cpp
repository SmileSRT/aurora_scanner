#include "./headers/server.h"
#include <httplib.h>

RestServer::RestServer() {};

void RestServer::start() {
    httplib::Server svr;

    svr.Get("/hi", [](const httplib::Request &, httplib::Response &res) {
        res.set_content("Hello World!", "text/plain");
    });

    svr.listen(hostname, port);
}