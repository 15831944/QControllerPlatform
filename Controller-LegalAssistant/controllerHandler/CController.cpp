/*
 * CController.cpp
 *
 *  Created on: 2017年4月8日
 *      Author: Jugo
 */
#include <stdio.h>
#include <string>
#include <QtWebView/QtWebView>
#include <typeinfo>
#include <iostream>
#include "mainwindowlegalassistant.h"
#include "CController.h"
#include "LogHandler.h"
#include "assistantwindow.h"
#include "CMysqlHandler.h"
#include "CCmpWord.h"
#include "CConfig.h"
#include "utility.h"
#include "packet.h"
#include "CString.h"
#include "JSONObject.h"
#include "config.h"
#include "CAssistant.h"

using namespace std;

CController::CController():cmpword(0),mysql(0),chatbot(0)
{

}

CController::~CController()
{

}

int CController::onCreated(void* nMsqKey)
{
    // reinterpret_cast 將一種型態的指標轉換為另一種型態的指標
    mnMsqKey = *(reinterpret_cast<int*>(nMsqKey));
    mainWindow = new MainWindowLegalAssistant();
    assisant = new AssistantWindow();
    cmpword = new CCmpWord(this);
    mysql = new CMysqlHandler();
    chatbot = new CAssistant();
    return mnMsqKey;
}

int CController::onInitial(void* szConfPath)
{

    int nResult;
    int nCount;
    int nPort;
    string strConfPath;
    string strConfig;
    CConfig *config;

    QtWebView::initialize();
    nResult = FALSE;
    strConfPath = reinterpret_cast<const char*>(szConfPath);
    _log("[CController] onInitial Config File: %s", strConfPath.c_str());
    if (strConfPath.empty())
        return nResult;

    config = new CConfig();
    if (config->loadConfig(strConfPath))
    {
        strConfig = config->getValue("SERVER WORD", "port");
        if (!strConfig.empty())
        {
            convertFromString(nPort, strConfig);
            nResult = cmpword->start(0, static_cast<short>(nPort), mnMsqKey);
        }
        if(mysql->connect(config->getValue("MYSQL","ip"), config->getValue("MYSQL","db"), "legal", "legal", "5"))
        {
            chatbot->init();
        }
    }
    delete config;

    return nResult;
}

int CController::onFinish(void* nMsqKey)
{
    int nKey = *(reinterpret_cast<int*>(nMsqKey));
    if(assisant)
        assisant->close();
    delete mainWindow;
    delete assisant;
    delete chatbot;
    return nKey;
}

void CController::onHandleMessage(Message &message)
{
    switch (message.what)
    {
    case assistant_request:
        // Lambda Expression
        thread([=]
        {	onAssistantRequest( message.arg[0], message.arg[1],   message.strData.c_str());}).detach();
        break;
    }
}

void CController::showMainWindow()
{
    _log("[CController] showMainWindow");
    //mainWindow->show();
    assisant->showMaximized();
}

void CController::onAssistantRequest(const int nSocketFD, const int nSequence, const char *szWord)
{
    JSONObject jsonResp;
    string strResp = GLOBAL_WORD_UNKNOW;
    chatbot->runAnalysis(szWord,strResp);
    cmpword->response(nSocketFD, assistant_request, STATUS_ROK, nSequence, strResp.c_str());
}
