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
    void initWeb(CWebWidget *webwidget);
private:
    Ui::AssistantWindow *ui;
    CWebWidget *webTalk;
    CWebWidget *webBook;
    CWebWidget *webNews;
    QTimer *timer;

public slots:
    void MySlot();
};

#endif // ASSISTANTWINDOW_H
