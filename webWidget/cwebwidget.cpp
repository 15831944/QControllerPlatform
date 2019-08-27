#include "cwebwidget.h"
#include <QUrl>
#include "ui_mainwindow.h"

CWebWidget::CWebWidget(QWidget *parent) : QWebEngineView(parent)
{

}

void CWebWidget::loadURL(const char *strURL)
{
    load(QUrl(strURL));
}
