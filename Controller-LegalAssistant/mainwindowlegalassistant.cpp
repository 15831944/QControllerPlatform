#include "mainwindowlegalassistant.h"
#include "ui_mainwindowlegalassistant.h"
#include "cwebwidget.h"
#include <QGridLayout>
#include <QtMultimedia>
#include <QtMultimediaWidgets>

MainWindowLegalAssistant::MainWindowLegalAssistant(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowLegalAssistant)
{
    ui->setupUi(this);
    webWidget = new CWebWidget(this);
    init();
}

MainWindowLegalAssistant::~MainWindowLegalAssistant()
{
    delete ui;
}

void MainWindowLegalAssistant::init()
{
    webWidget->setStyleSheet("QWidget { background: white; }");
    webWidget->load(QUrl::fromLocalFile("/opt/html/index.htm"));
    webWidget->resize(200,200);
    webWidget->show();

    QWidget *wLayout = new QWidget(this);
    wLayout->setStyleSheet("QWidget { background: white; }");
    this->setCentralWidget(wLayout);

    QWidget *wTemp = new QWidget(this);
    wTemp->resize(500,500);
    wTemp->setStyleSheet("QWidget { background: white; }");
    QWidget *wTemp2 = new QWidget(this);
    wTemp2->resize(500,500);
     wTemp2->setStyleSheet("QWidget { background: white; }");

    QGridLayout *lgrid = new QGridLayout(wLayout);
    lgrid->setMargin(0);
 //   lgrid->addWidget(wTemp, 0, 0, 1, 1);
    lgrid->addWidget(wTemp2, 0, 1, 1, 1);
    lgrid->addWidget(webWidget, 0, 2, 1, 1);

    QWindow *window = QWindow::fromWinId(0x03800003);
    window->setFlags(Qt::FramelessWindowHint);
    QWidget *widget = QWidget::createWindowContainer(window);
    lgrid->addWidget(widget, 0, 0, 1, 1);


//    QWindow *window = QWindow::fromWinId(5998);
//    window->setFlags(Qt::FramelessWindowHint);
//    QWidget *widget = QWidget::createWindowContainer(window);
//    lgrid->addWidget(webWidget, 0, 0, 3, 1);
}
