#pragma once

#include <map>
#include <list>

class JSONObject;
class CMysqlHandler;

class CAssistant
{
public:
    explicit CAssistant();
    virtual ~CAssistant();
    void runAnalysis(const char *szInput, std::string &strResp);
    void init();

private:
    void intent(int nIntent, const char* szTable, const char* szWord,std::string &strResp, CMysqlHandler*& mysql);
    std::string startup(const char* szTable, const char* szWord, CMysqlHandler*& mysql);

private:
    std::list<std::map<std::string, std::string> > listIntent;
    std::list<std::map<std::string, std::string> > listStartup;
    std::map<std::string,std::string> mapFuzzyWord;
};
