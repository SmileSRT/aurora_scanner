#include "./headers/table.h"

Table::Table() {}

Table::Table(int rows, int cols) {
    this->rows = rows;
    this->cols = cols;
};

int Table::getRowNum() {
    return this->rows;
};

int Table::getColNum() {
    return this->cols;
};
