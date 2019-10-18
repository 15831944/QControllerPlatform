#pragma once

#include <map>
#include <list>
#include "INTENT.h"

class JSONObject;
class CMysqlHandler;
class CFuzzyWord;

class CAssistant
{
public:
    explicit CAssistant();
    virtual ~CAssistant();
    void runAnalysis(const char *szInput, std::string &strResp);
    void init();

private:
    void intentTree(INTENT &intentInfo);
    void getReply(INTENT &intentInfo);

private:
    std::map<std::string,std::string> mapFuzzyWord;
    CFuzzyWord *fuzzyWord;
};
