#include "CIntent.h"

using namespace std;

CIntent::CIntent():CChatbot()
{
    init();
}

CIntent::~CIntent()
{

}

void CIntent::init()
{
    initData("intent");
}


