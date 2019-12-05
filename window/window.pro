QT      += core gui widgets

HEADERS += \
        window.h

SOURCES += \
        window.cpp

unix{
    TARGET      = ../target/window
    MOC_DIR     = ../tmpfiles
    RCC_DIR     = ../tmpfiles
    UI_DIR      = ../tmpfiles
    OBJECTS_DIR = ../tmpfiles
}
