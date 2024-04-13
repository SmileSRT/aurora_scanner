#include "./headers/tests.h"
#include "./headers/recogniser.h"

Tests::Tests() {}

Tests::Tests(Table _table) {
    testTable = _table;
}

void Tests::runTests(cv::Mat frame, int numberImg) {
    Recogniser testRecognise;
    Table tableForTest = testRecognise.recognise(frame);
    Tests test(tableForTest);

    switch (numberImg) {
    case 0:
        test.validateTable(0, 0);
        break;
    case 1:
        test.validateTable(5, 2);
        break;
    case 2: 
        test.validateTable(4, 1);
    case 3:
        test.validateTable(4, 4);

    default:
        break;
    }
}

void Tests::validateTable(int colNum, int rowNum) {
    if (testTable.getColNum() == colNum && testTable.getRowNum() == rowNum) {
        std::cout << "test passed\n";

        return;
    }

    std::cout << "test loosed\n";
}