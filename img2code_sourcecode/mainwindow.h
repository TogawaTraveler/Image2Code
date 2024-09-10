#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QFile"
#include "opencv2/opencv.hpp"
#include <QUdpSocket>
#include "QSerialPort"
#define DrawBoundary 0
#define DrawSkeleton 1
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int timer;
    bool drawFlag;
    bool drawMode;
    QFile *f;
    cv::Mat actMat;
    QImage *rowImage;
    QImage *tempImage;
    QImage *cannyImage;
    QImage *binarizedImage;
    QImage *skeletonImage;
    QImage *grayImage;
    QImage *boundaryImage;
    cv::Mat tempMat;
    cv::Mat cannyMat;
    cv::Mat boundaryMat;
    cv::Mat grayMat;
    cv::Mat binarizedMat;
    cv::Mat skeletonMat;
    cv::Mat rowMat;
    cv::Mat notMat;


    cv::Mat onnxMat;
    cv::Mat predict;
    QSerialPort *serialPort;
private slots:


    void on_chooseFile_clicked();

    void on_scaled_valueChanged(int value);

    void on_spawnLine_clicked();

    void on_beginDraw_clicked();

    void on_boundaryCheck_released();

    void on_skeletonCheck_released();

    void on_threshold1_valueChanged(int value);

    void on_threshold2_valueChanged(int value);

    void Datadeal();

    void on_comConnect_clicked();

protected:
    virtual void timerEvent(QTimerEvent *event);

private:
    Ui::MainWindow *ui;
    QUdpSocket* unity_udp;
};
#endif // MAINWINDOW_H
