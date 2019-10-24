#ifndef ASSISTANTWINDOW_H
#define ASSISTANTWINDOW_H

#include <QMainWindow>
#include <QtMultimedia/QMediaPlayer>

class CMysqlHandler;

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
    QTimer *timerQueryShow;
    QTimer *timerStopTalk;
    CMysqlHandler *mysql;
    QMediaPlayer *player;

public: signals:
    void singalsShowText(QString strText);

public slots:
    void slotQueryShow();
    void slotStopTalk();
    void playerState(QMediaPlayer::State state);

};

#endif // ASSISTANTWINDOW_H
