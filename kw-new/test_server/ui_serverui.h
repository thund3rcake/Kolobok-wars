/********************************************************************************
** Form generated from reading UI file 'serverui.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVERUI_H
#define UI_SERVERUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ServerUi
{
public:
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_3;
    QFormLayout *formLayout_8;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_6;
    QTextEdit *console;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *serverName;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *port;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QComboBox *mapName;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_4;
    QSpinBox *players;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QSpinBox *bots;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *start;
    QPushButton *stop;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ServerUi)
    {
        if (ServerUi->objectName().isEmpty())
            ServerUi->setObjectName(QStringLiteral("ServerUi"));
        ServerUi->resize(517, 355);
        centralWidget = new QWidget(ServerUi);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 0, 501, 311));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        formLayout_8 = new QFormLayout();
        formLayout_8->setSpacing(6);
        formLayout_8->setObjectName(QStringLiteral("formLayout_8"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_6 = new QLabel(verticalLayoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setLayoutDirection(Qt::LeftToRight);
        label_6->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        verticalLayout_2->addWidget(label_6);

        console = new QTextEdit(verticalLayoutWidget);
        console->setObjectName(QStringLiteral("console"));
        console->setReadOnly(true);

        verticalLayout_2->addWidget(console);


        formLayout_8->setLayout(1, QFormLayout::FieldRole, verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label_7 = new QLabel(verticalLayoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(label_7);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        serverName = new QLineEdit(verticalLayoutWidget);
        serverName->setObjectName(QStringLiteral("serverName"));
        serverName->setMaxLength(12);

        horizontalLayout->addWidget(serverName);


        verticalLayout_4->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        port = new QComboBox(verticalLayoutWidget);
        port->setObjectName(QStringLiteral("port"));

        horizontalLayout_2->addWidget(port);


        verticalLayout_4->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        mapName = new QComboBox(verticalLayoutWidget);
        mapName->setObjectName(QStringLiteral("mapName"));

        horizontalLayout_3->addWidget(mapName);


        verticalLayout_4->addLayout(horizontalLayout_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_4 = new QLabel(verticalLayoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_6->addWidget(label_4);

        players = new QSpinBox(verticalLayoutWidget);
        players->setObjectName(QStringLiteral("players"));
        players->setMinimum(1);
        players->setMaximum(8);

        horizontalLayout_6->addWidget(players);


        verticalLayout_4->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_5 = new QLabel(verticalLayoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_5->addWidget(label_5);

        bots = new QSpinBox(verticalLayoutWidget);
        bots->setObjectName(QStringLiteral("bots"));
        bots->setMaximum(8);

        horizontalLayout_5->addWidget(bots);


        verticalLayout_4->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        start = new QPushButton(verticalLayoutWidget);
        start->setObjectName(QStringLiteral("start"));

        horizontalLayout_4->addWidget(start);

        stop = new QPushButton(verticalLayoutWidget);
        stop->setObjectName(QStringLiteral("stop"));

        horizontalLayout_4->addWidget(stop);


        verticalLayout_4->addLayout(horizontalLayout_4);


        verticalLayout->addLayout(verticalLayout_4);


        formLayout_8->setLayout(1, QFormLayout::LabelRole, verticalLayout);


        verticalLayout_3->addLayout(formLayout_8);

        ServerUi->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(ServerUi);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ServerUi->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ServerUi);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ServerUi->setStatusBar(statusBar);

        retranslateUi(ServerUi);

        QMetaObject::connectSlotsByName(ServerUi);
    } // setupUi

    void retranslateUi(QMainWindow *ServerUi)
    {
        ServerUi->setWindowTitle(QApplication::translate("ServerUi", "Server", Q_NULLPTR));
        label_6->setText(QApplication::translate("ServerUi", "Server info", Q_NULLPTR));
        label_7->setText(QApplication::translate("ServerUi", "Kolobok-wars server", Q_NULLPTR));
        label->setText(QApplication::translate("ServerUi", "Server name", Q_NULLPTR));
        label_2->setText(QApplication::translate("ServerUi", "Port", Q_NULLPTR));
        port->clear();
        port->insertItems(0, QStringList()
         << QApplication::translate("ServerUi", "27031", Q_NULLPTR)
         << QApplication::translate("ServerUi", "27032", Q_NULLPTR)
         << QApplication::translate("ServerUi", "27033", Q_NULLPTR)
         << QApplication::translate("ServerUi", "27034", Q_NULLPTR)
         << QApplication::translate("ServerUi", "27035", Q_NULLPTR)
        );
        label_3->setText(QApplication::translate("ServerUi", "Map", Q_NULLPTR));
        label_4->setText(QApplication::translate("ServerUi", "Players", Q_NULLPTR));
        label_5->setText(QApplication::translate("ServerUi", "Bots", Q_NULLPTR));
        start->setText(QApplication::translate("ServerUi", "Start", Q_NULLPTR));
        stop->setText(QApplication::translate("ServerUi", "Stop", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ServerUi: public Ui_ServerUi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERUI_H
