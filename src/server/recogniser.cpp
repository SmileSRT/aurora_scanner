#include "./headers/recogniser.h"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace cv;
using namespace std;

static int getApproximatedLines(vector<Vec4i> &lines, int lineNumber) {
    int count_lines = 0;

    for (int i = 0; i < lines.size(); i++) {
        Vec4i curLine = lines[i];
        bool isTrueLine = true;

        for (int j = i + 1; j < lines.size(); j++) {
            Vec4i nextLine = lines[j];

            if (abs(curLine[lineNumber] - nextLine[lineNumber + 2]) < 20) {
                isTrueLine = false;
                break;
            }
        }

        if (isTrueLine) {
            count_lines++;
        }
    }

    return count_lines;
}

Recogniser::Recogniser () {};

Table Recogniser::recognise(cv::Mat frame) {
    Mat dst, cdstP;

    // Check if image is loaded fine
    if(frame.empty()){
        printf(" Error opening image\n");
        printf(" Program Arguments: [image_name -- default %s] \n");
        return Table(0, 0);
    }
    
    // Edge detection
    Canny(frame, dst, 50, 200, 3);
    
    // Copy edges to the images that will display the results in BGR
    cvtColor(dst, cdstP, COLOR_GRAY2BGR);
    
    // Probabilistic Line Transform
    vector<Vec4i> linesP; // will hold the results of the detection
    HoughLinesP(dst, linesP, 1, CV_PI/180, 150, 50, 5); // runs the actual detection

    vector<Vec4i> horizontal_lines;
    vector<Vec4i> vertical_lines;

    for( size_t i = 0; i < linesP.size(); i++ ) {
        Vec4i l = linesP[i];
        line( cdstP, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, LINE_AA);

        int dx = abs(l[2] - l[0]);
        int dy = abs(l[3] - l[1]);
 
        if (dx < dy) {
            vertical_lines.push_back(l);
        }
        else {
            horizontal_lines.push_back(l);
        }
    }

    int count_vercical_lines = getApproximatedLines(vertical_lines, 0);
    int count_horizontal_lines = getApproximatedLines(horizontal_lines, 1);

    int col_num = count_vercical_lines - 1;
    int row_num = count_horizontal_lines - 1;
    
    // Show results
    imshow("Source", frame);
    imshow("Detected Lines (in red) - Probabilistic Line Transform", cdstP);

    // Wait and Exit
    waitKey();

    return Table(col_num, row_num);
};

cv::Mat Recogniser::getCell(int col, int row) {};

bool Recogniser::isEmptyCell(int col, int row) {
    return false;
};
bool Recogniser::isEmptyCellImg(cv::Mat m) {
    return false;
};