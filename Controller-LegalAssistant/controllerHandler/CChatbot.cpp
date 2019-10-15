#include <sstream>
#include "CChatbot.h"
#include "CMysqlHandler.h"
#include "common.h"
#include "config.h"

using namespace std;

CChatbot::CChatbot()
{

}

CChatbot::~CChatbot()
{
    listData.clear();
}

void CChatbot::initData(const char * szTable)
{
    CMysqlHandler *mysql;
    string strSQL;
    ostringstream stringStream;

    if(0 == szTable)
        return;

    mysql = new CMysqlHandler();
    stringStream << SQL_QUERY_INTENT << szTable << SQL_QUERY_INTENT_ORDER;
    strSQL = stringStream.str();

    if (TRUE == mysql->connect(DB_IP, DB_DATABASE, DB_USER, DB_PASSWORD, DB_CONN_TIMEOUT))
    {
        listData.clear();
        mysql->query(strSQL.c_str(), listData);
        mysql->close();
        showData(listData,szTable);
    }
    _log("[CChatbot]initData mysql status: %s",mysql->getStatus());
    delete mysql;
}

void CChatbot::initData(const char * szSQL, std::list<std::map<std::string, std::string> > &listRecord)
{
    CMysqlHandler *mysql;

    mysql = new CMysqlHandler();
    if (TRUE == mysql->connect(DB_IP, DB_DATABASE, DB_USER, DB_PASSWORD, DB_CONN_TIMEOUT))
    {
        mysql->query(szSQL, listRecord);
        mysql->close();
    }
    delete mysql;
}

void CChatbot::showData(list<map<string, string> > &listRecord, const char* szTable)
{
    map<string, string> mapItem;
    for (list<map<string, string> >::iterator i = listRecord.begin(); i != listRecord.end(); ++i)
    {
        _log("============================= %s =============================",szTable);
        mapItem = *i;
        _log("%s:%s:%s", mapItem["keyword"].c_str(), mapItem["intent"].c_str(),mapItem["table_name"].c_str());
    }
}

/**
 * @brief CChatbot::runAnalysis
 * @param szInput
 * @param intentInfo
 * @ ToDo 未來依據intent 判斷關鍵字有多少個中
 */
void CChatbot::runAnalysis( INTENT &intentInfo)
{
    int nCount;
    list<map<string, string> >::iterator i;
    map<string, string>::iterator j;

    nCount = 0;

    // key word 字典檔查關鍵字
    for ( i = listData.begin(); i != listData.end(); ++i, ++nCount) // records
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
                     _log("[CChatbot] runAnalysis word march intent: %d keyword: %s table: %s\n", intentInfo.nIntent_id,j->second.c_str(),intentInfo.strTable.c_str());
                     return;
                  }
             }
       }
   }
}

int CChatbot::findAllOccurances(string data, string toSearch)
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
