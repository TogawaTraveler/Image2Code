#include "cvprocess.h"
#include "QDebug"
#include "QThread"
#include "QFile"
#include "QString"
CVProcess::CVProcess()
{

}
CVProcess::~CVProcess(void)
{

}
cv::Mat CVProcess::QImage2Mat(QImage image)
{
    cv::Mat mat;
    switch(image.format())
    {
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied:
        mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
        break;
    case QImage::Format_RGB888:
        mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
        cv::cvtColor(mat,mat,cv::COLOR_RGB2BGR);
        break;
    case QImage::Format_Indexed8:
        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
        break;
    }
    return mat;
}

QImage CVProcess::Mat2QImage(cv::Mat mat)
{
    if(mat.type() == CV_8UC1)
    {
        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
        image.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        uchar *pSrc = mat.data;
        for(int row = 0; row < mat.rows; row ++)
        {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }
        return image;
    }
    else if(mat.type() == CV_8UC3)
    {
        const uchar *pSrc = (const uchar*)mat.data;
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    else if(mat.type() == CV_8UC4)
    {
        const uchar *pSrc = (const uchar*)mat.data;
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        return image.copy();
    }
    else
    {
        return QImage();
    }
}


cv::Mat CVProcess::Canny(cv::Mat inputMat,int threshold1,int threshold2)//边界提取 输入缩放后图像/阈值
{
    cv::Mat frame,notMat;
    cv::Mat foreground;
    cv::Mat background;
    cv::Mat zoomin,zoomout;
    std::vector<cv::Vec4i> g_vHierarchy;
    cv::Mat lpls = (cv::Mat_<char>(3,3)<<
                0,-1,0,
                -1,4,-1,
                0,-1,0);
    cv::Mat lplsp = (cv::Mat_<char>(3,3)<<
                0,-1,0,
                -1,4,-1,
                0,-1,0);
    cv::Mat sobely = (cv::Mat_<char>(3,3)<<
                -1,0,1,
                -2,0,2,
                -1,0,1);
    cv::Mat sobelx = (cv::Mat_<char>(3,3)<<
                1,0,-1,
                2,0,-2,
                1,0,-1);
    frame = inputMat;
    cvtColor(frame,frame,cv::COLOR_BGR2GRAY);
    /*process begin*/
//    cv::resize(frame,zoomin,cv::Size(width,height),0,0,cv::INTER_LINEAR);
//    cv::flip(frame,frame,1);
//    cv::filter2D(frame,frame,frame.depth(),sobelx);
//    cv::filter2D(frame,frame,frame.depth(),sobely);
    cv::Canny(frame,frame,threshold1,threshold2,3);
    /*process end*/
    cv::bitwise_not(frame,notMat);
    return frame;
}


cv::Mat CVProcess::findLine(cv::Mat matCanny)
{
    cv::Mat boundaryMat;
    boundaryMat = cv::Mat(matCanny.size(),CV_8UC3, cv::Scalar(255,255,255));
    QFile f("code.txt");
    if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << ("打开文件失败");
    }
    QTextStream txtOutput(&f);
    QString str;
    std::vector<std::vector<cv::Point>> contours,min,temp;
    std::vector<cv::Vec4i> hierarchy,hierarchy2;
    cv::findContours(matCanny,contours,hierarchy,cv::RETR_LIST,cv::CHAIN_APPROX_SIMPLE,cv::Point(0,0));
    copy(contours.begin(), contours.end(), std::back_inserter(min));
    copy(contours.begin(), contours.end(), std::back_inserter(temp));
    for(int i = 0;i<contours.size()-1;i++)
    {
        double minDinstance = getDistnce(contours[i][contours[i].size()-1],contours[i+1][0]);
        int minNumb = i+1;
        for(int j = i+2;j<contours.size();j++)
        {
           double distance = getDistnce(contours[i][contours[i].size()-1],contours[j][0]);
           if(distance < minDinstance)
           {
               minDinstance = distance;
               minNumb = j;
           }
        }
        min[i+1] = contours[minNumb];
        temp[i+1] = contours[i+1];
        contours[i+1] = contours[minNumb];
        contours[minNumb] = temp[i+1];
    }
    for(int i = 0;i<contours.size();i++)
    {
        str = "Up";
        txtOutput << str << endl;
//        qDebug()<<str<<endl;
        for(int j = 0;j<contours[i].size();j++)
        {
            str.sprintf("X%03dY%03d",contours[i][j].x,contours[i][j].y);
            txtOutput << str << endl;
//            qDebug()<<str<<endl;
            if(j == 0)
            {
                str = "Down";
                txtOutput << str << endl;
//                qDebug()<<str<<endl;
            }
        }
        cv::Scalar color = cv::Scalar(0,0,255);
        cv::drawContours(boundaryMat,contours,i,color,1,8,hierarchy,0,cv::Point());
    }
    str = "Up";
    txtOutput << str << endl;
//    qDebug()<<str<<endl;
    f.close();
    return boundaryMat;
}

double CVProcess::getDistnce(cv::Point p1, cv::Point p2)
{
    double distance;
    distance = (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
    return distance;
}

cv::Mat CVProcess::rgb2binarized(cv::Mat inputMat)
{
    cv::Mat gray,buleMat1,adapMat,buleMat2,threMat,binarizedMat;
    cv::cvtColor(inputMat,gray,cv::COLOR_BGR2GRAY);
//    cv::GaussianBlur(gray,buleMat1,cv::Size(5, 5), 0);
    cv::adaptiveThreshold(gray,adapMat,255,cv::ADAPTIVE_THRESH_GAUSSIAN_C,cv::THRESH_BINARY,127,20);
//    cv::GaussianBlur(adapMat,buleMat2,cv::Size(5, 5), 0);
//    cv::threshold(buleMat2,threMat,200,255,cv::THRESH_BINARY);
    cv::bitwise_not(adapMat,binarizedMat);
    return binarizedMat;
}


void CVProcess::chaoThinimage(cv::Mat &srcimage)//单通道、二值化后的图像
{
    std::vector<cv::Point> deletelist1;
    int Zhangmude[9];
    int nl = srcimage.rows;
    int nc = srcimage.cols;
    while (true)
    {
        for (int j = 1; j<(nl - 1); j++)
        {
            uchar* data_last = srcimage.ptr<uchar>(j - 1);
            uchar* data = srcimage.ptr<uchar>(j);
            uchar* data_next = srcimage.ptr<uchar>(j + 1);
            for (int i = 1; i<(nc - 1); i++)
            {
                if (data[i] == 255)
                {
                    Zhangmude[0] = 1;
                    if (data_last[i] == 255) Zhangmude[1] = 1;
                    else  Zhangmude[1] = 0;
                    if (data_last[i + 1] == 255) Zhangmude[2] = 1;
                    else  Zhangmude[2] = 0;
                    if (data[i + 1] == 255) Zhangmude[3] = 1;
                    else  Zhangmude[3] = 0;
                    if (data_next[i + 1] == 255) Zhangmude[4] = 1;
                    else  Zhangmude[4] = 0;
                    if (data_next[i] == 255) Zhangmude[5] = 1;
                    else  Zhangmude[5] = 0;
                    if (data_next[i - 1] == 255) Zhangmude[6] = 1;
                    else  Zhangmude[6] = 0;
                    if (data[i - 1] == 255) Zhangmude[7] = 1;
                    else  Zhangmude[7] = 0;
                    if (data_last[i - 1] == 255) Zhangmude[8] = 1;
                    else  Zhangmude[8] = 0;
                    int whitepointtotal = 0;
                    for (int k = 1; k < 9; k++)
                    {
                        whitepointtotal = whitepointtotal + Zhangmude[k];
                    }
                    if ((whitepointtotal >= 2) && (whitepointtotal <= 6))
                    {
                        int ap = 0;
                        if ((Zhangmude[1] == 0) && (Zhangmude[2] == 1)) ap++;
                        if ((Zhangmude[2] == 0) && (Zhangmude[3] == 1)) ap++;
                        if ((Zhangmude[3] == 0) && (Zhangmude[4] == 1)) ap++;
                        if ((Zhangmude[4] == 0) && (Zhangmude[5] == 1)) ap++;
                        if ((Zhangmude[5] == 0) && (Zhangmude[6] == 1)) ap++;
                        if ((Zhangmude[6] == 0) && (Zhangmude[7] == 1)) ap++;
                        if ((Zhangmude[7] == 0) && (Zhangmude[8] == 1)) ap++;
                        if ((Zhangmude[8] == 0) && (Zhangmude[1] == 1)) ap++;
                        if (ap == 1)
                        {
                            if ((Zhangmude[1] * Zhangmude[7] * Zhangmude[5] == 0) && (Zhangmude[3] * Zhangmude[5] * Zhangmude[7] == 0))
                            {
                                deletelist1.push_back(cv::Point(i, j));
                            }
                        }
                    }
                }
            }
        }
        if (deletelist1.size() == 0) break;
        for (size_t i = 0; i < deletelist1.size(); i++)
        {
            cv::Point tem;
            tem = deletelist1[i];
            uchar* data = srcimage.ptr<uchar>(tem.y);
            data[tem.x] = 0;
        }
        deletelist1.clear();

        for (int j = 1; j<(nl - 1); j++)
        {
            uchar* data_last = srcimage.ptr<uchar>(j - 1);
            uchar* data = srcimage.ptr<uchar>(j);
            uchar* data_next = srcimage.ptr<uchar>(j + 1);
            for (int i = 1; i<(nc - 1); i++)
            {
                if (data[i] == 255)
                {
                    Zhangmude[0] = 1;
                    if (data_last[i] == 255) Zhangmude[1] = 1;
                    else  Zhangmude[1] = 0;
                    if (data_last[i + 1] == 255) Zhangmude[2] = 1;
                    else  Zhangmude[2] = 0;
                    if (data[i + 1] == 255) Zhangmude[3] = 1;
                    else  Zhangmude[3] = 0;
                    if (data_next[i + 1] == 255) Zhangmude[4] = 1;
                    else  Zhangmude[4] = 0;
                    if (data_next[i] == 255) Zhangmude[5] = 1;
                    else  Zhangmude[5] = 0;
                    if (data_next[i - 1] == 255) Zhangmude[6] = 1;
                    else  Zhangmude[6] = 0;
                    if (data[i - 1] == 255) Zhangmude[7] = 1;
                    else  Zhangmude[7] = 0;
                    if (data_last[i - 1] == 255) Zhangmude[8] = 1;
                    else  Zhangmude[8] = 0;
                    int whitepointtotal = 0;
                    for (int k = 1; k < 9; k++)
                    {
                        whitepointtotal = whitepointtotal + Zhangmude[k];
                    }
                    if ((whitepointtotal >= 2) && (whitepointtotal <= 6))
                    {
                        int ap = 0;
                        if ((Zhangmude[1] == 0) && (Zhangmude[2] == 1)) ap++;
                        if ((Zhangmude[2] == 0) && (Zhangmude[3] == 1)) ap++;
                        if ((Zhangmude[3] == 0) && (Zhangmude[4] == 1)) ap++;
                        if ((Zhangmude[4] == 0) && (Zhangmude[5] == 1)) ap++;
                        if ((Zhangmude[5] == 0) && (Zhangmude[6] == 1)) ap++;
                        if ((Zhangmude[6] == 0) && (Zhangmude[7] == 1)) ap++;
                        if ((Zhangmude[7] == 0) && (Zhangmude[8] == 1)) ap++;
                        if ((Zhangmude[8] == 0) && (Zhangmude[1] == 1)) ap++;
                        if (ap == 1)
                        {
                            if ((Zhangmude[1] * Zhangmude[3] * Zhangmude[5] == 0) && (Zhangmude[3] * Zhangmude[1] * Zhangmude[7] == 0))
                            {
                                deletelist1.push_back(cv::Point(i, j));
                            }
                        }
                    }
                }
            }
        }
        if (deletelist1.size() == 0) break;
        for (size_t i = 0; i < deletelist1.size(); i++)
        {
            cv::Point tem;
            tem = deletelist1[i];
            uchar* data = srcimage.ptr<uchar>(tem.y);
            data[tem.x] = 0;
        }
        deletelist1.clear();
    }
}

cv::Mat CVProcess::reverse(cv::Mat inputMat)
{
    cv::Mat output;
    cv::bitwise_not(inputMat,output);
    return output;
}
