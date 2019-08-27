#-------------------------------------------------
#
# Project created by QtCreator 2019-08-27T14:48:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QController-LegalAssistant
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        Controller-LegalAssistant/controllerHandler/CController.cpp \
        Controller-LegalAssistant/mainwindowlegalassistant.cpp \
        Global/application/CApplication.cpp \
        Global/cmpHandler/CCmpHandler.cpp \
        Global/configHandler/CConfig.cpp \
        Global/configHandler/CConfigHandler.cpp \
        Global/dataHandler/CDataHandler.cpp \
        Global/logHandler/LogHandler.cpp \
        Global/messageHandler/CMessageHandler.cpp \
        Global/objectHandler/CObject.cpp \
        Global/objectHandler/CThread.cpp \
        Global/objectHandler/CTimer.cpp \
        Global/objectHandler/Handler.cpp \
        Global/processHandler/CProcessHandler.cpp \
        Global/protocolHandler/CCmpClient.cpp \
        Global/protocolHandler/CCmpServer.cpp \
        Global/socketHandler/CATcpClient.cpp \
        Global/socketHandler/CATcpServer.cpp \
        Global/socketHandler/CDomainServer.cpp \
        Global/socketHandler/CSocket.cpp \
        Global/socketHandler/CSocketClient.cpp \
        Global/socketHandler/CSocketServer.cpp \
        Global/threadHandler/CThreadHandler.cpp

HEADERS += \
        Controller-LegalAssistant/controllerHandler/CController.h \
        Controller-LegalAssistant/mainwindowlegalassistant.h \
        Global/application/CApplication.h \
        Global/application/Message.h \
        Global/cmpHandler/CCmpHandler.h \
        Global/configHandler/CConfig.h \
        Global/configHandler/CConfigHandler.h \
        Global/dataHandler/CDataHandler.h \
        Global/global_inc/ICallback.h \
        Global/global_inc/common.h \
        Global/global_inc/container.h \
        Global/global_inc/dataType.h \
        Global/global_inc/event.h \
        Global/global_inc/packet.h \
        Global/global_inc/utf8.h \
        Global/global_inc/utility.h \
        Global/logHandler/LogHandler.h \
        Global/messageHandler/CMessageHandler.h \
        Global/objectHandler/CObject.h \
        Global/objectHandler/CThread.h \
        Global/objectHandler/CTimer.h \
        Global/objectHandler/Handler.h \
        Global/processHandler/CProcessHandler.h \
        Global/protocolHandler/CCmpClient.h \
        Global/protocolHandler/CCmpServer.h \
        Global/socketHandler/CATcpClient.h \
        Global/socketHandler/CATcpServer.h \
        Global/socketHandler/CDomainServer.h \
        Global/socketHandler/CSocket.h \
        Global/socketHandler/CSocketClient.h \
        Global/socketHandler/CSocketServer.h \
        Global/socketHandler/IReceiver.h \
        Global/threadHandler/CThreadHandler.h

INCLUDEPATH += \
        Controller-LegalAssistant/controllerHandler \
        Controller-LegalAssistant \
        Global/application \
        Global/messageHandler \
        Global/logHandler \
        Global/objectHandler \
        Global/processHandler \
        Global/socketHandler \
        Global/global_inc \
        Global/dataHandler \
        Global/configHandler \
        Global/cmpHandler \
        Global/threadHandler

LIBS += -lrt
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    Controller-LegalAssistant/mainwindowlegalassistant.ui

# copies the given files to the destination directory
defineTest(copyToDestDir) {
    files = $$1
    dir = $$2
    # replace slashes in destination path for Windows
    win32:dir ~= s,/,\\,g

    for(file, files) {
        # replace slashes in source path for Windows
        win32:file ~= s,/,\\,g

        QMAKE_POST_LINK += $$QMAKE_COPY_DIR $$shell_quote($$file) $$shell_quote($$dir) $$escape_expand(\\n\\t)
    }

    export(QMAKE_POST_LINK)
}

copyToDestDir($$PWD/Controller-LegalAssistant/QController-LegalAssistant.conf, $$PWD/Controller-LegalAssistant/bin)
