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
#include "config.h"

using namespace std;

CAssistant::CAssistant():fuzzyWord(0)
{
    fuzzyWord = new CFuzzyWord();
}

CAssistant::~CAssistant()
{
    delete fuzzyWord;
}

void CAssistant::init()
{
    fuzzyWord->init();
}

void CAssistant::runAnalysis(INTENT &stIntent)
{
    int nCompare;
    int nIntent = -1;
    int nCount = 0;
    string strField;
    string strValue;
    CMysqlHandler *mysql;
    map<string, string> mapItem;

    stIntent.strInput = trim(stIntent.strOringe);

    if(0 == stIntent.strInput.compare("更新"))
    {
        init();
        stIntent.strResp = "資料庫已更新完畢";
        return;
    }

    mysql = new CMysqlHandler();
    if (TRUE == mysql->connect(DB_IP, DB_DATABASE, DB_USER, DB_PASSWORD, DB_CONN_TIMEOUT))
    {
        //================ Fuzzy Word Filter =============//
        fuzzyWord->runAnalysis(stIntent);

        //================ 比對絕對字串 ====================//
        nCompare = compare(stIntent,mysql);
        if(0 > nCompare) // service
        {
            mysql->close();
            delete mysql;
            return;
        }
        else if(1000 > nCompare && 0 <= nCompare)
        {
            //================ Intent Analysis ===============//
            stIntent.strTable = "intent";
            intentTree(stIntent,mysql);
        }

        //================ Response Word =================//
        getReply(stIntent,mysql);
        history(stIntent,mysql);
        mysql->close();
    }
    else
    {
        _log("[CAssistant] intentTree mysql connect fail: %s %s %s %s",DB_IP, DB_DATABASE, DB_USER, DB_PASSWORD);
        stIntent.strResp = RESP_WORD_DATABASE_ERROR;
    }
    delete mysql;
}

void CAssistant::runAnalysis(const char *szInput, std::string &strResp)
{
    INTENT intent;
    intent.init();
    intent.strOringe = szInput;
    runAnalysis(intent);
    strResp = intent.strResp;
}

int CAssistant::compare(INTENT &intentInfo, CMysqlHandler *mysql)
{
    string strSQL;
    ostringstream outStream;
    list<map<string, string> > listData;
    list<map<string, string> >::iterator i;

    outStream << SQL_QUERY_COMPARE_START << intentInfo.strInput << SQL_QUERY_COMPARE_END;
    strSQL = outStream.str();
    _log("[CAssistant] compare SQL: %s", strSQL.c_str());
    mysql->query(strSQL.c_str(), listData);
    for ( i = listData.begin(); i != listData.end(); ++i) // records
    {
        intentInfo.nIntent_id = atoi((*i)["intent"].c_str());
        break;
    }
    return intentInfo.nIntent_id;
}

void CAssistant::intentTree(INTENT &intentInfo,CMysqlHandler *mysql)
{
    ostringstream outStream;
    list<map<string, string> > listData;
    string strSQL;
    string strBefTable;
    list<map<string, string> >::iterator i;
    map<string, string>::iterator j;
    int nCount;

    outStream.str("");
    outStream.clear();
    outStream << SQL_QUERY_INTENT << intentInfo.strTable << SQL_QUERY_INTENT_ORDER;
    strBefTable = intentInfo.strTable;
    strSQL = outStream.str();
    _log("[CAssistant] intentTree SQL: %s", strSQL.c_str());
    listData.clear();
    mysql->query(strSQL.c_str(), listData);
    ++intentInfo.nCount;
    for ( i = listData.begin(); i != listData.end(); ++i) // records
    {
        for ( j = i->begin(); j != i->end(); ++j) // fields
        {
            if (0 == j->first.compare("keyword") ) // find keyword field name
            {
                 if(0 < findAllOccurances(intentInfo.strInput, j->second))
                 {
                     intentInfo.nIntent_id = atoi((*i)["intent"].c_str());
                     intentInfo.listKeyWord.push_back(j->second);
                     intentInfo.strTable = (*i)["table_name"];
                     _log("[CAssistant] intentTree word march intent: %d keyword: %s table: %s count:%d\n", intentInfo.nIntent_id,j->second.c_str(),intentInfo.strTable.c_str(),intentInfo.nCount);
                     if(1000 > intentInfo.nIntent_id && 50 > intentInfo.nCount)
                        intentTree(intentInfo,mysql);
                     return;
                 }
             }
        }
    }
}


void CAssistant::getReply(INTENT &intentInfo, CMysqlHandler *mysql)
{
    ostringstream outStream;
    list<map<string, string> > listData;
    list<map<string, string> >::iterator i;
    map<string, string>::iterator j;
    string strSQL;

    getUnknow(intentInfo.strResp);

    if(1000 <= intentInfo.nIntent_id)
    {
        outStream << SQL_QUERY_REPLIES << intentInfo.nIntent_id;
        strSQL = outStream.str();
        _log("[CAssistant] getReply SQL: %s", strSQL.c_str());
        listData.clear();
        mysql->query(strSQL.c_str(), listData);
        for ( i = listData.begin(); i != listData.end(); ++i) // records
        {
            outStream.str("");
            outStream.clear();
            outStream << (*i)["reply"] << getEnd();
            intentInfo.strResp = trim(outStream.str());
            intentInfo.strImage = (*i)["image"];
            break;
        }
    }
    else
    {
        keepUnknow(intentInfo.strOringe);
    }

    _log("[CAssistant] getReply reply: %s", intentInfo.strResp.c_str());
}

void CAssistant::getUnknow(std::string &strResp)
{
    static int nCount = 0;

    if(3 <= nCount)
        nCount = 0;
    strResp = arUnknow[nCount];
    ++nCount;
}

string CAssistant::getEnd()
{
    static int nCount = 0;
    int nTmp;

    if(3 <= nCount)
        nCount = 0;
    nTmp = nCount;
    ++nCount;
    return arEnd[nTmp];
}

void CAssistant::keepUnknow(std::string &strInput)
{
    CMysqlHandler *mysql;
    ostringstream outStream;

    mysql = new CMysqlHandler();
    if (TRUE == mysql->connect(DB_IP, DB_DATABASE, DB_USER, DB_PASSWORD, DB_CONN_TIMEOUT))
    {
        outStream << SQL_INSERT_UNKNOW_START << strInput << SQL_INSERT_UNKNOW_END;
        mysql->sqlExec(outStream.str());
        mysql->close();
    }
    delete mysql;
}

void CAssistant::history(INTENT &intentInfo, CMysqlHandler *mysql)
{
    ostringstream outStream;

    outStream << SQL_INSERT_HISTORY_START << intentInfo.strInput << "','" << intentInfo.strResp << "','" << intentInfo.strImage  << SQL_INSERT_HISTORY_END;
    mysql->sqlExec(outStream.str());
    _log("[CAssistant] history SQL:%s",outStream.str().c_str());
}
