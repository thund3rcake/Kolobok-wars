#ifndef MAP_H
#define MAP_H

#include <QString>
#include <QVector>
#include <QVector2D>
#include <QTreeWidget>
#include <Utils.h>
#include <Entity.h>
#include <CommonGlobal.h>

class KW_COMMON_EXPORT abstractMap: public QObject
{
    friend class KW_COMMON_EXPORT XmlHandler;
public:
    abstractMap() {};
    const QString & getName ();
    QPoint getSize();
    int getPlayerAmount();

protected:
    uint m_sizeH;  //prefix 'm' means that this value belongs to map coordinates
    uint m_sizeW;  //prefix 'm' means that this value belongs to map coordinates
    int playersAmount;
    QString name;

    void setSize(uint height, uint width);
    void setName(const QString & str);
    void setPlayerAmount (int amnt);

private:
    abstractMap (const abstractMap& rhs);
    abstractMap & operator = (const abstractMap & rhs);
};


#ifndef KOLOBOK_BOT /* #IFDEF CLIENT || SERVER */

class KW_COMMON_EXPORT abstractNoAIMap: public abstractMap
{
Q_OBJECT
    friend class XmlHandler;
public:
    abstractNoAIMap(QString);

    bool isDotAvailable(QPoint dot);

    bool isThereSDotFile();
    bool load_sDOT_file();
    bool write_sDOT_file();

    QString getBackgroundPath();
    const QList<PolygonEntity*> & getPolygons();

protected:
    void findAvailblDots();
    bool addPolygon(PolygonEntity*);

private:
    abstractNoAIMap(const abstractNoAIMap & rhs);
    abstractNoAIMap & operator=(const abstractNoAIMap & rhs);

    QString backgroundPath;

    QList<PolygonEntity*> polygons;
    QVector<QVector<quint8> > availableDots;
    QVector<QPoint> m_respawnPlaces;

signals:
    void error (int, QString);
};

inline bool KW_COMMON_EXPORT isDotInAnyRect (
                            QPointF dot,
                            QList<PolygonEntity*> & polygons,
                            QList<PolygonEntity*> & suspiciousPols
                           );
void KW_COMMON_EXPORT markTheNearest (
                     int x, int y,
                     int srcX, int srcY,
                     QVector<QVector<quint8> > & availableDots
                    );

#endif

#ifdef KOLOBOK_BOT

class KW_COMMON_EXPORT Map: public abstractMap
{
private:
    Map (const Map & rhs);
    Map& operator = (const Map &rhs);
};

#endif

#ifdef KOLOBOK_CLIENT

class KW_COMMON_EXPORT Map : public abstractNoAIMap /* client map */ {
public:
    explicit Map(QString);

private:
    Map();
    Map(const Map &rhs);
    Map& operator = (const Map & rhs);
};

#endif

#ifdef KOLOBOK_SERVER

class KW_COMMON_EXPORT Map : public abstractNoAIMap /* server map */ {
public:
    explicit
    Map(QString);

private:
    Map(const Map &rhs);
    Map& operator = (const Map & rhs);
};

#endif


#endif // MAP_H
