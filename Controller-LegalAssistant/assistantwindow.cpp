#include "assistantwindow.h"
#include "ui_assistantwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include "cwebwidget.h"

AssistantWindow::AssistantWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AssistantWindow),webTalk(new CWebWidget(this)),webBook(new CWebWidget(this))
{
    ui->setupUi(this);
    webTalk->resize(600,800);
    webBook->resize(this->geometry().width() + 500,this->geometry().height());
    webTalk->load(QUrl::fromLocalFile("/opt/html/index.htm"));
    webBook->load(QUrl::fromLocalFile("/opt/html/left.htm"));
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

//    QListWidget *lw = new QListWidget(this);
//    lw->addItem("The Omen");
//    lw->addItem("The Exorcist");
//    lw->addItem("Notes on a scandal");
//    lw->addItem("Fargo");
//    lw->addItem("Capote");

    vbox->setSpacing(3);
    vbox->addStretch(1);
    vbox->addWidget(webTalk);
    vbox->addStretch(1);

    hbox->addWidget(webBook);
    hbox->addSpacing(2);
    hbox->addLayout(vbox);

    win->setStyleSheet("QWidget { background: white; }");
    setCentralWidget(win);


    int h = win->geometry().height();
    int w = win->geometry().width();
        int x = win->geometry().x();
        int y = win->geometry().y();

        webTalk->setGeometry( w - 800, 100, 800, 800 );

}
