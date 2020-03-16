/*
 *  Created on: 01.05.2012
 *
 * GamePanel.cpp
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

#include <GamePanel.h>

GamePanel::GamePanel():
  hpVal(100),
  ammoVal(100),
  secsVal(0),
  minsVal(0)

{
  QLabel  * hp      = new QLabel("HP ");
  QLabel  * ammo    = new QLabel("AMMO ");
  hpValLabel    = new QLabel("99");
  ammoValLabel  = new QLabel("100");
  timerValLabel = new QLabel("0:00");

  int fontId = QFontDatabase::addApplicationFont("./fonts/digitalFont.ttf");
  if ( fontId == 0 )
  {
    font = new QFont(QFontDatabase::applicationFontFamilies(fontId).first(),48);
    hp->setFont(*font);
    hpValLabel->setFont(*font);
    timerValLabel->setFont(*font);
    ammo->setFont(*font);
    ammoValLabel->setFont(*font);
  }
  else
  {
    qDebug() << "GamePanel" << (void*)this <<
              "::GamePanel:" << "Couldn't loaded game font"
                             << "./fonts/digitalFont.ttf";
  }

  hp->setStyleSheet(HUDStyle::panel);
  hpValLabel->setStyleSheet(HUDStyle::panel);
  timerValLabel->setStyleSheet(HUDStyle::panel);
  ammo->setStyleSheet(HUDStyle::panel);
  ammoValLabel->setStyleSheet(HUDStyle::panel);

  addWidget(hp);
  addWidget(hpValLabel);
  addStretch();
  addWidget(timerValLabel);
  addStretch();
  addWidget(ammo);
  addWidget(ammoValLabel);
}

GamePanel::~GamePanel ()
{
  delete font;
  QFontDatabase::removeAllApplicationFonts();
}

uint GamePanel::getAmmo() const
{
    return ammoVal;
}

uint GamePanel::getHp() const
{
    return hpVal;
}

uint GamePanel::getMins() const
{
    return minsVal;
}

uint GamePanel::getSecs() const
{
    return secsVal;
}

void GamePanel::setAmmo(uint ammo)
{
    this->ammoVal = ammo;
    ammoValLabel->setText(QString().number(ammo));
}

void GamePanel::setHp(uint hp)
{
    this->hpVal = hp;
    hpValLabel->setText(QString().number(hp));
}

void GamePanel::setMins(uint mins)
{
    this->minsVal = mins;
}

void GamePanel::setSecs(uint secs)
{
    this->secsVal = secs;
}
