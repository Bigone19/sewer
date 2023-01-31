QT       += core sql concurrent network gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    sewerclient.cpp \
    onnxDetector.cpp \
    onnxConfig.cpp

HEADERS += \
    sewerclient.h \
    onnxDetector.h \
    onnxConfig.h

FORMS += \
    sewerclient.ui

TRANSLATIONS += \
    sewer_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

INCLUDEPATH+=../opencv/build/include \
             ../opencv/build/include/opencv \
             ../opencv/build/include/opencv2 \
             ../Microsoft.ML.OnnxRuntime.1.10.0/build/native/include
DEPENDPATH+=../opencv/build/include \
            ../opencv/build/include/opencv \
            ../opencv/build/include/opencv2 \
            ../Microsoft.ML.OnnxRuntime.1.10.0/build/native/include
LIBS += -L../opencv/build/x64/vc15/lib \
        -lopencv_world452d \
        -lopencv_world452\
        -L../Microsoft.ML.OnnxRuntime.1.10.0/runtimes/win-x64/native \
        -lonnxruntime

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
