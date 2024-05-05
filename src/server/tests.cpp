#include "./headers/tests.h"
#include "./headers/recogniser.h"


Tests::Tests() {}

Tests::Tests(Table _table) {
    testTable = _table;
}

void Tests::runTests(Table recognisedTable, Images image) {
    Tests test(recognisedTable);

    switch (image) {
    case Images::testImg0:
        test.validateTable(1, 1);
        break;
    case Images::testImg1:
        test.validateTable(5, 2);
        break;
    case Images::testImg2: 
        test.validateTable(4, 1);
        break;
    case Images::testImg3:
        test.validateTable(4, 4);
        break;
    case Images::list:
        test.validateTable(19, 16);
        break;
    default:
        break;
    }
}

void Tests::validateTable(int colNum, int rowNum) {
    std::cout << "correct table: " << colNum << "x" << rowNum << std::endl;
    std::cout << "recognised table: " << testTable.getColNum() << "x" << testTable.getRowNum() << std::endl;

    if (testTable.getColNum() == colNum && testTable.getRowNum() == rowNum) {
        std::cout << "test passed\n";

        return;
    }

    std::cout << "test loosed\n";
}