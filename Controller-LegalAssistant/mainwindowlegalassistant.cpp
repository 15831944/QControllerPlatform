#include "mainwindowlegalassistant.h"
#include "ui_mainwindowlegalassistant.h"

MainWindowLegalAssistant::MainWindowLegalAssistant(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowLegalAssistant)
{
    ui->setupUi(this);
}

MainWindowLegalAssistant::~MainWindowLegalAssistant()
{
    delete ui;
}
