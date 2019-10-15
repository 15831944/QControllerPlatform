#pragma once

#include <string>
#include <list>

typedef struct _INTENT
{
    int nIntent_id;
    std::string strTable;
    std::string strInput;
    std::string strResp;
    std::list<std::string> listKeyWord;

    void init()
    {
        nIntent_id = 0;
        strTable.empty();
        strResp.empty();
        strInput.empty();
        listKeyWord.clear();
    }
}INTENT;


