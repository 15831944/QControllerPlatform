#ifndef MAINWINDOWLEGALASSISTANT_H
#define MAINWINDOWLEGALASSISTANT_H

#include <QMainWindow>

namespace Ui {
class MainWindowLegalAssistant;
}

class MainWindowLegalAssistant : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowLegalAssistant(QWidget *parent = nullptr);
    ~MainWindowLegalAssistant();

private:
    Ui::MainWindowLegalAssistant *ui;
};

#endif // MAINWINDOWLEGALASSISTANT_H
