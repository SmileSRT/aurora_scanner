#pragma once

#include <iostream>
#include "opencv2/opencv.hpp"
#include "table.h"

class Tests {
    Table testTable;

    public:
    Tests();
    Tests(Table _Table);
    void runTests(cv::Mat frame, int numberImg);
    void validateTable(int rowNums, int colNums);
};