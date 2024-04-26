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
        std::string get(int row, int col);
        int setNewRowNum(int rows);
        int setNewColNum(int cols);
        int getRowNum();
        int getColNum();
};  