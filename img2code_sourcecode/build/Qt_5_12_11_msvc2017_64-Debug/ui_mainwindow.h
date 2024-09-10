/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QSplitter *splitter_11;
    QLabel *imageDisplay;
    QSplitter *splitter_10;
    QSplitter *splitter_6;
    QPushButton *chooseFile;
    QSplitter *splitter_3;
    QLabel *label;
    QSlider *scaled;
    QSplitter *splitter_7;
    QCheckBox *boundaryCheck;
    QCheckBox *skeletonCheck;
    QSplitter *splitter_4;
    QSplitter *splitter;
    QLabel *label_2;
    QSlider *threshold1;
    QSplitter *splitter_2;
    QLabel *label_3;
    QSlider *threshold2;
    QPushButton *spawnLine;
    QSplitter *splitter_9;
    QLineEdit *port;
    QPushButton *netConnect;
    QSplitter *splitter_8;
    QComboBox *com;
    QPushButton *comConnect;
    QSplitter *splitter_5;
    QLabel *label_4;
    QTextEdit *codeOutput;
    QPushButton *beginDraw;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1200, 800);
        MainWindow->setMinimumSize(QSize(1200, 800));
        MainWindow->setMaximumSize(QSize(1200, 800));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        splitter_11 = new QSplitter(centralwidget);
        splitter_11->setObjectName(QString::fromUtf8("splitter_11"));
        splitter_11->setOrientation(Qt::Horizontal);
        imageDisplay = new QLabel(splitter_11);
        imageDisplay->setObjectName(QString::fromUtf8("imageDisplay"));
        splitter_11->addWidget(imageDisplay);
        splitter_10 = new QSplitter(splitter_11);
        splitter_10->setObjectName(QString::fromUtf8("splitter_10"));
        splitter_10->setOrientation(Qt::Vertical);
        splitter_6 = new QSplitter(splitter_10);
        splitter_6->setObjectName(QString::fromUtf8("splitter_6"));
        splitter_6->setOrientation(Qt::Vertical);
        chooseFile = new QPushButton(splitter_6);
        chooseFile->setObjectName(QString::fromUtf8("chooseFile"));
        chooseFile->setMinimumSize(QSize(200, 40));
        chooseFile->setMaximumSize(QSize(200, 40));
        splitter_6->addWidget(chooseFile);
        splitter_3 = new QSplitter(splitter_6);
        splitter_3->setObjectName(QString::fromUtf8("splitter_3"));
        splitter_3->setOrientation(Qt::Horizontal);
        label = new QLabel(splitter_3);
        label->setObjectName(QString::fromUtf8("label"));
        splitter_3->addWidget(label);
        scaled = new QSlider(splitter_3);
        scaled->setObjectName(QString::fromUtf8("scaled"));
        scaled->setMinimumSize(QSize(150, 20));
        scaled->setMaximumSize(QSize(150, 20));
        scaled->setOrientation(Qt::Horizontal);
        splitter_3->addWidget(scaled);
        splitter_6->addWidget(splitter_3);
        splitter_10->addWidget(splitter_6);
        splitter_7 = new QSplitter(splitter_10);
        splitter_7->setObjectName(QString::fromUtf8("splitter_7"));
        splitter_7->setOrientation(Qt::Horizontal);
        boundaryCheck = new QCheckBox(splitter_7);
        boundaryCheck->setObjectName(QString::fromUtf8("boundaryCheck"));
        boundaryCheck->setMinimumSize(QSize(97, 21));
        boundaryCheck->setMaximumSize(QSize(97, 21));
        splitter_7->addWidget(boundaryCheck);
        skeletonCheck = new QCheckBox(splitter_7);
        skeletonCheck->setObjectName(QString::fromUtf8("skeletonCheck"));
        skeletonCheck->setMinimumSize(QSize(97, 21));
        skeletonCheck->setMaximumSize(QSize(97, 21));
        splitter_7->addWidget(skeletonCheck);
        splitter_10->addWidget(splitter_7);
        splitter_4 = new QSplitter(splitter_10);
        splitter_4->setObjectName(QString::fromUtf8("splitter_4"));
        splitter_4->setOrientation(Qt::Vertical);
        splitter = new QSplitter(splitter_4);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        label_2 = new QLabel(splitter);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(70, 0));
        label_2->setMaximumSize(QSize(70, 16777215));
        splitter->addWidget(label_2);
        threshold1 = new QSlider(splitter);
        threshold1->setObjectName(QString::fromUtf8("threshold1"));
        threshold1->setMinimumSize(QSize(120, 20));
        threshold1->setMaximumSize(QSize(120, 20));
        threshold1->setOrientation(Qt::Horizontal);
        splitter->addWidget(threshold1);
        splitter_4->addWidget(splitter);
        splitter_2 = new QSplitter(splitter_4);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        label_3 = new QLabel(splitter_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(70, 0));
        label_3->setMaximumSize(QSize(70, 16777215));
        splitter_2->addWidget(label_3);
        threshold2 = new QSlider(splitter_2);
        threshold2->setObjectName(QString::fromUtf8("threshold2"));
        threshold2->setMinimumSize(QSize(120, 20));
        threshold2->setMaximumSize(QSize(120, 20));
        threshold2->setOrientation(Qt::Horizontal);
        splitter_2->addWidget(threshold2);
        splitter_4->addWidget(splitter_2);
        spawnLine = new QPushButton(splitter_4);
        spawnLine->setObjectName(QString::fromUtf8("spawnLine"));
        spawnLine->setMinimumSize(QSize(200, 40));
        spawnLine->setMaximumSize(QSize(200, 40));
        splitter_4->addWidget(spawnLine);
        splitter_10->addWidget(splitter_4);
        splitter_9 = new QSplitter(splitter_10);
        splitter_9->setObjectName(QString::fromUtf8("splitter_9"));
        splitter_9->setOrientation(Qt::Horizontal);
        port = new QLineEdit(splitter_9);
        port->setObjectName(QString::fromUtf8("port"));
        port->setMinimumSize(QSize(94, 31));
        port->setMaximumSize(QSize(94, 31));
        splitter_9->addWidget(port);
        netConnect = new QPushButton(splitter_9);
        netConnect->setObjectName(QString::fromUtf8("netConnect"));
        netConnect->setMinimumSize(QSize(94, 31));
        netConnect->setMaximumSize(QSize(94, 31));
        splitter_9->addWidget(netConnect);
        splitter_10->addWidget(splitter_9);
        splitter_8 = new QSplitter(splitter_10);
        splitter_8->setObjectName(QString::fromUtf8("splitter_8"));
        splitter_8->setOrientation(Qt::Horizontal);
        com = new QComboBox(splitter_8);
        com->setObjectName(QString::fromUtf8("com"));
        com->setMinimumSize(QSize(94, 31));
        com->setMaximumSize(QSize(94, 31));
        splitter_8->addWidget(com);
        comConnect = new QPushButton(splitter_8);
        comConnect->setObjectName(QString::fromUtf8("comConnect"));
        comConnect->setMinimumSize(QSize(94, 31));
        comConnect->setMaximumSize(QSize(94, 31));
        splitter_8->addWidget(comConnect);
        splitter_10->addWidget(splitter_8);
        splitter_5 = new QSplitter(splitter_10);
        splitter_5->setObjectName(QString::fromUtf8("splitter_5"));
        splitter_5->setOrientation(Qt::Vertical);
        label_4 = new QLabel(splitter_5);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(200, 15));
        label_4->setMaximumSize(QSize(200, 15));
        splitter_5->addWidget(label_4);
        codeOutput = new QTextEdit(splitter_5);
        codeOutput->setObjectName(QString::fromUtf8("codeOutput"));
        codeOutput->setMinimumSize(QSize(200, 169));
        codeOutput->setMaximumSize(QSize(200, 114514));
        codeOutput->setReadOnly(true);
        splitter_5->addWidget(codeOutput);
        beginDraw = new QPushButton(splitter_5);
        beginDraw->setObjectName(QString::fromUtf8("beginDraw"));
        beginDraw->setMinimumSize(QSize(200, 40));
        beginDraw->setMaximumSize(QSize(200, 40));
        splitter_5->addWidget(beginDraw);
        splitter_10->addWidget(splitter_5);
        splitter_11->addWidget(splitter_10);

        gridLayout->addWidget(splitter_11, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1200, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        imageDisplay->setText(QString());
        chooseFile->setText(QApplication::translate("MainWindow", "\351\200\211\346\213\251\345\233\276\347\211\207", nullptr));
        label->setText(QApplication::translate("MainWindow", "\347\274\251\346\224\276 ", nullptr));
        boundaryCheck->setText(QApplication::translate("MainWindow", "\346\217\217\350\276\271", nullptr));
        skeletonCheck->setText(QApplication::translate("MainWindow", "\345\206\231\345\255\227", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\350\276\271\347\225\214\351\230\210\345\200\2741", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "\350\276\271\347\225\214\351\230\210\345\200\2742", nullptr));
        spawnLine->setText(QApplication::translate("MainWindow", "\347\224\237\346\210\220\350\267\257\345\276\204", nullptr));
        netConnect->setText(QApplication::translate("MainWindow", "\347\275\221\347\273\234\350\277\236\346\216\245", nullptr));
        comConnect->setText(QApplication::translate("MainWindow", "\344\270\262\345\217\243\350\277\236\346\216\245", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Code Output", nullptr));
        beginDraw->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\347\273\230\347\224\273", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
