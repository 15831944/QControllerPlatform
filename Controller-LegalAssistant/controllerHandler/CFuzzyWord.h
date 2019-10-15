#pragma once

#include <map>
#include "CChatbot.h"

class CFuzzyWord : public CChatbot
{
public:
    CFuzzyWord();
    virtual ~CFuzzyWord();
    void runAnalysis(INTENT &intentInfo);
    void init();

private:
    std::map<std::string,std::string> mapFuzzyWord;
};
