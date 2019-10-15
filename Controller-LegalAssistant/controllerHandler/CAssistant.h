#pragma once

#include <map>
#include <list>
#include "INTENT.h"

class JSONObject;
class CMysqlHandler;
class CFuzzyWord;
class CIntent;
class CStartup;
class CBoss;

class CAssistant
{
    enum
    {
        SPACE = 1,
        OTHER = 2,
        STARTUP = 3,
        PAYMENT = 4,
        INVESTMENT = 5,
        SANDBOX = 6
    };
public:
    explicit CAssistant();
    virtual ~CAssistant();
    void runAnalysis(const char *szInput, std::string &strResp);
    void init();

private:
    void onStartup(INTENT &intentInfo);

private:
    typedef void (CAssistant::*MemFn)(INTENT &intentInfo);
    std::map<int, MemFn> mapFunc;
    std::list<std::map<std::string, std::string> > listIntent;
    std::list<std::map<std::string, std::string> > listStartup;
    std::map<std::string,std::string> mapFuzzyWord;
    CFuzzyWord *fuzzyWord;
    CIntent *intent;
    CStartup *startup;
    CBoss *boss;

};
