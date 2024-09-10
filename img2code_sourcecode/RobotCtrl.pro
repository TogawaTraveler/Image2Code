QT       += core gui serialport
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cvprocess.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    cvprocess.h \
    mainwindow.h


FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += D:/OpenCV/opencv-4.8.0/build/install/include \
               D:/OpenCV/opencv-4.8.0/build/install/include/opencv2
LIBS+=D:/OpenCV/opencv-4.8.0/build/install/x64/vc16/lib/opencv_world480d.lib
LIBS+=D:/OpenCV/opencv-4.8.0/build/install/x64/vc16/lib/opencv_world480.lib

RESOURCES += \
    resource.qrc


