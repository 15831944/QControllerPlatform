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

CController::CController():assisantWindow(0),cmpword(0),mysql(0),chatbot(0)
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
    assisantWindow = new AssistantWindow();
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
    }
    delete config;

    return nResult;
}

int CController::onFinish(void* nMsqKey)
{
    int nKey = *(reinterpret_cast<int*>(nMsqKey));
    if(assisantWindow)
        assisantWindow->close();
    delete mainWindow;
    delete assisantWindow;
    delete chatbot;
    return nKey;
}

void CController::onHandleMessage(Message &message)
{
    if(assistant_request == message.what)
    {
        thread([=]
        {	onAssistantRequest( message.arg[0], message.arg[1],   message.strData.c_str());}).detach();
    }
}

void CController::showMainWindow()
{
    assisantWindow->showMaximized();
}

void CController::onAssistantRequest(const int nSocketFD, const int nSequence, const char *szWord)
{
    JSONObject jsonResp;
    string strResp = RESP_WORD_UNKNOW0;
    chatbot->runAnalysis(szWord,strResp);
    cmpword->response(nSocketFD, assistant_request, STATUS_ROK, nSequence, strResp.c_str());
}
