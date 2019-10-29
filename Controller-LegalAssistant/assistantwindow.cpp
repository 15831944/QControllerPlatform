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
#include <string>
#include "LogHandler.h"
#include "cwebwidget.h"
#include "assistantwindow.h"
#include "ui_assistantwindow.h"
#include "CMysqlHandler.h"
#include "config.h"



using namespace std;

#define WEB_FINTECH "https://www.fintechspace.com.tw"

AssistantWindow::AssistantWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AssistantWindow),webTalk(new CWebWidget(this)),webBook(new CWebWidget(this)),webNews(new CWebWidget(this)),timerQueryShow(0),timerStopTalk(0),player(0)
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

    strPathSound.sprintf("%s/sound",QDir::currentPath().toStdString().c_str());

    initWeb(webTalk);
    initWeb(webNews);
    initWeb(webBook);
    initLayout();

   // timerQueryShow = new QTimer(this);
    timerStopTalk = new QTimer(this);

    connect(timerQueryShow,SIGNAL(timeout()) ,this, SLOT(slotQueryShow()));
    connect(timerStopTalk,SIGNAL(timeout()), this, SLOT(slotStopTalk()));

    player = new QMediaPlayer;
    //connect(player,SIGNAL(&stateChanged),this,SLOT(&stateChanged));
    connect(player,&QMediaPlayer::stateChanged,this,&AssistantWindow::stateChanged);

    // 偵測音檔播放時間
    //connect(player,&QMediaPlayer::positionChanged,this,&AssistantWindow::positionChanged);

    connect(this,&AssistantWindow::signalShowText,this,&AssistantWindow::slotShowText);
}

AssistantWindow::~AssistantWindow()
{
    timerQueryShow->stop();
    timerStopTalk->stop();
    player->stop();

    delete player;
    delete timerQueryShow;
    delete timerStopTalk;
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


void AssistantWindow::slotStopTalk()
{
    timerStopTalk->stop();
    webTalk->page()->runJavaScript("stop()");
}

void AssistantWindow::stateChanged(QMediaPlayer::State state)
{
    switch(state)
    {
    case QMediaPlayer::StoppedState:
        webTalk->page()->runJavaScript("stop()");
        _log("[AssistantWindow] stateChanged Stopped Sound");
        break;
    case QMediaPlayer::PlayingState:
        webTalk->page()->runJavaScript("play()");
        _log("[AssistantWindow] stateChanged Playing Sound");
        break;
    case QMediaPlayer::PausedState:
        _log("[AssistantWindow] stateChanged Pause Sound");
        break;
    }
}

void AssistantWindow::positionChanged(qint64 position)
{
   _log("[AssistantWindow] positionChanged : %d",position);
}

void AssistantWindow::showText(string strInput,string strResp,string strImage, int nIntentId)
{
    emit signalShowText( strInput.c_str(), strResp.c_str(), strImage.c_str(),  nIntentId);
}

void AssistantWindow::slotShowText(QString strInput,QString strResp,QString strImage, int nIntentId)
{
    QString strData;

    if(0 > nIntentId)
    {
        _log("[AssistantWindow] slotShowText run service: %d", nIntentId);
        service(nIntentId);
        return;
    }

    if(0 >= strImage.length())
        strImage = "default.png";

    _log("[AssistantWindow] slotShowText : %s %s %s %d",strInput.toStdString().c_str(),strResp.toStdString().c_str(),strImage.toStdString().c_str(),nIntentId);

    strData.sprintf("showTitle('%s')",strInput.toStdString().c_str());
    strData.replace("\n\r","</br>").replace("\r\n","</br>").replace("\r","</br>");
    webBook->page()->runJavaScript(strData);

    strData.sprintf("showText('%s')",strResp.toStdString().c_str());
    strData.replace("\n\r","</br>").replace("\r\n","</br>").replace("\r","</br>");
    webBook->page()->runJavaScript(strData);

    strData.sprintf("showImage('images/%s')",strImage.toStdString().c_str());
    webBook->page()->runJavaScript(strData);

    strData.sprintf("%s/%d.wav",strPathSound.toStdString().c_str(),nIntentId);
    player->stop();
    player->setMedia(QUrl::fromLocalFile(strData));
    player->setVolume(50);
    player->play();

}

void AssistantWindow::service(int nIntent)
{
    QString strPath;
    QString strSQL;
    CMysqlHandler *mysql;
    list<map<string, string> > listData;

    if(-1002 == nIntent) // go to assistant
    {
        strPath.sprintf("%s/html/amplify/index.html",QDir::currentPath().toStdString().c_str());
        webBook->load(QUrl::fromLocalFile(strPath));
        return;
    }

    mysql = new CMysqlHandler();
    mysql->connect(DB_IP, DB_DATABASE, DB_USER, DB_PASSWORD, DB_CONN_TIMEOUT);
    if(!mysql->isValid())
    {
        _log("[AssistantWindow] service Mysql connect fail!!");
        delete mysql;
        return;
    }

    strSQL.sprintf("SELECT service FROM services WHERE intent = %d", nIntent);
    mysql->query(strSQL.toStdString().c_str(), listData);
    if(0 < listData.size())
    {
        webBook->load(QUrl((*listData.begin())["service"].c_str()));
    }
    mysql->close();
    delete mysql;
}






/*
void AssistantWindow::slotQueryShow()
{
    string strFile;
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

        strFile = (*i)["image"];
        if(0 >= strFile.length())
            strFile = "default.png";
        strData.sprintf("showImage('images/%s')",strFile.c_str());
        webBook->page()->runJavaScript(strData);


        nTalkSec = (int)(*i)["reply"].length()/10;
        if(4 > nTalkSec)
            nTalkSec = 4;
        if(30 < nTalkSec)
            nTalkSec = 30;
        //timerStopTalk->start(nTalkSec * 1000);

        player->stop();
        player->setMedia(QUrl::fromLocalFile("/root/下載/語音測試/10004_FinTechSpace在哪？.wav"));
        player->setVolume(50);
        player->play();
       // _log("[AssistantWindow] slotQueryShow start play talk and show reply on left page. talk second:%d",nTalkSec);
    }
}
*/

