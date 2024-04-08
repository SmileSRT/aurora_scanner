#pragma once

#include <iostream>
#include <string>


class Table {
    private:
        int rows;
        int cols;
    public:
        Table(int rows, int cols);
        std::string get(int row, int col);
        int getRowNum();
        int getColNum();
};