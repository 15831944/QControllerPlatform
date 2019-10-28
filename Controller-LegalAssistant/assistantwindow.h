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
    void showText(std::string strInput,std::string strResp,std::string strImage, int nIntentId);

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
    QString strPathSound;

public: signals:
    void signalShowText(QString strInput,QString strResp,QString strImage, int nIntentId);

public slots:
    void slotQueryShow();
    void slotStopTalk();
    void stateChanged(QMediaPlayer::State state);
    void positionChanged(qint64 position);
    void slotShowText(QString strInput,QString strResp,QString strImage, int nIntentId);
};

#endif // ASSISTANTWINDOW_H
