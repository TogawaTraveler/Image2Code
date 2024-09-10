#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QVBoxLayout"
#include "QLabel"
#include "opencv2/opencv.hpp"
#include "QFileDialog"
#include "cvprocess.h"
#include "QDebug"
#include <QTimer>
#include "QSerialPortInfo"
#include "QMessageBox"
CVProcess* Process = new CVProcess;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    rowImage = new QImage();
    tempImage = new QImage();
    cannyImage = new QImage();
    binarizedImage = new QImage();
    skeletonImage = new QImage();
    grayImage = new QImage();
    boundaryImage = new QImage();
    rowImage->load(":/resource/93388262_p8.jpg");
    tempImage->load(":/resource/93388262_p8.jpg");
    skeletonImage->load(":/resource/93388262_p8.jpg");
    rowMat = Process->QImage2Mat(*rowImage);
    unity_udp = new QUdpSocket(this);//unity传输数据
    ui->setupUi(this);
    QStringList serialNamePort;
    serialPort = new QSerialPort(this);
    connect(serialPort,SIGNAL(readyRead()),this,SLOT(Datadeal()));
    foreach (const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        serialNamePort<<info.portName();
    }
    ui->com->addItems(serialNamePort);
    ui->scaled->setRange(0,100);
    ui->threshold1->setRange(0,100);
    ui->threshold1->setRange(0,100);
    ui->boundaryCheck->setCheckState(Qt::Checked);
    drawMode = DrawBoundary;
    ui->scaled->setValue(50);
    ui->imageDisplay->setAlignment(Qt::AlignCenter);
    ui->codeOutput->document()->setMaximumBlockCount(1000);
    timer = startTimer(6);
    f = new QFile("code.txt");
    drawFlag = 0;
    //

    //
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::Datadeal()
{


}

void MainWindow::on_chooseFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,QStringLiteral("choose file"),"C:",QStringLiteral("picture(*png *jpg)"));
    if(fileName!=NULL)
    {
        rowImage->load(fileName);
        *tempImage = rowImage->scaled(rowImage->width()*ui->scaled->value()/100,rowImage->height()*ui->scaled->value()/100,Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        tempMat = Process->QImage2Mat(*tempImage);
        ui->imageDisplay->setPixmap(QPixmap::fromImage(*tempImage));
        rowMat = Process->QImage2Mat(*tempImage);
    }
    else
        qDebug() << ("没有打开文件");

}


void MainWindow::on_scaled_valueChanged(int value)
{
    *tempImage = rowImage->scaled(rowImage->width()*ui->scaled->value()/100,rowImage->height()*ui->scaled->value()/100,Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    tempMat = Process->QImage2Mat(*tempImage);
    ui->imageDisplay->setPixmap(QPixmap::fromImage(*tempImage));
}


void MainWindow::on_spawnLine_clicked()
{
    if(drawMode == DrawBoundary)
    {
        cannyMat = Process->Canny(tempMat,ui->threshold1->value()*10,ui->threshold2->value()*10);
        boundaryMat = Process->findLine(cannyMat);
        *boundaryImage = Process->Mat2QImage(boundaryMat);
        ui->imageDisplay->setPixmap(QPixmap::fromImage(*boundaryImage));
    }
    else
    {
        binarizedMat = Process->rgb2binarized(tempMat);
        skeletonMat = binarizedMat;
        cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
        Process->chaoThinimage(skeletonMat);
        skeletonMat = Process->findLine(skeletonMat);
        *skeletonImage = Process->Mat2QImage(skeletonMat);
        ui->imageDisplay->setPixmap(QPixmap::fromImage(*skeletonImage));
    }

}


void MainWindow::on_beginDraw_clicked()
{
    drawFlag = 1;
    ui->codeOutput->clear();
    if(!f->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << ("打开文件失败");
        drawFlag = 0;
    }
    if(drawMode == DrawBoundary)
        actMat = cv::Mat(cannyMat.size(),CV_8UC3, cv::Scalar(255,255,255));
    else
        actMat = cv::Mat(skeletonMat.size(),CV_8UC3, cv::Scalar(255,255,255));

}
void MainWindow::timerEvent(QTimerEvent *event)
{
    static bool penFlag = 0;
    static cv::Point p1,p2;
    int x,y;
    QString xs,ys;
    if(event->timerId() == timer)
    {
        if(drawFlag)
        {
            static QTextStream txtInput(f);
            QString lineStr;
            cv::Scalar color;
            if(!txtInput.atEnd())
            {
                lineStr = txtInput.readLine();
                serialPort->write(lineStr.toLocal8Bit());
                qDebug()<<lineStr<<endl;
                unity_udp->writeDatagram(lineStr.toUtf8(),QHostAddress("127.0.0.1"),2333);//主机地址
                ui->codeOutput->append(lineStr);
                if(lineStr == "Up")
                    penFlag = 0;
                else if(lineStr == "Down")
                    penFlag = 1;
                else
                {
                    xs = lineStr.mid(1,3);
                    ys = lineStr.mid(5,3);
                    x = xs.toInt();
                    y = ys.toInt();
                    p1.x = x;
                    p1.y = y;
                    if(penFlag)
                        color = cv::Scalar(0, 0, 255);
                    else
                        color = cv::Scalar(0, 255, 0);
                    cv::line(actMat,p1,p2,color,1,cv::LINE_8);

//                    qDebug()<<"x="<<x<<"y="<<y<<endl;
                }
                p2.x = p1.x;
                p2.y = p1.y;
                ui->imageDisplay->setPixmap(QPixmap::fromImage(Process->Mat2QImage(actMat)));
            }
            else
            {
                p2.x = boundaryImage->size().width();
                p2.y = boundaryImage->size().height();
                drawFlag = 0;
                f->close();
            }
        }
    }

}


void MainWindow::on_boundaryCheck_released()
{
    if(ui->boundaryCheck->checkState() == Qt::Checked)
    {
        ui->skeletonCheck->setCheckState(Qt::Unchecked);
        drawMode = DrawBoundary;
    }
    else
    {
        ui->skeletonCheck->setCheckState(Qt::Checked);
        drawMode = DrawSkeleton;
    }
    if(drawMode == DrawSkeleton)
    {
        binarizedMat = Process->rgb2binarized(tempMat);
        *binarizedImage = Process->Mat2QImage(Process->reverse(binarizedMat));
        ui->imageDisplay->setPixmap(QPixmap::fromImage(*binarizedImage));
    }
    if(drawMode == DrawBoundary)
    {
        cannyMat = Process->Canny(tempMat,ui->threshold1->value()*10,ui->threshold2->value()*10);
        *cannyImage = Process->Mat2QImage(Process->reverse(cannyMat));
        ui->imageDisplay->setPixmap(QPixmap::fromImage(*cannyImage));
    }
}


void MainWindow::on_skeletonCheck_released()
{
    if(ui->skeletonCheck->checkState() == Qt::Checked)
    {
        ui->boundaryCheck->setCheckState(Qt::Unchecked);
        drawMode = DrawSkeleton;
    }
    else
    {
        ui->boundaryCheck->setCheckState(Qt::Checked);
        drawMode = DrawBoundary;
    }
    if(drawMode == DrawSkeleton)
    {
        binarizedMat = Process->rgb2binarized(tempMat);
        *binarizedImage = Process->Mat2QImage(Process->reverse(binarizedMat));
        ui->imageDisplay->setPixmap(QPixmap::fromImage(*binarizedImage));
    }
    if(drawMode == DrawBoundary)
    {
        cannyMat = Process->Canny(tempMat,ui->threshold1->value()*10,ui->threshold2->value()*10);
        *cannyImage = Process->Mat2QImage(Process->reverse(cannyMat));
        ui->imageDisplay->setPixmap(QPixmap::fromImage(*cannyImage));
    }
}


void MainWindow::on_threshold1_valueChanged(int value)
{
    cannyMat = Process->Canny(tempMat,ui->threshold1->value()*10,ui->threshold2->value()*10);
    *cannyImage = Process->Mat2QImage(Process->reverse(cannyMat));
    if(drawMode == DrawBoundary)
        ui->imageDisplay->setPixmap(QPixmap::fromImage(*cannyImage));
}


void MainWindow::on_threshold2_valueChanged(int value)
{
    cannyMat = Process->Canny(tempMat,ui->threshold1->value()*10,ui->threshold2->value()*10);
    *cannyImage = Process->Mat2QImage(Process->reverse(cannyMat));
    if(drawMode == DrawBoundary)
        ui->imageDisplay->setPixmap(QPixmap::fromImage(*cannyImage));
}


void MainWindow::on_comConnect_clicked()
{
    serialPort->setPortName(ui->com->currentText());
    serialPort->setBaudRate(QSerialPort::Baud115200);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setParity(QSerialPort::NoParity);
    if(serialPort->open(QIODevice::ReadWrite) == true){

    }else{
        QMessageBox::critical(this,"提示","失败");
    }
}

