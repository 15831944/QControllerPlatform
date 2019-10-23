#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QWebEngineSettings>
#include <QTextToSpeech>
#include <QVoice>
#include <QDesktopWidget>
#include <Qt>
#include <QLocale>
#include <QtCore>
#include "LogHandler.h"
#include "cwebwidget.h"
#include "assistantwindow.h"
#include "ui_assistantwindow.h"
#include "CMysqlHandler.h"
#include "config.h"
#include <string>

using namespace std;

#define WEB_FINTECH "https://www.fintechspace.com.tw"

AssistantWindow::AssistantWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AssistantWindow),webTalk(new CWebWidget(this)),webBook(new CWebWidget(this)),webNews(new CWebWidget(this)),mysql(new CMysqlHandler),timerQueryShow(0),timerStopTalk(0)
{
    QString strPath;

    ui->setupUi(this);

    QRect desktop = QApplication::desktop()->geometry();
    desktop.moveTo(QPoint(0, 0));
    setGeometry(desktop);

    QUrl url;
    webTalk->resize(600,350);
    webNews->resize(600,600);

    strPath.sprintf("%s/html/index.htm",QDir::currentPath().toStdString().c_str());
    webTalk->load(QUrl::fromLocalFile("/opt/html/index.htm"));

    strPath.sprintf("%s/html/news.htm",QDir::currentPath().toStdString().c_str());
    webNews->load(QUrl::fromLocalFile("/opt/html/news.htm"));

    strPath.sprintf("%s/html/amplify/index.html",QDir::currentPath().toStdString().c_str());
    webBook->load(QUrl::fromLocalFile(strPath));

    initWeb(webTalk);
    initWeb(webNews);
    initWeb(webBook);
    initLayout();

    timerQueryShow = new QTimer(this);
    timerStopTalk = new QTimer(this);

    connect(timerQueryShow,SIGNAL(timeout()) ,this, SLOT(slotQueryShow()));
    connect(timerStopTalk,SIGNAL(timeout()), this, SLOT(slotStopTalk()));

    timerQueryShow->start(1000);

    mysql->connect(DB_IP, DB_DATABASE, DB_USER, DB_PASSWORD, DB_CONN_TIMEOUT);
}

AssistantWindow::~AssistantWindow()
{
    if(mysql->isValid())
    {
        mysql->close();
    }
    timerQueryShow->stop();
    timerStopTalk->stop();
    delete timerQueryShow;
    delete timerStopTalk;
    delete mysql;
    delete webTalk;
    delete webNews;
    delete webBook;
    delete ui;
}

void AssistantWindow::initWeb(CWebWidget *webwidget)
{
    QWebEngineSettings *setting = webwidget->page()->settings();
    setting->setAttribute(QWebEngineSettings::AutoLoadImages,true);
    setting->setAttribute(QWebEngineSettings::JavascriptEnabled,true);
    setting->setAttribute(QWebEngineSettings::JavascriptCanOpenWindows,true);
    setting->setAttribute(QWebEngineSettings::LocalStorageEnabled,true);
    setting->setAttribute(QWebEngineSettings::PluginsEnabled,true);
    setting->setAttribute(QWebEngineSettings::ShowScrollBars,false);
    setting->setAttribute(QWebEngineSettings::PdfViewerEnabled,true);
}

void AssistantWindow::initLayout()
{
    QWidget *win = new QWidget(this);

    QHBoxLayout *hbox = new QHBoxLayout(win);
    QVBoxLayout *vbox = new QVBoxLayout();


    QSizePolicy spRight(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spRight.setVerticalStretch(1);
    webNews->setSizePolicy(spRight);

    vbox->addWidget(webNews);
    vbox->addWidget(webTalk);
    vbox->setAlignment(webTalk,Qt::AlignBottom);
    vbox->setAlignment(webNews,Qt::AlignTop);


    QSizePolicy spLeft(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spLeft.setHorizontalStretch(1);
    webBook->setSizePolicy(spLeft);

    hbox->setMargin(30);
    hbox->addWidget(webBook);
    hbox->addSpacing(2);
    hbox->addLayout(vbox);

    win->setStyleSheet("QWidget { background-image:url(\"/opt/html/bg.jpg\"); background-position: center;}");
    setCentralWidget(win);
}


void AssistantWindow::slotQueryShow()
{
    string strSQL;
    list<map<string, string> > listData;
    list<map<string, string> >::iterator i;
    map<string, string>::iterator j;
    QString strData;
    int nTalkSec;


    if(!mysql->isValid())
    {
        _log("[AssistantWindow] slotQueryShow Mysql Invalid!!");
       return;
    }

    strSQL = "SELECT id,input,reply,image FROM history WHERE state = 0 LIMIT 1";
    mysql->query(strSQL.c_str(), listData);
    if(0 < listData.size())
    {
        i = listData.begin();
        strData.sprintf("UPDATE history SET state = 1 WHERE id = %s", (*i)["id"].c_str());
        mysql->sqlExec(strData.toStdString());
        //_log("[AssistantWindow] slotQueryShow SQL:%s",strData.toStdString().c_str());

        strData.sprintf("showTitle('%s')",(*i)["input"].c_str());
        webBook->page()->runJavaScript(strData);

        strData.sprintf("showText('%s')",(*i)["reply"].c_str());
        webBook->page()->runJavaScript(strData);

        strData.sprintf("showImage('images/%s')",(*i)["image"].c_str());
        webBook->page()->runJavaScript(strData);

        webTalk->page()->runJavaScript("play()");
        nTalkSec = (int)(*i)["reply"].length()/10;
        if(4 > nTalkSec)
            nTalkSec = 4;
        if(30 < nTalkSec)
            nTalkSec = 30;
        timerStopTalk->start(nTalkSec * 1000);
       // _log("[AssistantWindow] slotQueryShow start play talk and show reply on left page. talk second:%d",nTalkSec);
    }
}

void AssistantWindow::slotStopTalk()
{
    timerStopTalk->stop();
    webTalk->page()->runJavaScript("stop()");
}
