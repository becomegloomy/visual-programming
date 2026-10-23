QT += gui widgets

TEMPLATE = lib
DEFINES += LIB_CHESS_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chesswidget.cpp

HEADERS += \
    lib_chess_global.h \
    chesswidget.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

FORMS += \
    chesswidget.ui

RESOURCES += \
    pick.qrc
