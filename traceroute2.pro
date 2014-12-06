TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    common.cpp \
    NICDevices.cpp \
    traceroute.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    common.h \
    NICDevices.h \
    traceroute.h

