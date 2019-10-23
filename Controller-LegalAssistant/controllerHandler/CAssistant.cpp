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

void CAssistant::runAnalysis(const char *szInput, std::string &strResp)
{
    int nIntent = -1;
    int nCount = 0;
    string strField;
    string strValue;
    CMysqlHandler *mysql;
    map<string, string> mapItem;
    INTENT intentInfo;

    intentInfo.init();
    intentInfo.strOringe = szInput;
    intentInfo.strInput = trim(szInput);

    if(0 == intentInfo.strInput.compare("更新"))
    {
        init();
        strResp = "資料庫已更新完畢";
        return;
    }



    mysql = new CMysqlHandler();
    if (TRUE == mysql->connect(DB_IP, DB_DATABASE, DB_USER, DB_PASSWORD, DB_CONN_TIMEOUT))
    {
        //================ Fuzzy Word Filter =============//
        fuzzyWord->runAnalysis(intentInfo);
        intentInfo.strTable = "intent";

        //================ Intent Analysis ===============//
        intentTree(intentInfo,mysql);
        //intentTree(intentInfo);

        //================ Response Word =================//
        getReply(intentInfo,mysql);
        strResp = intentInfo.strResp;
        history(intentInfo,mysql);
        mysql->close();
    }
    else
    {
        _log("[CAssistant] intentTree mysql connect fail: %s %s %s %s",DB_IP, DB_DATABASE, DB_USER, DB_PASSWORD);
        strResp = RESP_WORD_DATABASE_ERROR;
    }
    delete mysql;
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
                     _log("[CAssistant] intentTree word march intent: %d keyword: %s table: %s\n", intentInfo.nIntent_id,j->second.c_str(),intentInfo.strTable.c_str());
                     if(1000 > intentInfo.nIntent_id && 20 > intentInfo.nCount)
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
            intentInfo.strResp = outStream.str();
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




/*
void CAssistant::intentTree(INTENT &intentInfo)
{
    CMysqlHandler *mysql;
    ostringstream outStream;
    list<map<string, string> > listData;
    string strSQL;
    string strBefTable;
    list<map<string, string> >::iterator i;
    map<string, string>::iterator j;
    int nCount;

    mysql = new CMysqlHandler();
    if (TRUE == mysql->connect(DB_IP, DB_DATABASE, DB_USER, DB_PASSWORD, DB_CONN_TIMEOUT))
    {
        nCount = 0;
        while(1000 > intentInfo.nIntent_id)
        {
INTENT_HERE:
            outStream.str("");
            outStream.clear();
            outStream << SQL_QUERY_INTENT << intentInfo.strTable << SQL_QUERY_INTENT_ORDER;
            strBefTable = intentInfo.strTable;
            strSQL = outStream.str();
            _log("[CAssistant] intentTree SQL: %s", strSQL.c_str());
            listData.clear();
            mysql->query(strSQL.c_str(), listData);
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
                             _log("[CAssistant] intentTree word march intent: %d keyword: %s table: %s\n", intentInfo.nIntent_id,j->second.c_str(),intentInfo.strTable.c_str());
                             goto INTENT_HERE;
                         }
                     }
                }
            }
            if(20 < ++nCount || 0 == strBefTable.compare(intentInfo.strTable))
                break;
        }
        mysql->close();
    }
    delete mysql;
}
*/
