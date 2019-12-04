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

CONFIG      += debug_and_release build_all

CONFIG(debug, debug|release){
    TARGET  = ../../window/debug/platformInputContexts/$$join(TARGET,,,d)
    LIBS    += -L$$PWD/googlepinyin/ -lgooglepinyind
}CONFIG(release, debug|release){
    TARGET  = ../../window/release/platformInputContexts/$$TARGET
    LIBS    += -L$$PWD/googlepinyin/ -lgooglepinyin
}
