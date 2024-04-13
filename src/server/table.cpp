#include "./headers/table.h"

Table::Table() {}

Table::Table(int rows, int cols) {
    this->rows = rows;
    this->cols = cols;
};

int Table::getRowNum() {
    return this->rows;
};

int Table::setNewColNum(int cols) {
    this->cols = cols;
    return 0;
}

int Table::setNewRowNum(int rows) {
    this->rows = rows;
    return 0;
}

int Table::getColNum() {
    return this->cols;
};
