#pragma once

#include <iostream>
#include "table.h"

class Tests {
    Table testTable;

    public:
    Tests(Table _Table);
    void validateTable(int rowNums, int colNums);
};