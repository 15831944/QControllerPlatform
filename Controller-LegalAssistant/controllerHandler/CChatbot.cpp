#include "CChatbot.h"
#include "CMysqlHandler.h"
#include "common.h"

using namespace std;

CChatbot::CChatbot():mysql(0)
{
    mysql = CMysqlHandler::getInstance();
}

CChatbot::~CChatbot()
{

}

void CChatbot::initData(const char * szTable)
{
    if(0 == szTable)
        return;

     if (TRUE == mysql->connect("127.0.0.1", "legal", "legal", "legal", "5"))
     {

     }
}
