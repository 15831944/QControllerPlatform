#ifndef CWEBWIDGET_H
#define CWEBWIDGET_H


#include <QWebEngineView>


class CWebWidget : public QWebEngineView
{
    Q_OBJECT
public:
    explicit CWebWidget(QWidget *parent = nullptr);
    void loadURL(const char *strURL);

signals:

public slots:


};

#endif // CWEBWIDGET_H
