#pragma once

#include <iostream>
#include "opencv2/opencv.hpp"
#include "../helpers/images.h"
#include "table.h"

class Tests {
    Table testTable;

    public:
    Tests();
    Tests(Table _Table);
    void runTests(Table recgTable, Images image);
    void validateTable(int rowNums, int colNums);
};