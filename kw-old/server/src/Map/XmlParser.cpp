/*
 *  Created on: 25.03.2012
 *
 * XML_Parser.cpp
 *
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
#include <XmlParser.h>
#include <QDebug>
#include <commonLibs.h>
#include <GameWorldConsts.h>

XmlHandler::XmlHandler (abstractNoAIMap& map, QString file) :
    dest(map),
    filename (file),
    entityID (0),
    polygon (),
    isNewEntityDefined (false),
    isThereMapTag (false),
    isThereRespawnTag (false)
{}

bool XmlHandler::startElement (
                              const QString &/*namespaceURI*/,
                              const QString &/*localName*/,
                              const QString &qName,
                              const QXmlAttributes &attributes
                              )
{

  if ( qName == "map" )
  {
    isThereMapTag = true;
    if ( attributes.value("size_w") < 0 ||
         attributes.value("size_h") < 0 )
      return false;
    dest.setSize(
                 attributes.value("size_w").toUInt(),
                 attributes.value("size_h").toUInt()
                );
    dest.setName( attributes.value("name") );
    dest.setPlayerAmount( attributes.value("players_amnt").toInt() );
  }

  if ( qName == "wall" )
  {
    isNewEntityDefined = true;
    curEntity = new PolygonEntity;
  }

  if ( qName == "point" )
  {
    if ( attributes.value("dotX").toUInt() > dest.m_sizeW ||
         attributes.value("dotY").toUInt() > dest.m_sizeH   )
    {
      return false;
    }

    if ( isNewEntityDefined == false ) return false;
#ifdef KOLOBOK_CLIENT
    polygon << QPoint (
                       attributes.value("dotX").toInt()*scale_x_100()/100,
                       attributes.value("dotY").toInt()*scale_x_100()/100
                      );
#endif

#ifndef KOLOBOK_CLIENT
    polygon << QPoint (
                       attributes.value("dotX").toInt(),
                       attributes.value("dotY").toInt()
                      );
#endif
  }

  if ( qName == "texture" )
  {
    if ( isNewEntityDefined == false ) return false;

    if ( attributes.value("overlay") == "tiled" )
    {
      curEntity->overlay = PolygonEntity::Tiled;
    }
    else if ( attributes.value("overlay") == "native" )
    {
      curEntity->overlay = PolygonEntity::Native;
    }
    else
    {
      curEntity->overlay = PolygonEntity::Tiled;
    }

    if ( attributes.value("animated") == "yes" )
    {
      curEntity->animated = true;
    }
    else
    {
      curEntity->animated = false;
    }

  }

  if ( qName == "respawn_place" )
  {
    isThereRespawnTag = true;
    if ( attributes.value("dotX").toUInt() > dest.m_sizeW ||
         attributes.value("dotY").toUInt() > dest.m_sizeH )
    {
      return false;
    }

    dest.m_respawnPlaces << QPoint (
                                    attributes.value("dotX").toUInt(),
                                    attributes.value("dotY").toUInt()
                                   );
  }
  return true;
}

bool XmlHandler::characters (const QString &str)
{
  currentText = str;
  return true;
}

bool XmlHandler::endElement (
                             const QString &/*namespaceURI*/,
                             const QString &/*localName*/,
                             const QString &qName
                            )
{
  if ( qName == "background" )
  {
    dest.backgroundPath = currentText;
  }

  if ( qName == "wall" )
  {
    entityID++;

    if ( curEntity->setId (entityID) == false ) return false;

    curEntity->setPolygon (polygon);
    polygon.clear();

    if ( dest.addPolygon(curEntity) == false ) return false;

    isNewEntityDefined = false;
  }

  if ( qName == "texture" )
  {
    curEntity->setTexturePath ( "./maps/" + dest.name + "/"+ currentText );
  }
  return true;
}

bool XmlHandler::fatalError (const QXmlParseException & /*exception*/)
{
  /*QMessageBox::warning (
                        0,
                        QObject::tr("XML Reading Error"),
                        QObject::tr("Parse error at line %1, column %2:\n%3.")
                        .arg(exception.lineNumber())
                        .arg(exception.columnNumber())
                        .arg(exception.message())
                       );*/
  return false;
}

bool XmlHandler::parseXML ()
{
  QFile file(filename);

  QXmlInputSource inputSource (&file);
  QXmlSimpleReader reader;
  reader.setContentHandler(this);
  reader.setErrorHandler(this);

  if ( reader.parse(inputSource) )
  {
    qDebug() << "XmlHandler::parseXML" << "file was successfully parsed";
    if ( isThereMapTag && isThereRespawnTag )
      return true;
    else
      return false;
  }
  qDebug() << "XmlHandler::parseXML" << "parsing failed";
  return false;
}
