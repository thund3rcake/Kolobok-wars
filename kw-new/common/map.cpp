#include <Map.h>
#include <XmlParser.h>
#include <GeometryAlgorithms.h>
#include <Utils.h>
#include <GameWorldConsts.h>
#include <Entity.h>

QPoint abstractMap::getSize () {
    return QPoint(m_sizeW, m_sizeH);
}

void abstractMap::setSize (uint width, uint height) {
  this->m_sizeW = width;
  this->m_sizeH = height;
}

const QString& abstractMap::getName () {
  return name;
}

void abstractMap::setName(const QString& name) {
  this->name = name;
}

int abstractMap::getPlayerAmount() {
  return playersAmount;
}

void abstractMap::setPlayerAmount(int amnt) {
  this->playersAmount = amnt;
}

abstractNoAIMap::abstractNoAIMap(QString mapPath) {
  XmlHandler handler (*this, mapPath);

  if (!handler.parseXML()) {
    throw Exception ( -1, "Wrong Map-file" );
  }

  availableDots = QVector<QVector<quint8>>(m_sizeW, QVector<quint8>(m_sizeH));

  for (QVector<QVector<quint8> >::iterator i = availableDots.begin(); i != availableDots.end(); ++i) {
    i->fill(0, i->size());
  }
}

bool abstractNoAIMap::isThereSDotFile() {
  QFile file("./maps/" + name + "/" + name + ".dot");
  if (file.open(QIODevice::ReadOnly ) == false) {
    return false;
  }
  else {
    file.close();
    return true;
  }
  return false;
}

bool abstractNoAIMap::load_sDOT_file() {
  QFile file("./maps/" + name + "/" + name + ".dot");
  if (file.open(QIODevice::ReadOnly ) == false) {
    return false;
  }
  QDataStream dotData(&file);
  dotData.setVersion(QDataStream::Qt_4_0);

  dotData >> availableDots;
  return true;
}

bool abstractNoAIMap::write_sDOT_file() {
  QFile file("./maps/" + name + "/" + name + ".dot");
  if (file.open(QIODevice::WriteOnly ) == false) {
    return false;
  }

  QDataStream dotData(&file);
  dotData.setVersion(QDataStream::Qt_4_0);
  dotData << availableDots; //TODO: what if file smaller than needs?
  return true;
}


void abstractNoAIMap::findAvailblDots () {
  if (isThereSDotFile ()) {
    if (load_sDOT_file() == false)
      emit error (-1, "Wrong dot-file");
    return;
  }

  QList<PolygonEntity*> suspiciousPols;

  QPointF dot;
  for (uint i = 0; i < m_sizeW; i++) {
    for (uint j = 0; j < m_sizeH; j++) {
      suspiciousPols.clear();
      dot.setX(i);
      dot.setY(j);

      if (isDotInAnyRect ( dot, polygons, suspiciousPols))
        if (isDotInAnyPolygon (dot, suspiciousPols))
          markTheNearest (i, j, i, j, availableDots);
    }
  }

  double playerRadius = consts::playerSize;
  for (uint i = 0; i < m_sizeW; i++) {
    for(uint j = 0; j < playerRadius; j++) {
      availableDots[i][j] = 1;
    }
    for(uint j = m_sizeH - 1; j > m_sizeH - playerRadius; j--) {
      availableDots[i][j] = 1;
    }
  }
  for(uint j = 0; j < m_sizeH; j++) {
    for(uint i = 0; i < playerRadius; i++) {
      availableDots[i][j] = 1;
    }
    for(uint i = m_sizeW - 1; i > m_sizeW - playerRadius; i--) {
      availableDots[i][j] = 1;
    }
  }
  if (write_sDOT_file() == false)
    emit error (-1, "Cannot write dot-file");
}

inline bool isDotInAnyRect (
                            QPointF dot,
                            QList<PolygonEntity*> & polygons,
                            QList<PolygonEntity*> & suspiciousPols
                           )
{

#ifdef KOLOBOK_CLIENT
  dot = dot*scale_x_100()/100;
#endif

  foreach (PolygonEntity* entity, polygons) {
    if (dot.x() >= entity->boundingRect().topLeft().rx()     &&
        dot.y() >= entity->boundingRect().topLeft().ry()     &&
        dot.x() <= entity->boundingRect().bottomRight().rx() &&
        dot.y() <= entity->boundingRect().bottomRight().ry()) {
      suspiciousPols.append(entity);
    }
  }
  if (suspiciousPols.isEmpty())
    return false;
  else
    return true;
}

void markTheNearest (
                     int x,    int y,
                     int srcX, int srcY,
                     QVector<QVector<quint8> > & availableDots
                    ) {
  static double size = consts::playerSize;
  static double maxRadius = (size + 0.5) * size;

  if ( x < 0 ||
       y < 0 ||
       x > availableDots.size() - 1 ||
       y > availableDots[0].size() - 1
       )
      return;

  int radius = (srcX - x) * (srcX - x) + (srcY - y) * (srcY - y);

  if (availableDots[x][y] <= radius && availableDots[x][y] != 0)
      return;
  if ( radius > maxRadius )
      return;
  if ( radius == 0 )
      radius = 1;
  availableDots[x][y] = radius;

  markTheNearest( x+1, y, srcX, srcY, availableDots );
  markTheNearest( x-1, y, srcX, srcY, availableDots );
  markTheNearest( x, y+1, srcX, srcY, availableDots );
  markTheNearest( x, y-1, srcX, srcY, availableDots );
}

bool abstractNoAIMap::isDotAvailable (QPoint dot) {

#ifdef KOLOBOK_CLIENT
  dot = dot*100/scale_x_100();
#endif

  if ( (uint)dot.rx() >= m_sizeW || (uint)dot.ry() >= m_sizeH )
    return false;
  else {
    if ( availableDots[dot.x()][dot.y()] > 0 )
      return false;
    else
      return true;
  }
}

bool abstractNoAIMap::addPolygon ( PolygonEntity* polygon ) {
  if (polygon->isValid()) {
    polygons << polygon;
    return true;
  } else
  return false;
}

QString abstractNoAIMap::getBackgroundPath () {
  return backgroundPath;
}

const QList<PolygonEntity*> &  abstractNoAIMap::getPolygons () {
  return polygons;
}

#ifdef KOLOBOK_CLIENT

Map::Map (QString mapPath):
  abstractNoAIMap(mapPath) {
  foreach ( PolygonEntity* entity, getPolygons() ) {
    entity->makeImage();
  }
  abstractNoAIMap::findAvailblDots ();
}

#endif

#ifdef KOLOBOK_SERVER

Map::Map (QString mapPath):
  abstractNoAIMap(mapPath) {
  abstractNoAIMap::findAvailblDots ();
}

#endif
