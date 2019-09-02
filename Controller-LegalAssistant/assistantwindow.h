#ifndef ASSISTANTWINDOW_H
#define ASSISTANTWINDOW_H

#include <QMainWindow>

namespace Ui {
class AssistantWindow;
}

class CWebWidget;

class AssistantWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AssistantWindow(QWidget *parent = nullptr);
    ~AssistantWindow();

private:
    void initLayout();
private:
    Ui::AssistantWindow *ui;
    CWebWidget *webTalk;
    CWebWidget *webBook;
    CWebWidget *webNews;
};

#endif // ASSISTANTWINDOW_H
