#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "cwebwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
/*
    CWebWidget *webWidget = new CWebWidget(this);
    webWidget->loadURL("https://www.google.com");
    webWidget->show();
    webWidget->resize(500,500);*/
    //setCentralWidget(webWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
