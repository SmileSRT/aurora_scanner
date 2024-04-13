#include "./headers/tests.h"

Tests::Tests(Table _table) {
    testTable = _table;
}

void Tests::validateTable(int colNum, int rowNum) {
    if (testTable.getColNum() == colNum && testTable.getRowNum() == rowNum) {
        std::cout << "test passed\n";

        return;
    }

    std::cout << "test loosed\n";
}