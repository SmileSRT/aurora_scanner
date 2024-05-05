#pragma once

#include "opencv2/opencv.hpp"
#include "./table.h"

class Recogniser {
    private:

    public:
        Recogniser();
        Table recognise(cv::Mat frame);
        cv::Mat getCell(int col, int row);
        bool isEmptyCell(int col, int row);
        bool isEmptyCellImg(cv::Mat m);
};