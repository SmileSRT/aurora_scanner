#pragma once

#include "opencv2/opencv.hpp"
#include "./table.h"


// google test
class Recogniser {
    private:

    public:
        Recogniser();
        virtual Table recognise(cv::Mat frame);
        cv::Mat getCell(int col, int row);
        bool isEmptyCell(int col, int row);
        bool isEmptyCellImg(cv::Mat m);
};