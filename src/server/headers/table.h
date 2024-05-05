#pragma once

#include <iostream>
#include <string>


class Table {
    private:
        int rows;
        int cols;
    public:
        Table();
        Table(int rows, int cols);
        int getRowNum();
        int getColNum();
};  