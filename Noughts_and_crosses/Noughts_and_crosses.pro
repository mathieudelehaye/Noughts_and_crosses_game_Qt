QT       += core gui \
    quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    clickablelabel.cpp \
    gamereferee.cpp \
    gameview.cpp \
    homeview.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    clickablelabel.h \
    gamereferee.h \
    gameview.h \
    homeview.h \
    mainwindow.h

TRANSLATIONS += \
    Noughts_and_crosses_en_GB.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    cross-01.png \
    nought-01.png
