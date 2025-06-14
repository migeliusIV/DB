QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    broker.cpp \
    centrdepwindow.cpp \
    database.cpp \
    empldirector.cpp \
    emploperator.cpp \
    main.cpp \
    mainwindow.cpp \
    passwchange.cpp

HEADERS += \
    broker.h \
    centrdepwindow.h \
    database.h \
    empldirector.h \
    emploperator.h \
    mainwindow.h \
    passwchange.h

FORMS += \
    broker.ui \
    centrdepwindow.ui \
    empldirector.ui \
    emploperator.ui \
    mainwindow.ui \
    passwchange.ui

TRANSLATIONS += \
    kr_ru_RU.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
