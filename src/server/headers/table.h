#include <iostream>

class Table {
    private:
        int rows;
        int cols;
    public:
        Table();
        Table(int rows, int cols);
        std::string get(int row, int col);
        int getRowNum();
        int getColNum();
};  