#include "assistantwindow.h"
#include "ui_assistantwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QMediaPlayer>
#include <QVideoWidget>
#include "cwebwidget.h"
#include <Qt>

AssistantWindow::AssistantWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AssistantWindow),webTalk(new CWebWidget(this)),webBook(new CWebWidget(this)),webNews(new CWebWidget(this))
{
    ui->setupUi(this);
    webTalk->resize(600,600);
    webBook->resize(this->geometry().width() + 500,this->geometry().height()+150);
    webTalk->load(QUrl::fromLocalFile("/opt/html/index.htm"));
    webBook->load(QUrl::fromLocalFile("/opt/html/left.htm"));
    webNews->load(QUrl::fromLocalFile("/opt/html/news.htm"));
    webNews->resize(600,600);
    initLayout();
}

AssistantWindow::~AssistantWindow()
{
    delete ui;
}

void AssistantWindow::initLayout()
{
    QWidget *win = new QWidget(this);
    QVBoxLayout *vbox = new QVBoxLayout();
    QHBoxLayout *hbox = new QHBoxLayout(win);

   // vbox->setSpacing(1);
  //  vbox->addStretch(1);
    vbox->addWidget(webNews);
    vbox->addWidget(webTalk);
  //  vbox->addStretch(1);
    vbox->setAlignment(webTalk,Qt::AlignBottom);

    hbox->addWidget(webBook);
    hbox->addSpacing(2);
    hbox->addLayout(vbox);

    win->setStyleSheet("QWidget { background-image:url(\"/opt/html/bg.jpg\"); background-position: center;}");
    setCentralWidget(win);


}
