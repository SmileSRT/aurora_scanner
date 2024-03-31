#include "./headers/server.h"
#include <httplib.h>
#include <iostream>

RestServer::RestServer() {};

void RestServer::start() {
    httplib::Server app;

    app.Get("/lines", [](const httplib::Request &req, httplib::Response &res) {
        res.set_content("Hello World!", "text/plain");
    });

    app.Post("/lines", [](const httplib::Request &req, httplib::Response &res) {

        res.set_content("ok", "text/plain");
    });

    app.listen(hostname, port);
}