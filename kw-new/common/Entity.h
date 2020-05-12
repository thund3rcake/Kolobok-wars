#ifndef ENTITY_CLASS_H_
#define ENTITY_CLASS_H_

#include <QGraphicsPolygonItem>
#include <QVector2D>
#include <CommonGlobal.h>

const int NOT_VALID = -1;

class KW_COMMON_EXPORT Entity: public QObject {
    Q_OBJECT
    friend class KW_COMMON_EXPORT XmlHandler;

public:
    Entity ();
    Entity (int id): id(id) {}

    bool isValid ();
    int getId ();
    bool setId (int ID);

protected:
    int id;

private:
    Entity (const Entity & rhs);
    Entity & operator= (const Entity &rhs);

signals:
    void error (int, QString);
};

class KW_COMMON_EXPORT PolygonEntity: public Entity, public QGraphicsPolygonItem {

    friend class KW_COMMON_EXPORT XmlHandler;

public:
    PolygonEntity ();

    virtual
    void paint (
               QPainter * painter,
               const QStyleOptionGraphicsItem * option,
               QWidget * widget = nullptr
               );
    QString getTexturePath ();
    bool makeImage ();

    enum OverlayModes {Tiled, Extended, Native};
private:
    PolygonEntity (const PolygonEntity& rhs);
    PolygonEntity& operator= (const PolygonEntity& rhs);

    void setTexturePath (QString path);

    QPixmap* pixmap;

    QRect boundRect;
    QString texturePath;
    bool animated;
    OverlayModes overlay;
};

class KW_COMMON_EXPORT MovingEntity: public Entity {
    Q_OBJECT

public:
    MovingEntity () {}
    MovingEntity (int, QPointF, QVector2D);

    void setIntention (const QVector2D);
    void setPosition (const QPointF&);

    const QPointF getPosition ();
    const QVector2D getIntention ();

protected:
    QPointF position;
    QVector2D intent;

private:
    MovingEntity (const MovingEntity & rhs);
    MovingEntity & operator= (const MovingEntity & rhs);
};

#endif /* ENTITY_CLASS_H_ */
