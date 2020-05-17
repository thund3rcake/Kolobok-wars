#ifndef LANTAB_H
#define LANTAB_H

#include <QtGui>
#include <QTreeWidget>

#include <ActivatableButton.h>
#include <Datagramms.h>
#include<BroadcastReceiver.h>

class LanTab : public QWidget {
    Q_OBJECT

public:
    explicit
    LanTab( QWidget * parent = 0 );

    ~LanTab();

private:
    LanTab();
    LanTab( const LanTab & rhs );
    LanTab & operator=( const LanTab & rhs );

    inline
    void tableInitialization();

    ActivatableButton       * lanRefresh;
    ActivatableButton       * lanConnect;
    QTreeWidget             * table;
    BroadcastReceiver  * receiver;

    QVector<ServerAbout> servers;
    QTimer                    timer;
    int                       curSelectedIndex;

    int port;

private slots:
    void refreshStart();
    void refreshStop();
    void addNewItem( int );
    void onServerSelection( QTreeWidgetItem *, int );
    void onConnectClicked();

signals:
    void error( int errNo, QString message );
    void startGame( const ServerAbout & connectionInfo );
};


#endif // LANTAB_H