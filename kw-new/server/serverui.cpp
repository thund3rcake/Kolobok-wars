#include "serverui.h"
#include "ui_serverui.h"
#include <QDebug>
#include <QDir>

ServerUi::ServerUi(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ServerUi),
    tools(NULL)
{
    setFixedSize(530, 255);
    ui->setupUi(this);
    findMaps();
}

ServerUi::~ServerUi()
{
    delete ui;
}

void ServerUi::findMaps() {
    QDir mapDirectory("./maps/");
    QStringList maps = mapDirectory.entryList(QDir::Dirs, QDir::Name);
    foreach (QString name, maps) {
        if (name != "." && name != "..") {
            mapDirectory.cd(name);
            if (mapDirectory.exists(name + ".xml")) {
                ui->mapName->addItem(name);
            }
            mapDirectory.cdUp();
        }
    }
}

void ServerUi::setupTools(const QString &serverName) {
    if (tools == NULL) {
        bool ok;
        tools = new ServerTools(
                                serverName,
                                ui->mapName->currentText(),
                                ui->port->currentText().toInt(&ok, 10),
                                (quint8)(ui->players->value()),
                                (quint8)(ui->bots->value()),
                                ui->console,
                                this
                                );
        ui->console -> insertHtml( "Starting broadcast... &nbsp" );
        tools -> getBroadcastSender().start();
        ui->console -> insertHtml( "[DONE]<br />" );

        ui->console -> insertHtml( "Starting udp server... &nbsp" );
        tools -> getUdpServer().start();
        ui->console -> insertHtml( "[DONE]<br />" );

        ui->console -> insertHtml( "==========================<br />" );
        ui->console -> insertHtml( "<b>Kolobok Wars Server " +
                               QString().number( Net::ProtVersion, 10 ) +
                               "." +
                               QString().number( Net::ProtSubversion, 10 ) +
                               "</b><br />"
                              );
        ui->console -> insertHtml( "port: \"" +
                               ui->port -> currentText() +
                               "\"<br />"
                              );
        ui->console -> insertHtml( "name: \"" + serverName + "\"<br />" );
        ui->console -> insertHtml( "map: \"" + ui->mapName -> currentText() + "\"<br />" );
        ui->console -> insertHtml(
                               "max. players: \"" +
                               QString().number( ui->players -> value(), 10 ) +
                               "\"<br />"
                              );
        ui->console -> insertHtml( "==========================<br />" );
    } else {
        ui->console -> insertHtml( "<b>Server already has been started</b><br />" );
    }
}

void ServerUi::on_start_clicked() {
    QString serverName = ui->serverName->text().simplified();
    qint8 j = 0;
    while ((j = serverName.indexOf(" ", j)) != -1) {
        serverName.replace(j, 1, "_");
    }

    if (serverName.length() == 0) {
        ui->console->insertHtml( "You should set \"Server Name\"<br />" );
        return;
    }

    setupTools(serverName);
}

void ServerUi::on_stop_clicked() {
    if (tools) {
        delete tools;
        tools = NULL;

        ui->console->clear();
        ui->console->insertHtml( "Server stopped.<br />" );
    }
}
