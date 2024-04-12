#pragma once
#include "opencv2/opencv.hpp"
#include "./table.h"


// google test
class Recogniser {
    private:

    public:
        Recogniser();
        virtual Table recognise(cv::Mat frame);
};