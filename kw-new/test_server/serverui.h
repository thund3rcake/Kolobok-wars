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
    explicit ServerUi(QWidget *parent = nullptr);
    ~ServerUi();

private slots:

    void on_start_clicked();

    void on_stop_clicked();

private:
    void findMaps();
    void setupTools(const QString & serverName);

    Ui::ServerUi *ui;
    ServerTools * tools;
};

#endif // SERVERUI_H
