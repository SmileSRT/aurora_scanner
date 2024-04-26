#include "./headers/recogniser.h"


Recogniser::Recogniser () {};

Table Recogniser::recognise(cv::Mat frame) {
    // to print lines
    // cv::Mat cdst(600, 1200, CV_8UC3, cv::Scalar(0, 0, 0));

    // an algorithm to define whether
    // line is vertical or horizontal
    int rows = 0, cols = 0;
    for (size_t i = 0; i < frame.rows - 1; i++) {
        int dx = abs(frame.at<double>(i+1, 0) - frame.at<double>(i, 0));
        int dy = abs(frame.at<double>(i+1, 1) - frame.at<double>(i, 1));

        if ((dx > dy) && (dy <= 5)) {
            rows++;
        } else if ((dy > dx) && (dx <= 5)) {
            cols++;
        } else continue;

        // to print lines
        // cv::Point2d pt1 = cv::Point(frame.at<double>(i, 0), frame.at<double>(i, 1));
        // cv::Point2d pt2 = cv::Point(frame.at<double>(i+1, 0), frame.at<double>(i+1, 1));

        // cv::line(cdst, pt1, pt2, cv::Scalar(0, 0, 255), 2, cv::LINE_AA);
        // cv::imshow("image", cdst);
    }
    // cv::waitKey(0);

    std::cout << "rows: " << rows << std::endl << "cols: " << cols << std::endl;

    Table table(0, 0);
    table.setNewColNum(cols);
    table.setNewRowNum(rows);
    
    return table;
};

cv::Mat Recogniser::getCell(int col, int row) {};

bool Recogniser::isEmptyCell(int col, int row) {
    return false;
};
bool Recogniser::isEmptyCellImg(cv::Mat m) {
    return false;
};