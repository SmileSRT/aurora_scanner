#include "opencv2/opencv.hpp"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "./headers/application.h"
#include "./headers/table.h"
#include "./headers/recogniser.h"
#include <vector>

#include <httplib.h>

using namespace cv;

Application::Application() {};

void Application::sendLinesInJSON(std::vector<Vec4i> lines) {
    rapidjson::Document document;
    document.SetObject();

    rapidjson::Value linesJSON(rapidjson::kArrayType);

    for (int i = 0; i < lines.size(); i++) {
        rapidjson::Value object(rapidjson::kObjectType);
        object.AddMember("x1", lines[i][0], document.GetAllocator());
        object.AddMember("y1", lines[i][1], document.GetAllocator());
        object.AddMember("x2", lines[i][2], document.GetAllocator());
        object.AddMember("y2", lines[i][3], document.GetAllocator());
        linesJSON.PushBack(object, document.GetAllocator());
    }

    document.AddMember("lines", linesJSON, document.GetAllocator());
    
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    // std::cout << buffer.GetString() << std::endl;

    this->postJSONToAPI(strdup(buffer.GetString()));
};

void Application::postJSONToAPI(std::string buff) {
    httplib::Client client(this->hostname, this->port);

    client.Post("/lines", buff, "application/json");
};
