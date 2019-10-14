#pragma once

#include <map>
#include <list>

class CMysqlHandler;

class CChatbot
{
public:


protected:
    CChatbot();
    virtual ~CChatbot();
    virtual void runAnalysis(const char *szInput, std::string &strResp) = 0;
    void initData(const char * szTable);

private:
    std::list<std::map<std::string, std::string> > listData;
    CMysqlHandler *mysql;
};
