#pragma once

#include "opencv2/opencv.hpp"
#include <vector>
#include <string>


class Application {
    private:
        const char* hostname = "0.0.0.0";
        const int port = 8080;
        cv::Mat edges;

    public:
        Application();
        void start();
        cv::Mat applyHoughLinesToJPG(std::string filepath);
        void postJSONToAPI(std::string buff);
        void sendLinesInJSON(std::vector<cv::Vec4i> lines);
        void runTests(cv::Mat frame, int numberFrame);
};