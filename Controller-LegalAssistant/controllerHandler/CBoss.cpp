#include <sstream>
#include "CBoss.h"
#include "CMysqlHandler.h"
#include "common.h"
#include "config.h"

using namespace std;

CBoss::CBoss()
{

}

CBoss::~CBoss()
{

}

void CBoss::runAnalysis(INTENT &intentInfo)
{
    string strStartupName;
    string strSQL;
    ostringstream stringStream;
    ostringstream osResp;
    list<string>::iterator it;
    list<map<string, string> >::iterator irecord;

   intentInfo.strResp = "請問要詢問那一個新創團隊的老闆";
    stringStream << "SELECT boss FROM legal.boss WHERE name LIKE ";

    for(it = intentInfo.listKeyWord.begin(); intentInfo.listKeyWord.end() != it; ++it)
    {
        if(it != intentInfo.listKeyWord.begin())
        {
            stringStream << " or name LIKE ";
        }
        else
        {
            strStartupName = *it;
        }
        stringStream << "'%%";
        stringStream << *it;
        stringStream << "%%'";
    }

    strSQL = stringStream.str();
    _log("[CBoss] runAnalysis sql: %s", strSQL.c_str());
    list<map<string, string> > listRecord;
    initData(strSQL.c_str(),listRecord);
    for (irecord = listRecord.begin(); irecord != listRecord.end(); ++irecord)
    {
        _log("[CBoss] runAnalysis boss: %s", (*irecord)["boss"].c_str());
        osResp << "新創團隊" << strStartupName << "的老闆是" << (*irecord)["boss"];
        intentInfo.strResp = osResp.str();
        break;
    }

}
