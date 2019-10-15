#pragma once

#include <map>
#include <list>
#include "INTENT.h"

class CMysqlHandler;



class CChatbot
{
public:
    void showData(std::list<std::map<std::string, std::string> > &listRecord, const char* szTable);
    void runAnalysis(INTENT &intentInfo);

protected:
    CChatbot();
    virtual ~CChatbot();
    void initData(const char * szSQL, std::list<std::map<std::string, std::string> > &listRecord);
    void initData(const char * szTable);

private:
    int findAllOccurances(std::string data, std::string toSearch);

private:
    std::list<std::map<std::string, std::string> > listData;

};
