QT          += gui-private widgets

TEMPLATE    = lib
TARGET      = tgtsmlInputContextPlugin

LIBS        += -L$$PWD/googlepinyin/ -lgooglepinyin
INCLUDEPATH += $$PWD/googlepinyin

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

