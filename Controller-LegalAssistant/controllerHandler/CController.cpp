/*
 * CController.cpp
 *
 *  Created on: 2017年4月8日
 *      Author: Jugo
 */
#include <stdio.h>
#include <string>
#include "mainwindowlegalassistant.h"
#include "CController.h"
#include <typeinfo>
#include <iostream>
#include "LogHandler.h"
#include <QtWebView/QtWebView>

using namespace std;

CController::CController()
{
// Dummy Class
}

CController::~CController()
{

}

int CController::onCreated(void* nMsqKey)
{
	// reinterpret_cast 將一種型態的指標轉換為另一種型態的指標
	int nKey = *(reinterpret_cast<int*>(nMsqKey));
    mainWindow = new MainWindowLegalAssistant();
	return nKey;
}

int CController::onInitial(void* szConfPath)
{
	string strConfPath = reinterpret_cast<const char*>(szConfPath);
    QtWebView::initialize();
	return 0;
}

int CController::onFinish(void* nMsqKey)
{
	int nKey = *(reinterpret_cast<int*>(nMsqKey));
    delete mainWindow;
	return nKey;
}

void CController::onHandleMessage(Message &message)
{
	switch(message.what)
	{

	}
}

void CController::showMainWindow()
{
    _log("[CController] showMainWindow");
    mainWindow->show();
}
