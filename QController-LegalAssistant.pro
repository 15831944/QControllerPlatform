#-------------------------------------------------
#
# Project created by QtCreator 2019-08-27T14:48:55
#
#-------------------------------------------------

QT       += core gui webenginewidgets webview webenginewidgets multimedia multimediawidgets texttospeech



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
        Controller-LegalAssistant/controllerHandler/CCmpWord.cpp \
        Controller-LegalAssistant/controllerHandler/CController.cpp \
        Controller-LegalAssistant/assistantwindow.cpp \
        Controller-LegalAssistant/controllerHandler/CResponsePacket.cpp \
        Controller-LegalAssistant/mainwindowlegalassistant.cpp \
        Controller-LegalAssistant/semanticHandler/CAnalysisHandler.cpp \
        Controller-LegalAssistant/semanticHandler/CSemantic.cpp \
        Controller-LegalAssistant/semanticHandler/CSemanticJudge.cpp \
        Controller-LegalAssistant/serviceHandler/CContentHandler.cpp \
        Controller-LegalAssistant/serviceHandler/CDisplayHandler.cpp \
        Controller-LegalAssistant/serviceHandler/CGamePlay.cpp \
        Controller-LegalAssistant/serviceHandler/CParticiple.cpp \
        Controller-LegalAssistant/serviceHandler/CPenReader.cpp \
        Controller-LegalAssistant/serviceHandler/CSemanticService.cpp \
        Controller-LegalAssistant/serviceHandler/CStory.cpp \
        Controller-LegalAssistant/webWidget/cwebwidget.cpp \
        Global/application/CApplication.cpp \
        Global/cmpHandler/CCmpHandler.cpp \
        Global/configHandler/CConfig.cpp \
        Global/configHandler/CConfigHandler.cpp \
        Global/dataHandler/CDataHandler.cpp \
        Global/fileHandler/CFileHandler.cpp \
        Global/httpHandler/CHttpClient.cpp \
        Global/httpHandler/CHttpsClient.cpp \
        Global/jsonHandler/JSONArray.cpp \
        Global/jsonHandler/JSONObject.cpp \
        Global/jsonHandler/cJSON.cpp \
        Global/logHandler/LogHandler.cpp \
        Global/messageHandler/CMessageHandler.cpp \
        Global/mysqlHandler/CMysqlHandler.cpp \
        Global/mysqlHandler/main.cpp \
        Global/objectHandler/CObject.cpp \
        Global/objectHandler/CThread.cpp \
        Global/objectHandler/CTimer.cpp \
        Global/objectHandler/Handler.cpp \
        Global/processHandler/CProcessHandler.cpp \
        Global/protocolHandler/CCmpClient.cpp \
        Global/protocolHandler/CCmpServer.cpp \
        Global/rankingHandler/CRankingHandler.cpp \
        Global/socketHandler/CATcpClient.cpp \
        Global/socketHandler/CATcpServer.cpp \
        Global/socketHandler/CDomainServer.cpp \
        Global/socketHandler/CSocket.cpp \
        Global/socketHandler/CSocketClient.cpp \
        Global/socketHandler/CSocketServer.cpp \
        Global/spotifyHandler/CSpotify.cpp \
        Global/stringHandler/CString.cpp \
        Global/stringHandler/CStringArray.cpp \
        Global/stringHandler/main.cpp \
        Global/threadHandler/CThreadHandler.cpp \
        Global/weatherHandler/CWeather.cpp \
        Global/wmctrl/wmctrl.c


HEADERS += \
        Controller-LegalAssistant/controllerHandler/CCmpWord.h \
        Controller-LegalAssistant/controllerHandler/CController.h \
        Controller-LegalAssistant/assistantwindow.h \
        Controller-LegalAssistant/controllerHandler/CResponsePacket.h \
        Controller-LegalAssistant/controllerHandler/config.h \
        Controller-LegalAssistant/mainwindowlegalassistant.h \
        Controller-LegalAssistant/semanticHandler/CAnalysisHandler.h \
        Controller-LegalAssistant/semanticHandler/CSemantic.h \
        Controller-LegalAssistant/semanticHandler/CSemanticJudge.h \
        Controller-LegalAssistant/semanticHandler/dataStruct.h \
        Controller-LegalAssistant/serviceHandler/CContentHandler.h \
        Controller-LegalAssistant/serviceHandler/CDisplayHandler.h \
        Controller-LegalAssistant/serviceHandler/CGamePlay.h \
        Controller-LegalAssistant/serviceHandler/CParticiple.h \
        Controller-LegalAssistant/serviceHandler/CPenReader.h \
        Controller-LegalAssistant/serviceHandler/CSemanticService.h \
        Controller-LegalAssistant/serviceHandler/CStory.h \
        Controller-LegalAssistant/webWidget/cwebwidget.h \
        Global/application/CApplication.h \
        Global/application/Message.h \
        Global/cmpHandler/CCmpHandler.h \
        Global/configHandler/CConfig.h \
        Global/configHandler/CConfigHandler.h \
        Global/dataHandler/CDataHandler.h \
        Global/fileHandler/CFileHandler.h \
        Global/global_inc/ICallback.h \
        Global/global_inc/common.h \
        Global/global_inc/container.h \
        Global/global_inc/dataType.h \
        Global/global_inc/event.h \
        Global/global_inc/packet.h \
        Global/global_inc/utf8.h \
        Global/global_inc/utility.h \
        Global/httpHandler/CHttpClient.h \
        Global/httpHandler/CHttpsClient.h \
        Global/jsonHandler/JSONArray.h \
        Global/jsonHandler/JSONObject.h \
        Global/jsonHandler/cJSON.h \
        Global/logHandler/LogHandler.h \
        Global/messageHandler/CMessageHandler.h \
        Global/mysqlHandler/CMysqlHandler.h \
        Global/objectHandler/CObject.h \
        Global/objectHandler/CThread.h \
        Global/objectHandler/CTimer.h \
        Global/objectHandler/Handler.h \
        Global/processHandler/CProcessHandler.h \
        Global/protocolHandler/CCmpClient.h \
        Global/protocolHandler/CCmpServer.h \
        Global/rankingHandler/CRankingHandler.h \
        Global/socketHandler/CATcpClient.h \
        Global/socketHandler/CATcpServer.h \
        Global/socketHandler/CDomainServer.h \
        Global/socketHandler/CSocket.h \
        Global/socketHandler/CSocketClient.h \
        Global/socketHandler/CSocketServer.h \
        Global/socketHandler/IReceiver.h \
        Global/spotifyHandler/CSpotify.h \
        Global/stringHandler/CString.h \
        Global/stringHandler/CStringArray.h \
        Global/threadHandler/CThreadHandler.h \
        Global/weatherHandler/CWeather.h


INCLUDEPATH += \
        Controller-LegalAssistant/controllerHandler \
        Controller-LegalAssistant \
        Controller-LegalAssistant/webWidget \
        Controller-LegalAssistant/serviceHandler \
        Controller-LegalAssistant/semanticHandler \
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
        Global/threadHandler \
        Global/protocolHandler \
        Global/jsonHandler \
        Global/fileHandler \
        Global/rankingHandler \
        Global/stringHandler \
        Global/mysqlHandler \
        Global/spotifyHandler \
        Global/weatherHandler \
        Global/httpHandler \
        /usr/include/glib-2.0 \
        /usr/lib/glib-2.0/include \
        /usr/lib/x86_64-linux-gnu/glib-2.0/include


#apt-get install libxmu-dev

LIBS += -lrt -lm -lglib-2.0 -lX11 -lXmu -L/usr/lib

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    Controller-LegalAssistant/form/assistantwindow.ui \
    Controller-LegalAssistant/form/mainwindowlegalassistant.ui

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

#copyToDestDir($$PWD/Controller-LegalAssistant/QController-LegalAssistant.conf, $$PWD/Controller-LegalAssistant/bin)

DISTFILES += \
    html/hop.ogg \
    html/index.htm
