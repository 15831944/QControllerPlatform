#pragma once

#include "INTENT.h"
#include "CChatbot.h"

class CBoss : public CChatbot
{
public:
    explicit CBoss();
    virtual ~CBoss();
    void runAnalysis(INTENT &intentInfo);
};
