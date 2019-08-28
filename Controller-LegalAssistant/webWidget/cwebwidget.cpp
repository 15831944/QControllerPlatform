#include "cwebwidget.h"
#include <QUrl>


CWebWidget::CWebWidget(QWidget *parent) : QWebEngineView(parent)
{

}

void CWebWidget::loadURL(const char *strURL)
{
    load(QUrl(strURL));
}
