#pragma once

#include <map>
#include <list>
#include "INTENT.h"
#include "config.h"


class JSONObject;
class CMysqlHandler;
class CFuzzyWord;

class CAssistant
{
public:
    explicit CAssistant();
    virtual ~CAssistant();
    void runAnalysis(const char *szInput, std::string &strResp);
    void runAnalysis(INTENT &stIntent);
    void init();

private:
    void intentTree(INTENT &intentInfo, CMysqlHandler *mysql);
    void getReply(INTENT &intentInfo, CMysqlHandler *mysql);
    void history(INTENT &intentInfo, CMysqlHandler *mysql);
    void getUnknow(std::string &strResp);
    std::string getEnd();
    void keepUnknow(std::string &strInput);
    int compare(INTENT &intentInfo, CMysqlHandler *mysql);


private:
    std::map<std::string,std::string> mapFuzzyWord;
    CFuzzyWord *fuzzyWord;
    std::string arUnknow[3] = {RESP_WORD_UNKNOW1,RESP_WORD_UNKNOW2,RESP_WORD_UNKNOW3};
    std::string arEnd[3] = {RESP_WORD_END1,RESP_WORD_END2,RESP_WORD_END3};

};
