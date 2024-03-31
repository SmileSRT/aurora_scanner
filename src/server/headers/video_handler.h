#pragma once
#include "opencv2/opencv.hpp"
#include <vector>

using namespace cv;

class VideoHandler {
    private:
        Mat edges;

    public:
        VideoHandler();
        void start();
        void sendLinesInJSON(std::vector<Vec4i> lines);
};