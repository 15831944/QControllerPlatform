#ifndef MAINWINDOWLEGALASSISTANT_H
#define MAINWINDOWLEGALASSISTANT_H

#include <QMainWindow>

namespace Ui {
class MainWindowLegalAssistant;
}

class CWebWidget;

class MainWindowLegalAssistant : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowLegalAssistant(QWidget *parent = nullptr);
    ~MainWindowLegalAssistant();

private:
    void init();

private:
    Ui::MainWindowLegalAssistant *ui;
    CWebWidget *webWidget;
    CWebWidget *webWidget2;
    QWindow *extWindow;
};

#endif // MAINWINDOWLEGALASSISTANT_H
