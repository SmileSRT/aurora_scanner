#include "./headers/application.h"
#include "opencv2/opencv.hpp"
#include <vector>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <httplib.h>


using namespace cv;

Application::Application() {};

void Application::start() {
    VideoCapture cap(0); // Открываем камеру или файл

    if(!cap.isOpened()) { 
        std::cout << "The video capture is denied or failed" << std::endl;
        return; // check if we succeeded
    } 

    Mat edges;
    namedWindow("edges",1);

    while(1) {
        Mat frame;
        cap >> frame; // get a new frame from camera
        cvtColor(frame, edges, COLOR_BGR2GRAY); // Перевод в градации серого
        GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5); // Размытие
        Canny(edges, edges, 0, 30, 3); // Выделение границ

        // Add Hough Lines
        std::vector<Vec4i> lines;
        HoughLinesP(edges, lines, 1, CV_PI / 180, 100, 10, 250); // Выполнить преобразование хафа

        for (size_t i = 0; i < lines.size(); i++) {
            Vec4i l = lines[i];

            line(edges, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 0, 0), 3, LINE_AA);
        }

        if(waitKey(30) >= 0) break;

        imshow("edges", edges);
    }

    return;
};

void Application::applyHoughLinesToJPG(std::string filepath) {
    // Load an image
    Mat src = imread( samples::findFile( filepath ), IMREAD_GRAYSCALE );
    Mat dst, cdst, cdstP;

    if(src.empty()) {
        std::cout << "Could not read the image: " << std::endl;
        return;
    }
    
    Canny(src, dst, 50, 200, 3);
    cvtColor(dst, cdst, COLOR_GRAY2BGR);
    cdstP = cdst.clone();

    // Standard Hough Line Transform in Points
    std::vector<Vec4f> lines; // will hold the results of the detection
    HoughLinesP(dst, lines, 1, CV_PI/180, 150, 0, 0 ); // runs the actual detection

    // Draw the lines
    for (size_t i = 0; i < lines.size(); i++) {
        Vec4i l = lines[i];

        line(cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 0, 0), 3, LINE_AA);
    }

    this->sendLinesInJSON(lines);
};

void Application::sendLinesInJSON(std::vector<Vec4f> lines) {
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

    this->postJSONToAPI(strdup(buffer.GetString()));
};

void Application::postJSONToAPI(std::string buff) {
    httplib::Client client(this->hostname, this->port);

    client.Post("/lines", buff, "application/json");
};