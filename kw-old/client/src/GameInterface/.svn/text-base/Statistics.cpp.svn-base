/*
 *  Created on: 10.05.2012
 *
 * Statistics.cpp
 * This file is part of kolobok-wars-client
 *
 * Copyright (C) 2012 - Krepak Vitaly, MIPT
 * krepakvitaliy@gmail.com
 *
 * kolobok-wars-client is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * kolobok-wars-client is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with kolobok-wars-client if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 *
 */

#include <Statistics.h>
#include <HUDStyleSheets.h>
#include <commonLibs.h>
#include <QTableWidget>

Statistics::Statistics ( QWidget * parent ):
  QWidget(parent)
{
  setStyleSheet(HUDStyle::statistics);
  setFixedHeight ( 8*getDesktopSize().y()/10 );
  setFixedWidth  ( 8*getDesktopSize().x()/10 );
  move( getDesktopSize().x()/10, getDesktopSize().y()/10 );

  QVBoxLayout * layout = new QVBoxLayout;
  QLabel  * label = new QLabel("Kolobok Wars");
  QLabel  * tabUp = new QLabel;
  tabUp->setFixedHeight(1);
  tabUp->setFixedWidth(this->width()-18);
  tabUp->setStyleSheet(HUDStyle::tab);
  QLabel  * tabDown = new QLabel;
  tabDown->setFixedHeight(1);
  tabDown->setFixedWidth(this->width()-18);
  tabDown->setStyleSheet(HUDStyle::tab);
  label->setStyleSheet(HUDStyle::title);

  QTableWidget * table = new QTableWidget(6,4);

  //table->setGridStyle(Qt::NoPen);
  table->verticalHeader()->hide();
  table->horizontalHeader()->hide();

  table->setColumnWidth(1, this->width()/6); //score
  table->setColumnWidth(2, this->width()/6); //deaths
  table->setColumnWidth(3, this->width()/6); //Latency
  table->horizontalHeader()->setResizeMode(0,QHeaderView::Stretch); //name

  QWidget * tableTitleWidget = new QWidget;

  QHBoxLayout * tableTitle = new QHBoxLayout;
  QLabel * name    = new QLabel("Name");
  QLabel * score   = new QLabel("Score");
  QLabel * deaths  = new QLabel("Deaths");
  QLabel * latency = new QLabel("Latency");

  name->   setStyleSheet(HUDStyle::head);
  score->  setStyleSheet(HUDStyle::head);
  deaths-> setStyleSheet(HUDStyle::head);
  latency->setStyleSheet(HUDStyle::head);

  tableTitle->addWidget(name);
  tableTitle->addWidget(score);
  tableTitle->addWidget(deaths);
  tableTitle->addWidget(latency);

  tableTitle->setStretchFactor(name, 3);
  tableTitle->setStretchFactor(score, 1);
  tableTitle->setStretchFactor(deaths, 1);
  tableTitle->setStretchFactor(latency, 1);

  tableTitleWidget->setLayout(tableTitle);

  layout->setSpacing(0);
  layout->addWidget(label);
  layout->addWidget(tabUp);
  layout->addWidget(tableTitleWidget);
  layout->addWidget(tabDown);
  layout->addWidget(table);

  layout->setStretchFactor(label, 4);
  layout->setStretchFactor(tabUp, 1);
  layout->setStretchFactor(tableTitleWidget, 4);
  layout->setStretchFactor(tabDown, 1);
  layout->setStretchFactor(table, 120);



  setLayout(layout);
}

void Statistics::updateStatistic ()
{

}
