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
    void showText(const char* szInput);

private:
    void initLayout();
    void initWeb(CWebWidget *webwidget);
private:
    Ui::AssistantWindow *ui;
    CWebWidget *webTalk;
    CWebWidget *webBook;
    CWebWidget *webNews;
    QTimer *timer;

signals:
    void singalsShowText(QString strText);

public slots:
    void MySlot();
    void slotShowText(QString strText);

};

#endif // ASSISTANTWINDOW_H
