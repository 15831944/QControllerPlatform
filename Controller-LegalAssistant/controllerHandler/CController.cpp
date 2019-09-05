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

using namespace std;

CController::CController():cmpword(0),mysql(0)
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
        mysql->connect(config->getValue("MYSQL","ip"), config->getValue("MYSQL","db"), "legal", "legal", "5");
    }
    delete config;

    //semanticJudge->loadAnalysis();

    return nResult;
}

int CController::onFinish(void* nMsqKey)
{
    int nKey = *(reinterpret_cast<int*>(nMsqKey));
    if(assisant)
        assisant->close();
    delete mainWindow;
    delete assisant;
    return nKey;
}

void CController::onHandleMessage(Message &message)
{
    switch (message.what)
    {
    case semantic_word_request:
        // Lambda Expression
        thread([=]
        {	onSemanticWordRequest( message.arg[0], message.arg[1], message.arg[2], message.arg[3],
                    message.strData.c_str());}).detach();
        break;
    }
}

void CController::showMainWindow()
{
    _log("[CController] showMainWindow");
    //mainWindow->show();
    assisant->showMaximized();
}

void CController::onSemanticWordRequest(const int nSocketFD, const int nSequence, const int nId, const int nType,
                                        const char *szWord)
{
    CString strWord;
    CString strDevice_id;
    JSONObject jsonReq;
    JSONObject jsonResp;
    jsonResp.create();

    jsonReq.load(szWord);
    strWord = jsonReq.getString("word");
    strDevice_id = jsonReq.getString("device_id");
    jsonReq.release();

    _log("[CController] onSemanticWordRequest device_id: %s word: %s", strDevice_id.getBuffer(), strWord.getBuffer());

    switch (nType)
    {
    case TYPE_REQ_NODEFINE: // 語意判斷
        //  semanticJudge->runAnalysis(strWord.getBuffer(), jsonResp);
        break;
    case TYPE_REQ_CONTROL:	// 控制
        break;
    case TYPE_REQ_TALK: 	// 會話
        break;
    case TYPE_REQ_RECORD:	// 紀錄
        break;
    case TYPE_REQ_STORY:	// 故事
        break;
    case TYPE_REQ_GAME:		// 遊戲
        break;
    case TYPE_REQ_PEN:		// 點讀筆
        break;
    default:
        cmpword->response(nSocketFD, semantic_word_request, STATUS_RINVJSON, nSequence, 0);
        jsonResp.release();
        return;
    }

    cmpword->response(nSocketFD, semantic_word_request, STATUS_ROK, nSequence, jsonResp.put("id", nId).toJSON().c_str());
    jsonResp.release();
}
