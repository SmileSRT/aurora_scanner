#include "opencv2/opencv.hpp"
#include <rapidjson/document.h>
#include <vector>
#include "httplib.h"
#include "./headers/server.h"

using namespace cv;

void restThread() {
    RestServer test;
    test.start();
}

int main(int, char**) {
    VideoCapture cap(0); // Открываем камеру или файл

    std::thread th(restThread);

    if(!cap.isOpened()) { 
        return -1; // check if we succeeded
    } 

    Mat edges;
    namedWindow("edges",1);

    while(1) {
        Mat frame;
        cap >> frame; // get a new frame from camera
        cvtColor(frame, edges, COLOR_BGR2GRAY); // Перевод в градации серого
        GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5); // Размытие
        Canny(edges, edges, 0, 30, 3); // Выделение границ

        std::vector<Vec4i> lines; // Создать вектор для хранения линий
        
        HoughLinesP(edges, lines, 1, CV_PI/180, 100, 10, 250); // Выполнить преобразование хафа

        for (size_t i=0; i<lines.size(); i++) {
            Vec4i l = lines[i];
            
            line(edges, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 0, 0), 3, LINE_AA);
        }

        if(waitKey(30) >= 0) break;

        imshow("edges", edges);
    }

    return 0;
}