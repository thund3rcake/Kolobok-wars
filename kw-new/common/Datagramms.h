#ifndef DATAGRAMMS_H
#define DATAGRAMMS_H

#include<QtNetwork/QNetworkDatagram>
#include<Serializable.h>
#include<CommonGlobal.h>
#include<QVector2D>
#include<Weapon.h>
#include<MetaRegistrator.h>

namespace Net {

}

static const int MaxSignatureLength = 16;
static const int MaxMapNameLength = 16;

static const QString QStringSignature = "Kolobok";

/*
 *
 *
 * UDP broadcast
 *
 */

class DATA_EXPORT BroadcastData : public Serializable {
    Q_OBJECT

public:
    explicit BroadcastData(QObject * parent = 0);
    BroadcastData(
                                    const QString & signature,
                                    const QString & servername,
                                    const QString & mapName,
                                    quint16 tcpPort,
                                    quint8 version,
                                    quint8 subversion,
                                    quint8 bots,
                                    quint8 players,
                                    quint8 maxPlayers,
                                    QObject * parent = 0
                                    );

    BroadcastData(const BroadcastData & rhs);
    virtual ~BroadcastData();

    bool operator== (const BroadcastData & rhs) const;

    Q_PROPERTY(QString signature
               READ getSignature
               WRITE setSignature);
    Q_PROPERTY(QString serverName
               READ getServerName
               WRITE setServerName);
    Q_PROPERTY(QString mapName
               READ getMapName
               WRITE setMapName);
    Q_PROPERTY(quint16 tcpPort
               READ getTcpPort
               WRITE setTcpPort);
    Q_PROPERTY(quint8 version
               READ getVersion
               WRITE setVersion);
    Q_PROPERTY(quint8 subversion
               READ getSubversion
               WRITE setSubversion);
    Q_PROPERTY(quint8 bots
               READ getBots
               WRITE setBots);
    Q_PROPERTY(quint8 players
               READ getPlayers
               WRITE setPlayers);
    Q_PROPERTY(quint8 maxPlayers
               READ getMaxPlayers
               WRITE setMaxPlayers);

    QString getSignature() const;
    QString getServerName() const;
    QString getMapName() const;
    quint16 getTcpPort() const;
    quint8 getVersion() const;
    quint8  getSubversion() const;
    quint8 getBots() const;
    quint8 getPlayers() const;
    quint8 getMaxPlayers() const;

    void setSignature(QString signature);
    void setServerName(QString serverName);
    void setMapName(QString mapName);
    void setTcpPort(quint16 tcpPort);
    void setVersion(quint8 version);
    void setSubversion(quint8 subversion);
    void setBots(quint8 bots);
    void setPlayers(quint8 players);
    void setMaxPlayers(quint8 maxPlayers);

private:
    MetaRegistrator<BroadcastData> broadcastDataRegistrator;
    QString signature;
    QString serverName;
    QString mapName;
    quint16 tcpPort;
    quint8 version;
    quint8 subversion;
    quint8 bots;
    quint8 players;
    quint8 maxPlayers;
};

Q_DECLARE_METATYPE(BroadcastData);
Q_DECLARE_TYPEINFO(BroadcastData, Q_COMPLEX_TYPE);

struct ServerAbout {
    QHostAddress address;
    quint16 port;
    BroadcastData data;
    quint8 latency;
};

static const QStringList tableHeadLabels =
                        QList<QString>() << "Servers"
                                                             << "Players (B/P/M)"
                                                             << "Map"
                                                             << "Latency";

/* UDP broadcast */



/*
 *
 *
 *UDP Client
 *
 */

class DATA_EXPORT MovingObjectProperties: public Serializable {
Q_OBJECT

public:
    enum Type {
                            Player = 1,
                            Bullet = 2,
                            Timestamp = 3
    };
    enum Team {
                            Red = 1,
                            Blue = 2
    };

    explicit MovingObjectProperties (QObject * parent = 0);
    MovingObjectProperties (
                                                        quint32 timestamp,
                                                        Type type,
                                                        Team team,
                                                        quint16 id,
                                                        const QPointF & position,
                                                        const QVector2D & intent,
                                                        const QVector2D & head,
                                                        quint8 hp,
                                                        const GameWorld::Weapon & weapon,
                                                        QObject * parent = 0
                                                        );

    MovingObjectProperties (const MovingObjectProperties & rhs);
    virtual ~MovingObjectProperties ();

    bool operator== (const MovingObjectProperties & rhs) const;

    Q_PROPERTY(quint32 timestamp
               READ getTimestamp
               WRITE setTimestamp);
    Q_PROPERTY(quint8 type
               READ getQuintType
               WRITE setQuintType);
    Q_PROPERTY(quint8 team
               READ getQuintTeam
               WRITE setQuintTeam);
    Q_PROPERTY(quint16 id
               READ getId
               WRITE setId);
    Q_PROPERTY(QPointF position
               READ getPosition
               WRITE setPosition);
    Q_PROPERTY(QVector2D intent
               READ getIntent
               WRITE setIntent);
    Q_PROPERTY(QVector2D head
               READ getHead
               WRITE setHead);
    Q_PROPERTY(quint8 hp
               READ getHp
               WRITE setHp);
    Q_PROPERTY(GameWorld::Weapon weapon
               READ getWeapon
               WRITE setWeapon);

    quint32 getTimestamp() const;
    MovingObjectProperties::Type getType() const;
    MovingObjectProperties::Team getTeam() const;
    quint8 getQuintType() const;
    quint8 getQuintTeam() const;
    quint16 getId() const;
    QPointF getPosition() const;
    QVector2D getIntent() const;
    QVector2D getHead() const;
    quint8 getHp() const;
    GameWorld::Weapon getWeapon() const;

    void setTimestamp(quint32 timestamp);
    void setType(MovingObjectProperties::Type type);
    void setTeam(MovingObjectProperties::Team team);
    void setQuintType(quint8 type);
    void setQuintTeam(quint8 team);
    void setId(quint16 id);
    void setPosition(QPointF position);
    void setIntent(QVector2D intent);
    void setHead(QVector2D head);
    void setHp(quint8 hp);
    void setWeapon(GameWorld::Weapon weapon);

private:
    MetaRegistrator<MovingObjectProperties> movingObjectPropertiesRegistrator;
    MetaRegistrator<GameWorld::Weapon> weaponRegistrator;
    quint32 timestamp;
    Type type;
    Team team;
    quint16 id;
    QPointF position;
    QVector2D intent;
    QVector2D head;
    quint8 hp;
    GameWorld::Weapon weapon;
};

Q_DECLARE_METATYPE(MovingObjectProperties);
Q_DECLARE_TYPEINFO(MovingObjectProperties, Q_COMPLEX_TYPE);

/* UDP Client*/



/*
// *
// *
// * TCP - options
// *
// */

class DATA_EXPORT GameProperties: public Serializable {
    Q_OBJECT

public:
    enum Type {UdpPort = 1};

    explicit GameProperties(QObject * parent = 0);
    GameProperties(
                                        GameProperties::Type type,
                                        const QString & firstQString,
                                        QObject * parent = 0
                                    ):
            Serializable(parent),
            gamePropertiesRegistrator(MetaRegistrator<GameProperties>("GameProperties")),
            type(type),
            firstQString(firstQString) {}
    GameProperties(
                                        GameProperties::Type type,
                                        qint64 firstQInt,
                                        QObject * parent = 0
                                    ):
            Serializable(parent),
            gamePropertiesRegistrator(MetaRegistrator<GameProperties>("GameProperties")),
            type(type),
            firstQInt(firstQInt) {}
    GameProperties(
                                        GameProperties::Type type,
                                        qreal firstQReal,
                                        QObject * parent = 0
                                    ):
            Serializable(parent),
            gamePropertiesRegistrator(MetaRegistrator<GameProperties>("GameProperties")),
            type( type ),
            firstQReal(firstQReal) {}
    GameProperties(
                                        GameProperties::Type type,
                                        const QString & firstQString,
                                        qint64 firstQInt,
                                        QObject * parent = 0
                                    ):
            Serializable(parent),
            gamePropertiesRegistrator(MetaRegistrator<GameProperties>("GameProperties")),
            type(type),
            firstQString(firstQString),
            firstQInt(firstQInt) {}
    GameProperties(
                                        GameProperties::Type type,
                                        const QString & firstQString,
                                        qreal firstQReal,
                                        QObject * parent = 0
                                    ):
            Serializable(parent),
            gamePropertiesRegistrator(MetaRegistrator<GameProperties>("GameProperties")),
            type(type),
            firstQString(firstQString),
            firstQReal(firstQReal) {}
    GameProperties(
                                        GameProperties::Type type,
                                        const QString & firstQString,
                                        qint64 firstQInt,
                                        qreal  firstQReal,
                                        QObject * parent = 0
                                    ):
            Serializable(parent),
            gamePropertiesRegistrator(MetaRegistrator<GameProperties>("GameProperties")),
            type(type),
            firstQString(firstQString),
            firstQInt(firstQInt),
            firstQReal(firstQReal) {}
    GameProperties(
                                        GameProperties::Type type,
                                        const QString & firstQString,
                                        const QString & secondQString,
                                        qint64 firstQInt,
                                        qint64 secondQInt,
                                        qreal  firstQReal,
                                        qreal  secondQReal,
                                        QObject * parent = 0
                                    ):
            Serializable(parent),
            gamePropertiesRegistrator(MetaRegistrator<GameProperties>("GameProperties")),
            type(type),
            firstQString(firstQString),
            secondQString(secondQString),
            firstQInt(firstQInt),
            secondQInt(secondQInt),
            firstQReal(firstQReal),
            secondQReal(secondQReal) {}

    GameProperties (const GameProperties & rhs);
    virtual ~GameProperties();

    bool operator== (const GameProperties & rhs) const;

    Q_PROPERTY(quint8 Type
               READ getQuintType
               WRITE setQuintType);
    Q_PROPERTY(QString firstQString
               READ getFirstQString
               WRITE setFirstQstring);
    Q_PROPERTY(QString secondQString
               READ getSecondQString
               WRITE setSecondQstring);
    Q_PROPERTY(quint64 firstQInt
               READ getFirstQInt
               WRITE setFirstQInt);
    Q_PROPERTY(quint64 secondQInt
               READ getSecondQInt
               WRITE setSecondQInt);
    Q_PROPERTY(qreal firstQReal
               READ getFirstQReal
               WRITE setFirstQReal);
    Q_PROPERTY(qreal secondQReal
               READ getSecondQReal
               WRITE setSecondQReal);

    GameProperties::Type getType()  const;
    quint8 getQuintType()  const;
    QString getFirstQString() const;
    QString getSecondQString() const;
    quint64 getFirstQInt() const;
    quint64 getSecondQInt() const;
    qreal getFirstQReal() const;
    qreal getSecondQReal() const;

    void setType(GameProperties::Type type);
    void setQuintType(quint8 type);
    void setFirstQstring(QString firstQString);
    void setSecondQstring(QString secondQString);
    void setFirstQInt(quint64 firstQInt);
    void setSecondQInt(quint64 secondQInt);
    void setFirstQReal(qreal firstQReal);
    void setSecondQReal(qreal secondQReal);

private:
    MetaRegistrator<GameProperties> gamePropertiesRegistrator;
    Type type;
    QString firstQString;
    QString secondQString;
    qint64 firstQInt;
    qint64 secondQInt;
    qreal firstQReal;
    qreal secondQReal;
};

Q_DECLARE_METATYPE(GameProperties);
Q_DECLARE_TYPEINFO(GameProperties, Q_COMPLEX_TYPE);

/* TCP - options */

#endif // DATAGRAMMS_H