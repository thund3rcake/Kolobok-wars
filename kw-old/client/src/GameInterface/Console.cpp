/*
 *  Created on: 01.05.2012
 *
 * Console.cpp
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

#include <Console.h>
#include <commonLibs.h>

Console::Console ( QWidget * parent ):
  QWidget(parent)
{
  QWidget * consoleWidget = new QWidget;
  consoleWidget->setStyleSheet(HUDStyle::consoleBack);
  consoleWidget->setFixedWidth(300);

  QVBoxLayout * console = new QVBoxLayout;

  playerPos.setText("Player Position: ");
  topLeft  .setText("Top Left: ");
  availbl  .setText("Available: ");
  heading  .setText("Heading Vector: ");
  fireTargt.setText("Fire target: ");
  intention.setText("Intention Vector: ");

  consoleWidget->setLayout(console);

  playerPos.setStyleSheet (HUDStyle::console);
  topLeft  .setStyleSheet (HUDStyle::console);
  availbl  .setStyleSheet (HUDStyle::console);
  heading  .setStyleSheet (HUDStyle::console);
  intention.setStyleSheet (HUDStyle::console);
  fireTargt.setStyleSheet (HUDStyle::console);

  console->addWidget(&playerPos);
  console->addWidget(&topLeft);
  console->addWidget(&availbl);
  console->addWidget(&heading);
  console->addWidget(&intention);
  console->addWidget(&fireTargt);
  console->addStretch();

  QVBoxLayout * consoleLayout = new QVBoxLayout;
  setLayout(consoleLayout);
  consoleLayout->addWidget(consoleWidget);
}

void Console::setPlayerPos(const QPoint & pos)
{
  playerPos.setText("Player Position: x" + QString().number(pos.x())+
                    " y" + QString().number(pos.y()) );
}

void Console::setTopLeft(const QPointF & top)
{
  topLeft.setText("Top Left: \n\tx" + QString().setNum(top.x(),'f',7)+
                    "\n\ty" + QString().setNum(top.y(),'f',7) );
}

void Console::setAvailable(bool avail)
{
  if ( avail == true )
  {
    availbl.setStyleSheet(HUDStyle::console);
    availbl.setText("Available: true");
  }
  else
  {
    availbl.setStyleSheet(HUDStyle::consoleError);
    availbl.setText("Available: false");
  }
}

void Console::setHeading( const QVector2D & head)
{
  heading.setText("Heading vector: \n\tx" + QString().setNum(head.x(), 'f', 4)
                                + "\n\ty" + QString().setNum(head.y(), 'f', 4) );
}

void Console::setIntention ( const QVector2D & intn )
{
  intention.setText("Intention vector: \n\tx" + QString().setNum(intn.x(), 'f', 4)
                                    + "\n\ty" + QString().setNum(intn.y(), 'f', 4) );
}

void Console::setFireTargt ( const QPointF & trgt)
{
  QPointF tmp = trgt*100/scale_x_100();
  fireTargt.setText("Fire target: \n\tx" + QString().setNum(tmp.x(), 'f', 4)
                               + "\n\ty" + QString().setNum(tmp.y(), 'f', 4) );
}
