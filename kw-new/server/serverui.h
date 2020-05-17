#ifndef SERVERUI_H
#define SERVERUI_H

#include <QMainWindow>
#include "servertools.h"

namespace Ui {
class ServerUi;
}

class ServerUi : public QMainWindow
{
    Q_OBJECT

public:
    explicit ServerUi(int port, QWidget *parent = nullptr);
    ~ServerUi();

private slots:

    void on_start_clicked();
    void on_stop_clicked();
    void printIP(QString);

    void on_portToBroadcast_cursorPositionChanged(int arg1, int arg2);

private:
    void findMaps();
    void setupTools(const QString & serverName);

    Ui::ServerUi *ui;
    ServerTools * tools;
    int portForSending;
};

#endif // SERVERUI_H
