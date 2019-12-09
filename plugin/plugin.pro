QT          = core gui-private widgets

TEMPLATE    = lib
TARGET      = tgtsmlInputContextPlugin

HEADERS     += \
            tgtsmlplatforminputcontextplugin.h \
            tgtsmlplatforminputcontext.h \
            keyboardform.h

SOURCES     += \
            tgtsmlplatforminputcontextplugin.cpp \
            tgtsmlplatforminputcontext.cpp \
            keyboardform.cpp

RESOURCES   += \
            res.qrc

INCLUDEPATH += $$PWD/googlepinyin

win32{
    CONFIG      += debug_and_release build_all

    CONFIG(debug, debug|release){
        TARGET  = ../../testWindow/debug/platformInputContexts/$$join(TARGET,,,d)
        LIBS    += -L$$PWD/googlepinyin/ -lgooglepinyind
    }CONFIG(release, debug|release){
        TARGET  = ../../testWindow/release/platformInputContexts/$$TARGET
        LIBS    += -L$$PWD/googlepinyin/ -lgooglepinyin
    }
}
unix{
    TARGET      = ../target/$$TARGET
    LIBS        += -L$$PWD/googlepinyin/ -lgooglepinyin
    MOC_DIR     = ../tmpfiles
    RCC_DIR     = ../tmpfiles
    UI_DIR      = ../tmpfiles
    OBJECTS_DIR = ../tmpfiles
}
