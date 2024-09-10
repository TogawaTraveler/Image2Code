#ifndef CVPROCESS_H
#define CVPROCESS_H

#endif // CVPROCESS_H
#include "QLabel"
#include "opencv2/opencv.hpp"
class CVProcess
{
public:
    CVProcess(void);
    ~CVProcess(void);
    cv::Mat QImage2Mat(QImage image);
    QImage Mat2QImage(cv::Mat mat);
    cv::Mat Canny(cv::Mat inputMat,int threshold1,int threshold2);
    cv::Mat findLine(cv::Mat matCanny);
    double getDistnce(cv::Point p1,cv::Point p2);
    cv::Mat rgb2binarized(cv::Mat inputMat);
    void chaoThinimage(cv::Mat &srcimage);
    cv::Mat reverse(cv::Mat inputMat);
//    void getRGBThreshold(uint8_t rmax,uint8_t rmin,uint8_t g_max,uint8_t g_min,uint8_t b_max,uint8_t b_min,)
private:


};
