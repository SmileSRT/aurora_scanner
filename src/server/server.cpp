#include "./headers/server.h"
#include <httplib.h>
#include <iostream>

RestServer::RestServer() {};

void RestServer::process() {
    httplib::Server app;

    app.Get("/lines", [](const httplib::Request &req, httplib::Response &res) {
        res.set_content("Hello World!", "text/plain");
    });

    app.Post("/lines", [](const httplib::Request &req, httplib::Response &res) {
            res.set_content(req.body, "text/plain");
    });

    app.listen(this->hostname, this->port);
}