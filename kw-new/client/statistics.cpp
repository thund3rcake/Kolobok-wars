#include <Statistics.h>
#include <HUDStyleSheets.h>
#include <Utils.h>
#include <QHeaderView>
#include <QTableWidget>

Statistics::Statistics ( QWidget * parent ):
    QWidget(parent) {
    setStyleSheet(statistics);
    setFixedHeight(8*getDesktopSize().y()/10);
    setFixedWidth(8*getDesktopSize().x()/10);
    move(getDesktopSize().x()/10, getDesktopSize().y()/10);

    QVBoxLayout * layout = new QVBoxLayout;
    QLabel * label = new QLabel("Kolobok Wars");
    QLabel * tabUp = new QLabel;
    tabUp -> setFixedHeight(1);
    tabUp -> setFixedWidth(this -> width()-18);
    tabUp -> setStyleSheet(tab);
    QLabel * tabDown = new QLabel;
    tabDown -> setFixedHeight(1);
    tabDown -> setFixedWidth(this->width()-18);
    tabDown -> setStyleSheet(tab);
    label -> setStyleSheet(title);

    QTableWidget * table = new QTableWidget(6,4);

    table->setGridStyle(Qt::NoPen);
    table -> verticalHeader() -> hide();
    table -> horizontalHeader() -> hide();

    table->setColumnWidth(1, this->width()/6); //score
    table->setColumnWidth(2, this->width()/6); //deaths
    table->setColumnWidth(3, this->width()/6); //Latency
    table->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);

    QWidget * tableTitleWidget = new QWidget;

    QHBoxLayout * tableTitle = new QHBoxLayout;
    QLabel * name    = new QLabel("Name");
    QLabel * score   = new QLabel("Score");
    QLabel * deaths  = new QLabel("Deaths");
    QLabel * latency = new QLabel("Latency");

    name-> setStyleSheet(head);
    score-> setStyleSheet(head);
    deaths-> setStyleSheet(head);
    latency -> setStyleSheet(head);

    tableTitle -> addWidget(name);
    tableTitle -> addWidget(score);
    tableTitle -> addWidget(deaths);
    tableTitle -> addWidget(latency);

    tableTitle -> setStretchFactor(name, 3);
    tableTitle -> setStretchFactor(score, 1);
    tableTitle -> setStretchFactor(deaths, 1);
    tableTitle -> setStretchFactor(latency, 1);

    tableTitleWidget -> setLayout(tableTitle);

    layout -> setSpacing(0);
    layout -> addWidget(label);
    layout -> addWidget(tabUp);
    layout -> addWidget(tableTitleWidget);
    layout -> addWidget(tabDown);
    layout -> addWidget(table);

    layout -> setStretchFactor(label, 4);
    layout -> setStretchFactor(tabUp, 1);
    layout -> setStretchFactor(tableTitleWidget, 4);
    layout -> setStretchFactor(tabDown, 1);
    layout -> setStretchFactor(table, 120);



    setLayout(layout);
}

void Statistics::updateStatistic ()
{

}