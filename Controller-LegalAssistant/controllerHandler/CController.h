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

class CController: public CApplication
{
public:
	CController();
	virtual ~CController();
    void showMainWindow();

protected:
	int onCreated(void* nMsqKey);
	int onInitial(void* szConfPath);
	int onFinish(void* nMsqKey);
	void onHandleMessage(Message &message);

private:
    MainWindowLegalAssistant *mainWindow;


};
