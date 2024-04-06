#pragma once
#include "opencv2/opencv.hpp"
#include <vector>

using namespace cv;

class Application {
    private:
        std::string hostname = "0.0.0.0";
        int port = 8080;
        Mat edges;

    public:
        Application();
        void start();
        void applyHoughLinesToJPG(std::string filepath);
        void postJSONToAPI(std::string buff);
        void sendLinesInJSON(std::vector<Vec4f> lines);
};