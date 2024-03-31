#include "./headers/video_handler.h"
#include "opencv2/opencv.hpp"
#include <vector>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace cv;


VideoHandler::VideoHandler() {};

void VideoHandler::start() {
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

        // this->sendLinesInJSON(lines);
        if(waitKey(30) >= 0) break;

        imshow("edges", edges);
    }

    return;
};

void VideoHandler::sendLinesInJSON(std::vector<Vec4i> lines) {
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

    // Выводим JSON
    std::cout << buffer.GetString() << std::endl;

};