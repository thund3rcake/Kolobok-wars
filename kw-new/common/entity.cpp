#include "Entity.h"
#include <QDebug>
#include <QPainter>
#include <QGraphicsPolygonItem>
#include <QVector2D>

Entity::Entity () {
    this->id = NOT_VALID;
}

bool Entity::setId (int ID) {
    if (this->isValid())
        return false;
    id = ID;
    return true;
}

bool Entity::isValid () {
    if (id >= 0)
        return true;
    else
        return false;
}

int Entity::getId () {
    return id;
}


PolygonEntity::PolygonEntity ():
    Entity(),              //TODO: cut it down
    QGraphicsPolygonItem()
{}

bool PolygonEntity::makeImage () { //используется только в клиенте
    /*возвращает true, если присвоила значение pixmap*/

    boundRect = boundingRect().toRect();
    QImage * image;
    if (overlay == Native) {
    /*помещает текстуру из texturePath в image*/

        // ! QImage::QImage( !const! QString &fileName, const char *format = nullptr)
        image = new QImage(texturePath);

        if (image->isNull()) {
            qDebug() << "EntityID:" << id << "Texture wasn't found";
            //если верить документации, qDebug() расставляет кавычки и пробелы, std::endl не поддерживается
            return false;
        }

    } else if (overlay == Tiled) {
        /*рисует image используя картинку из TexturePath*/

        //QImage(const QString &fileName, const char *format = nullptr)
        image = new QImage(boundRect.size(), QImage::Format_ARGB32);

        //Fills the image with the given color, described as a standard global color. (c)
        image->fill(125);

        const QImage * brushImg = new QImage(texturePath);
        if (brushImg->isNull()) {
            return false;
        }

        QPainter imagePainter(image);
        QPolygonF tmpPolygon;
        QPointF tmpPoint;

        //foreach (variable, container) statement. (c)
        //итерируется по точкам и добавляет их в tmpPolygon (c)

        foreach(QPointF point, this->polygon().toList()) { //!!!
            tmpPoint.rx() = point.x() - boundRect.topLeft().x();
            tmpPoint.ry() = point.y() - boundRect.topLeft().y();

            tmpPolygon << tmpPoint;
            //operator<<(tmpPolygon, tmpPoint);
        }

        imagePainter.setBrush(QBrush(*brushImg));
        imagePainter.setPen(Qt::NoPen);

        //Draws the polygon (многоугольник) defined by the points
        //using the current pen and brush.
        imagePainter.drawPolygon(tmpPolygon);

        //imagePainter.end();
        //You don't normally need to call this since it is called by the destructor (c)
    } else {
        // Extanded?
        // image = new QImage(...);
        // ...
        return false;
    }

    pixmap = new QPixmap;
    *pixmap = (pixmap->fromImage(*image));

    delete image;

    return true;
}

QString PolygonEntity::getTexturePath() {
    return texturePath;
}

void PolygonEntity::setTexturePath (QString path) {
    texturePath = path;
}

void PolygonEntity::paint (
                          QPainter * painter,
                          const QStyleOptionGraphicsItem *,
                          QWidget *
                          )
{
    painter -> drawPixmap(boundRect, *pixmap);
}

MovingEntity::MovingEntity (
                           int ID,
                           QPointF position,
                           QVector2D intention
                           ):
    Entity(ID),
    position(position),
    intent(intention)
{}

void MovingEntity::setIntent (const QVector2D & intention) {
    intent = intention;
}

void MovingEntity::setPosition (const QPointF & pos) {
    position = pos;
}

const QPointF & MovingEntity::getPosition () {
    return position;
}