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
    //webBook->load(QUrl::fromLocalFile("/opt/html/left.htm"));
    //webBook->load(QUrl("https://law.moj.gov.tw/LawClass/LawSingle.aspx?pcode=G0400121&flno=63"));
    webNews->load(QUrl::fromLocalFile("/opt/html/news.htm"));

    initWeb(webTalk);
    initWeb(webNews);
    initWeb(webBook);
    initLayout();
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()) ,this, SLOT(MySlot()));
    timer->start(10000);
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

    QString strData = "<HTML><HEADER><BODY><H1>第 63 條 證券投資信託事業及證券投資顧問事業，應經主管機關許可，並核發營業 執照後，始得營業。 證券投資信託事業及證券投資顧問事業設立分支機構，應經主管機關許可            。</BODY><HTML>";
    timer->stop();
    //webBook->load(QUrl("https://law.moj.gov.tw/LawClass/LawSingle.aspx?pcode=G0400121&flno=63"));
    webBook->setHtml(strData);
    webTalk->page()->runJavaScript("play()");
    qDebug () << "Timer executed";
}
