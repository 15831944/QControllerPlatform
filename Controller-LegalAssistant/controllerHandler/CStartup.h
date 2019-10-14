#pragma once

#include "CChatbot.h"

class CStartup : CChatbot
{
public:
    explicit CStartup();
    virtual ~CStartup();

protected:
    void runAnalysis(const char *szInput, std::string &strResp);
};
