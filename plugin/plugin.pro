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

INCLUDEPATH += $$PWD/../googlepinyin

win32{
    CONFIG      += debug_and_release build_all

    CONFIG(debug, debug|release){
        TARGET  = ../../debug/platformInputContexts/$$join(TARGET,,,d)
        LIBS    += -L$$PWD/googlepinyin/ -lgooglepinyind
    }CONFIG(release, debug|release){
        TARGET  = ../../release/platformInputContexts/$$TARGET
        LIBS    += -L$$PWD/googlepinyin/ -lgooglepinyin
    }
}
unix{
    LIBS        += -L$$PWD/../build/lib/googlepinyin -lgooglepinyin

    DESTDIR     = $$PWD/../build/bin/platforminputcontexts

    MOC_DIR     = $$PWD/../build/plugin/moc
    RCC_DIR     = $$PWD/../build/plugin/res
    UI_DIR      = $$PWD/../build/plugin/ui
    OBJECTS_DIR = $$PWD/../build/plugin/obj
}

RESOURCES += \
    res.qrc
