/*
 *  Created on: 29.04.2012
 *
 * HUD.cpp
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

#include <HUD.h>
#include <commonLibs.h>
#include <HUDStyleSheets.h>


HUD::HUD ():
  bottomPanel(new GamePanel()),
  console(new Console(this)),
  statistics(new Statistics(this))
{
  setStyleSheet( "background-color: rgba(255, 255, 255, 0%);" );
  setFixedSize(QSize(getDesktopSize().x() - 2, getDesktopSize().y() - 2));

  vLayout = new QVBoxLayout;
  setLayout(vLayout);

  topHLayout = new QHBoxLayout;

  topHLayout->addWidget(console);
  topHLayout->addStretch();

  vLayout->addLayout (topHLayout);
  vLayout->addStretch ();
  vLayout->addLayout (bottomPanel);

  statistics->hide();
}

void HUD::updateConsole ( Player* player,
                          const QPointF & topLeft,
                          bool avail )
{
  console->setPlayerPos ( player -> getPosition().toPoint()*100/scale_x_100() );
  console->setHeading   ( player -> getHead() );
  console->setIntention ( player -> getIntention() );
  console->setTopLeft (topLeft);
  console->setAvailable (avail);

}

void HUD::updConsFireTargt (const QPointF & trgt)
{
  console->setFireTargt(trgt);
}

HUD::~HUD()
{
  delete bottomPanel;
}

void  HUD::keyPressEvent ( QKeyEvent * event )
{
  if ( event->key() == Qt::Key_Tab )
  {
    statistics->show();
    console->hide();
  }
}

void  HUD::keyReleaseEvent ( QKeyEvent * event )
{
  if ( event->key() == Qt::Key_Tab )
  {
    statistics->hide();
    console->show();
  }
}
