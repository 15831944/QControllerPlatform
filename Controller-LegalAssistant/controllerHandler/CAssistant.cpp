#include "CAssistant.h"
#include "JSONObject.h"
#include "CMysqlHandler.h"
#include "LogHandler.h"
#include "common.h"
#include "CString.h"

using namespace std;

CAssistant::CAssistant()
{

}

CAssistant::~CAssistant()
{

}

inline void showInit(list<std::map<std::string, std::string> > &listRecord, const char* szTable)
{
    map<string, string> mapItem;
    for (list<map<string, string> >::iterator i = listRecord.begin(); i != listRecord.end(); ++i)
    {
        _log("============================= %s =============================",szTable);
        mapItem = *i;
        _log("%s:%s:%s", mapItem["keyword"].c_str(), mapItem["intent"].c_str(),mapItem["table_name"].c_str());
    }
}

void CAssistant::init()
{

    CMysqlHandler *mysql = new CMysqlHandler();

    if (TRUE == mysql->connect("127.0.0.1", "legal", "legal", "legal", "5"))
    {
        _log("[CAssistant] init: Mysql Connect Success");
        listIntent.clear();
        listStartup.clear();

        mysql->query("select intent,keyword,table_name from intent", listIntent);
        mysql->query("select intent,keyword,table_name from startup", listStartup);

        showInit(listIntent,"intent");
        showInit(listStartup,"startup");

        // init fuzzy word table
        map<string, string> mapItem;
        mapFuzzyWord.clear();
        list<map<string, string> > listFuzzy;
        mysql->query("select fuzzyWord,correctWord from fuzzyWord", listFuzzy);

        for (list<map<string, string> >::iterator i = listFuzzy.begin(); i != listFuzzy.end(); ++i)
        {
            mapItem = *i;
            mapFuzzyWord[mapItem["fuzzyWord"]] = mapItem["correctWord"];
            _log("Fuzzy Word %s : %s", mapItem["fuzzyWord"].c_str(), mapItem["correctWord"].c_str());
        }

        mysql->close();
        delete mysql;
    }
}

void CAssistant::runAnalysis(const char *szInput, std::string &strResp)
{
    int nIntent = -1;
    int nCount = 0;
    string strField;
    string strValue;
    map<string, string> mapItem;
    CString strWord = szInput;
    CMysqlHandler *mysql;

    strWord.trim();

    if(0 == strWord.Compare("更新"))
    {
        init();
        strResp = "資料庫已更新完畢";
        return;
    }
    //================ 謝謝你的解說=====================//
    if (0 == strWord.getLength() || 0 <= strWord.find("謝謝") || 0 <= strWord.find("感謝") || 0 <= strWord.find("掰掰") || 0 <= strWord.find("拜拜")
                || 0 <= strWord.find("謝啦") || 0 <= strWord.find("謝拉"))
    {
        strResp = "謝謝您的使用";
        return;
    }

    mysql = new CMysqlHandler();
    if (TRUE == mysql->connect("127.0.0.1", "legal", "legal", "legal", "5"))
    {
        _log("[CAssistant] runAnalysis: Mysql Connect Success");
        // key word 字典檔查關鍵字
        for (list<map<string, string> >::iterator i = listIntent.begin(); i != listIntent.end(); ++i, ++nCount)
        {
            mapItem = *i;
            for (map<string, string>::iterator j = mapItem.begin(); j != mapItem.end(); ++j)
            {
              //  _log("%s : %s\n", (*j).first.c_str(), (*j).second.c_str());
                if ((*j).first.compare("keyword") == 0)
                {
                     if (0 <= strWord.find(j->second.c_str()))
                     {
                         nIntent = atoi(mapItem["intent"].c_str());
                         _log("word march intent: %d keyword: %s table: %s\n", nIntent,(*j).second.c_str(),mapItem["table_name"].c_str());
                         intent(nIntent, mapItem["table_name"].c_str(), (*j).second.c_str(), strResp, mysql);
                         mysql->close();
                         delete mysql;
                         return;
                      }
                 }
           }
       }
       mysql->close();
       delete mysql;
    }
}

void CAssistant::intent(int nIntent, const char* szTable, const char* szWord,std::string &strResp, CMysqlHandler*& mysql)
{
    // Intent search
        switch (nIntent)
        {
        case 1: // How many startup in fintech space
            strResp = "園區類別尚未建立";
            break;
        case 2: // Information of fintech
            strResp = "金融資訊尚未建立";
            break;
        case 3: // startup 新創
            strResp = startup(szTable,szWord,mysql);
            break;
        case 4: // payment 儲值支付
            break;
        case 5: // investment 投資理財
            break;
        case 6: // sandbox 監理沙盒
            break;
        default: // unknow intent
            strResp = "目前不清楚此問題 ";
            break;
        }
}

string CAssistant::startup(const char* szTable, const char* szWord, CMysqlHandler*& mysql)
{
    return "startup";
}
