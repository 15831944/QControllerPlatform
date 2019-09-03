#include "assistantwindow.h"
#include "ui_assistantwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QWebEngineSettings>
#include <QTextToSpeech>
#include <QVoice>
#include "cwebwidget.h"
#include <Qt>
#include <QLocale>
#include "LogHandler.h"

AssistantWindow::AssistantWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AssistantWindow),webTalk(new CWebWidget(this)),webBook(new CWebWidget(this)),webNews(new CWebWidget(this))
{
    ui->setupUi(this);

    webTalk->resize(600,600);
    webNews->resize(600,600);
    webTalk->load(QUrl::fromLocalFile("/opt/html/index.htm"));
    webBook->load(QUrl::fromLocalFile("/opt/html/law_book/book.html"));
    webNews->load(QUrl::fromLocalFile("/opt/html/news.htm"));

    initWeb(webTalk);
    initWeb(webNews);
    initWeb(webBook);
    initLayout();
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
    QVBoxLayout *vbox = new QVBoxLayout(win);


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

   // webTalk->page()->runJavaScript("test()");
   // webTalk->page()->runJavaScript("test2()");
   // webTalk->page()->runJavaScript("test()");

    QVoice voice;
    voice.ageName(QVoice::Adult);





}
