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
    intentInfo.strInput = trim(szInput);

    if(0 == intentInfo.strInput.compare("更新"))
    {
        init();
        strResp = "資料庫已更新完畢";
        return;
    }

    //================ Fuzzy Word Filter =============//

    fuzzyWord->runAnalysis(intentInfo);
    intentInfo.strTable = "intent";
    intentTree(intentInfo);
    getReply(intentInfo);
    strResp = intentInfo.strResp;

}

inline int findAllOccurances(string data, string toSearch)
{
    int nCount;
    // Get the first occurrence
    size_t pos = data.find(toSearch);

    // Repeat till end is reached
    nCount = 0;
    while( pos != string::npos)
    {
        ++nCount;
        // Get the next occurrence from the current position
        pos =data.find(toSearch, pos + toSearch.size());
    }
    return nCount;
}

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

void CAssistant::getReply(INTENT &intentInfo)
{
    CMysqlHandler *mysql;
    ostringstream outStream;
    list<map<string, string> > listData;
    list<map<string, string> >::iterator i;
    map<string, string>::iterator j;
    string strSQL;

    intentInfo.strResp = GLOBAL_WORD_UNKNOW;
    if(1000 <= intentInfo.nIntent_id)
    {
        mysql = new CMysqlHandler();
        if (TRUE == mysql->connect(DB_IP, DB_DATABASE, DB_USER, DB_PASSWORD, DB_CONN_TIMEOUT))
        {
            outStream << SQL_QUERY_REPLIES << intentInfo.nIntent_id;
            strSQL = outStream.str();
            _log("[CAssistant] getReply SQL: %s", strSQL.c_str());
            listData.clear();
            mysql->query(strSQL.c_str(), listData);
            for ( i = listData.begin(); i != listData.end(); ++i) // records
            {
                intentInfo.strResp = (*i)["reply"];
                break;
            }
            mysql->close();
        }
        delete mysql;
    }
    _log("[CAssistant] getReply reply: %s", intentInfo.strResp.c_str());
}
