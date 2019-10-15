#include "CStartup.h"

CStartup::CStartup():CChatbot()
{
    init();
}

CStartup::~CStartup()
{

}

void CStartup::init()
{
    initData("startup");
}
