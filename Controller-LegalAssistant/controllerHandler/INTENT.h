#pragma once

#include <string>
#include <list>

typedef struct _INTENT
{
    int nCount;
    int nIntent_id;
    std::string strOringe;
    std::string strTable;
    std::string strInput;
    std::string strResp;
    std::list<std::string> listKeyWord;

    void init()
    {
        nCount = 0;
        nIntent_id = 0;
        strOringe.empty();
        strTable.empty();
        strResp.empty();
        strInput.empty();
        listKeyWord.clear();
    }
}INTENT;


