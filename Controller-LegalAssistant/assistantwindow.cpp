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

AssistantWindow::AssistantWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AssistantWindow),webTalk(new CWebWidget(this)),webBook(new CWebWidget(this)),webNews(new CWebWidget(this))
{
    ui->setupUi(this);

    QRect desktop = QApplication::desktop()->geometry();
    desktop.moveTo(QPoint(0, 0));
    setGeometry(desktop);

    webTalk->resize(600,350);
    webNews->resize(600,600);
    webTalk->load(QUrl::fromLocalFile("/opt/html/index.htm"));
    webBook->load(QUrl::fromLocalFile("/opt/html/left.htm"));
    //webBook->load(QUrl("https://law.moj.gov.tw/LawClass/LawSingle.aspx?pcode=G0400121&flno=63"));
    webNews->load(QUrl::fromLocalFile("/opt/html/news.htm"));

    initWeb(webTalk);
    initWeb(webNews);
    initWeb(webBook);
    initLayout();
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()) ,this, SLOT(MySlot()));
    connect(this,SIGNAL(singalsShowText(QString strText)),this,SLOT(slotShowText(QString strText)));
}

AssistantWindow::~AssistantWindow()
{
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

void AssistantWindow::MySlot(){

    webTalk->page()->runJavaScript("stop()");
    qDebug () << "Timer executed";
}

void AssistantWindow::showText(const char* szInput)
{
    webTalk->page()->runJavaScript("play()");
    QString strData;
    strData.sprintf("<HTML><HEADER></HEADER><BODY><H1>%s</BODY><HTML>",  szInput);
    emit singalsShowText(strData);
    webBook->page()->runJavaScript("play()");
    _log("[AssistantWindow] showText : emit singalsShowText");



    try {
        webBook->setHtml(strData);

    } catch (QException e) {
_log("exception: %s",e.what());
    }

   // webBook->load(QUrl::fromLocalFile("/opt/html/left.htm"));
   // connect(timer,SIGNAL(timeout()) ,this, SLOT(MySlot()));
   // timer->start(5000);

}

void AssistantWindow::slotShowText(QString strText)
{
    _log("[AssistantWindow] slotShowText : %s", strText.toStdString().c_str());
}
