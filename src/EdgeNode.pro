TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Node.cpp \
    Edge.cpp \
    Geometry.cpp \
    Triangle.cpp \
    AdvancingFront.cpp

HEADERS += \
    Node.h \
    global.h \
    Edge.h \
    Geometry.h \
    Triangle.h \
    AdvancingFront.h
