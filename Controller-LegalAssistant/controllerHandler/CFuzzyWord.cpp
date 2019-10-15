#include "CFuzzyWord.h"
#include "CMysqlHandler.h"
#include "LogHandler.h"
#include "common.h"
#include "config.h"
#include "utility.h"

using namespace std;

CFuzzyWord::CFuzzyWord():CChatbot()
{
    init();
}

CFuzzyWord::~CFuzzyWord()
{

}

void CFuzzyWord::runAnalysis(INTENT &intentInfo)
{
    string strOrg = intentInfo.strInput;
    for (map<string, string>::iterator it = mapFuzzyWord.begin(); it != mapFuzzyWord.end(); ++it)
    {
        intentInfo.strInput = ReplaceAll(intentInfo.strInput,it->first,it->second);
    }
    _log("[CFuzzyWord] runAnalysis : %s --> %s", strOrg.c_str(), intentInfo.strInput.c_str());
}

void CFuzzyWord::init()
{
    list<map<string, string> > listRecord;

    initData("SELECT fuzzyWord,correctWord FROM fuzzyWord", listRecord);

    mapFuzzyWord.clear();
    for (list<map<string, string> >::iterator i = listRecord.begin(); i != listRecord.end(); ++i)
    {
        mapFuzzyWord[(*i)["fuzzyWord"]] = (*i)["correctWord"];
        _log("[CFuzzyWord] init: %s --> %s", (*i)["fuzzyWord"].c_str(), (*i)["correctWord"].c_str());
    }
}
