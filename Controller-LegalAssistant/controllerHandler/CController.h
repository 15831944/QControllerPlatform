/*
 * CController.h
 *
 *  Created on: 2017年4月8日
 *      Author: Jugo
 *      this is dummy class
 */

#pragma once

#include "CApplication.h"

class MainWindowLegalAssistant;
class AssistantWindow;
class CCmpWord;
class CMysqlHandler;

class CController: public CApplication
{
public:
	CController();
	virtual ~CController();
    void showMainWindow();
    void onSemanticWordRequest(const int nSocketFD, const int nSequence, const int nId, const int nType,
                const char *szWord);

protected:
	int onCreated(void* nMsqKey);
	int onInitial(void* szConfPath);
	int onFinish(void* nMsqKey);
	void onHandleMessage(Message &message);

private:
    int mnMsqKey;
    MainWindowLegalAssistant *mainWindow;
    AssistantWindow *assisant;
    CCmpWord *cmpword;
    CMysqlHandler *mysql;

};
