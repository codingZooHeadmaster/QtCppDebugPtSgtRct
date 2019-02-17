TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.cpp \
    pt.cpp \
    rct.cpp \
    sgt.cpp \
    TestPtSgt.cpp \
    TestPtSgtRct.cpp

HEADERS += \
    epsilon.h \
    pt.h \
    rct.h \
    sgt.h \
    stdafx.h
