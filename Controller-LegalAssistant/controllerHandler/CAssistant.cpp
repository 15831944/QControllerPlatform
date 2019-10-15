#include "CAssistant.h"
#include "JSONObject.h"
#include "CMysqlHandler.h"
#include "LogHandler.h"
#include "common.h"
#include "CString.h"
#include "CFuzzyWord.h"
#include "CIntent.h"
#include "CStartup.h"
#include "utility.h"
#include "CBoss.h"

using namespace std;

CAssistant::CAssistant():fuzzyWord(0),intent(0),startup(0),boss(0)
{
    fuzzyWord = new CFuzzyWord();
    intent = new CIntent();
    startup = new CStartup();
    boss = new CBoss();

    mapFunc[STARTUP] = &CAssistant::onStartup;
}

CAssistant::~CAssistant()
{
    delete fuzzyWord;
    delete intent;
    delete startup;
    delete boss;
}

void CAssistant::init()
{
    fuzzyWord->init();
    intent->init();
    startup->init();
}

void CAssistant::runAnalysis(const char *szInput, std::string &strResp)
{
    int nIntent = -1;
    int nCount = 0;
    string strField;
    string strValue;

    CMysqlHandler *mysql;
    map<string, string> mapItem;
    map<int, MemFn>::iterator iter;
    INTENT intentInfo;

    intentInfo.init();
    intentInfo.strInput = trim(szInput);

    if(0 == intentInfo.strInput.compare("更新"))
    {
        init();
        strResp = "資料庫已更新完畢";
        return;
    }
    //================ 謝謝你的解說=====================//
  //  if (0 == intentInfo.strInput.length() || string::npos != intentInfo.strInput.compare("謝謝") || string::npos != intentInfo.strInput.compare("感謝") || string::npos != intentInfo.strInput.find("掰掰") || string::npos != intentInfo.strInput.find("拜拜")
  //              || string::npos != intentInfo.strInput.compare("謝啦") || string::npos != intentInfo.strInput.compare("謝拉"))
  //  {
  //      strResp = "謝謝您的使用";
  //      return;
  //  }

    //================ Fuzzy Word Filter =============//

    fuzzyWord->runAnalysis(intentInfo);
    intent->runAnalysis(intentInfo);

    if(mapFunc.end() == mapFunc.find(intentInfo.nIntent_id))
    {
        strResp = "語意的意圖未建立相關的知識庫";
        return;
    }

    (this->*this->mapFunc[intentInfo.nIntent_id])(intentInfo);

    strResp = intentInfo.strResp;
    return;
}

void CAssistant::onStartup(INTENT &intentInfo)
{
    intentInfo.strResp = "分析新創相關問題";
    startup->runAnalysis(intentInfo);
    _log("[CAssistant] onStartup runAnalysis nIntent_id: %d", intentInfo.nIntent_id);
    switch(intentInfo.nIntent_id)
    {
    case 1:
        boss->runAnalysis(intentInfo);
        break;
    }
}

