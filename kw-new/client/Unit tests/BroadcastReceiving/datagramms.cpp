#include <Datagramms.h>

/*BrodacastData*/
BroadcastData::BroadcastData(QObject *parent) :
    Serializable(parent),
    broadcastDataRegistrator(MetaRegistrator<BroadcastData>("broadcastData")) {}

BroadcastData::BroadcastData(
                                                                    const QString & signature,
                                                                    const QString & serverName,
                                                                    const QString & mapName,
                                                                    quint16  tcpPort,
                                                                    quint8   version,
                                                                    quint8   subversion,
                                                                    quint8   bots,
                                                                    quint8   players,
                                                                    quint8   maxPlayers,
                                                                    QObject * parent
                                                                    ):
    Serializable(parent),
    broadcastDataRegistrator(MetaRegistrator<BroadcastData>("BroadcastData")),
    signature( signature ),
    serverName( serverName ),
    mapName( mapName ),
    tcpPort( tcpPort ),
    version( version ),
    subversion( subversion ),
    bots( bots ),
    players( players ),
    maxPlayers(maxPlayers) {}

BroadcastData::BroadcastData(const BroadcastData &rhs) :
    Serializable(rhs.parent()),
    broadcastDataRegistrator(rhs.broadcastDataRegistrator) {}

BroadcastData::~BroadcastData() {}

bool BroadcastData::operator== (const BroadcastData & rhs) const {

    if (rhs.signature == this -> signature) {
        if (rhs.serverName == this -> serverName) {
            if (rhs.mapName == this -> mapName) {
                if (rhs.tcpPort == this -> tcpPort) {
                    if (rhs.version == this -> version) {
                        if (rhs.subversion == this -> subversion) {
                            if (rhs.bots == this -> bots) {
                                if (rhs.players == this -> players) {
                                    if (rhs.maxPlayers == this -> maxPlayers) {
                                        return true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

QString BroadcastData::getSignature() const {
    return signature;
}
void BroadcastData::setSignature(QString signature){
    this -> signature = signature;
}

QString BroadcastData::getServerName() const {
    return serverName;
}
void BroadcastData::setServerName(QString serverName) {
    this -> serverName = serverName;
}

QString BroadcastData::getMapName() const {
    return mapName;
}
void BroadcastData::setMapName(QString mapName) {
    this -> mapName = mapName;
}

quint16 BroadcastData::getTcpPort() const {
    return tcpPort;
}
void BroadcastData::setTcpPort(quint16 tcpPort) {
    this -> tcpPort = tcpPort;
}

quint8 BroadcastData::getVersion() const {
    return version;
}
void BroadcastData::setVersion(quint8 version) {
    this -> version = version;
}

quint8 BroadcastData::getSubversion() const {
    return subversion;
}
void BroadcastData::setSubversion(quint8 subversion) {
    this -> subversion = subversion;
}

quint8 BroadcastData::getBots() const {
    return bots;
}
void BroadcastData::setBots(quint8 bots) {
    this -> bots = bots;
}

quint8 BroadcastData::getPlayers() const {
    return players;
}
void BroadcastData::setPlayers(quint8 players) {
    this -> players = players;
}

quint8 BroadcastData::getMaxPlayers() const {
    return maxPlayers;
}
void BroadcastData::setMaxPlayers(quint8 maxPlayers) {
    this -> maxPlayers = maxPlayers;
}
/*End BrodacastData*/




/*MovingObjectProperties*/
MovingObjectProperties::MovingObjectProperties(QObject *parent) :
    Serializable(parent),
    movingObjectPropertiesRegistrator(MetaRegistrator<MovingObjectProperties>("MovingObjectProperties")),
    weaponRegistrator(MetaRegistrator<GameWorld::Weapon>("GameWorld::Weapon")) {}

MovingObjectProperties::MovingObjectProperties(
                                                                                                            quint32 timestamp,
                                                                                                            Type type,
                                                                                                            Team team,
                                                                                                            quint16 id,
                                                                                                            const QPointF & position,
                                                                                                            const QVector2D & intent,
                                                                                                            const QVector2D & head,
                                                                                                            quint8 hp,
                                                                                                            const GameWorld::Weapon & weapon,
                                                                                                            QObject * parent
                                                                                                            ):
    Serializable(parent),
    movingObjectPropertiesRegistrator(MetaRegistrator<MovingObjectProperties>("MovingObjectProperties")),
    weaponRegistrator(MetaRegistrator<GameWorld::Weapon>("GameWorld::Weapon")) ,
    timestamp( timestamp ),
    type( type ),
    team( team ),
    id( id ),
    position( position ),
    intent( intent ),
    head( head ),
    hp( hp ),
    weapon( weapon ) {};

MovingObjectProperties::MovingObjectProperties(const MovingObjectProperties &rhs) :
    Serializable(rhs.parent()),
    movingObjectPropertiesRegistrator(rhs.movingObjectPropertiesRegistrator),
    weaponRegistrator(rhs.weaponRegistrator) {}

MovingObjectProperties::~MovingObjectProperties() {}

bool MovingObjectProperties::operator== (const MovingObjectProperties & rhs) const {

    if (rhs.timestamp == this -> timestamp) {
        if (rhs.type == this -> type) {
            if (rhs.team == this -> team) {
                if (rhs.id == this -> id) {
                    if (rhs.position == this -> position) {
                        if (rhs.intent == this -> intent) {
                            if (rhs.head == this -> head) {
                                if (rhs.hp == this -> hp) {
                                    if (rhs.weapon == this -> weapon) {
                                        return true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

quint32 MovingObjectProperties::getTimestamp() const {
    return timestamp;
}
void MovingObjectProperties::setTimestamp(quint32 timestamp) {
    this -> timestamp = timestamp;
}

MovingObjectProperties::Type MovingObjectProperties::getType() const {
    return type;
}
void MovingObjectProperties::setType(Type type) {
    this -> type = type;
}

MovingObjectProperties::Team MovingObjectProperties::getTeam() const {
    return team;
}
void MovingObjectProperties::setTeam(Team team) {
    this -> team = team;
}

quint16 MovingObjectProperties::getId() const {
    return id;
}
void MovingObjectProperties::setId(quint16 id) {
    this -> id = id;
}

QPointF MovingObjectProperties::getPosition() const {
    return position;
};
void MovingObjectProperties::setPosition(QPointF position) {
    this -> position = position;
}

QVector2D MovingObjectProperties::getIntent() const {
    return intent;
}
void MovingObjectProperties::setIntent(QVector2D intent) {
    this -> intent = intent;
}

QVector2D MovingObjectProperties::getHead() const {
    return head;
}
void MovingObjectProperties::setHead(QVector2D head) {
    this -> head = head;
}

quint8 MovingObjectProperties::getHp() const {
    return hp;
}
void MovingObjectProperties::setHp(quint8 hp) {
    this -> hp = hp;
}

GameWorld::Weapon MovingObjectProperties::getWeapon() const {
    return weapon;
}
void MovingObjectProperties::setWeapon(GameWorld::Weapon weapon) {
    this -> weapon = weapon;
}

quint8 MovingObjectProperties::getQuintType() const {
    return static_cast<quint8>(this -> type);
}
void MovingObjectProperties::setQuintType(quint8 type) {
    this -> type = static_cast<MovingObjectProperties::Type>(type);
}

quint8 MovingObjectProperties::getQuintTeam() const {
    return static_cast<quint8>(this -> team);
}
void MovingObjectProperties::setQuintTeam(quint8 team) {
    this -> team = static_cast<MovingObjectProperties::Team>(team);
}
/*End MovingObjectProperties*/




/*TCP-options*/
GameProperties::GameProperties(QObject *parent) :
    Serializable(parent),
    gamePropertiesRegistrator(MetaRegistrator<GameProperties>("GameProperties")) {}

GameProperties::GameProperties(const GameProperties &rhs) :
    Serializable(rhs.parent()),
    gamePropertiesRegistrator(rhs.gamePropertiesRegistrator) {}

GameProperties::~GameProperties() {}

bool GameProperties::operator== (const GameProperties & rhs) const {

    if (rhs.type == this -> type) {
        if (rhs.firstQString == this -> firstQString) {
            if (rhs.secondQString == this -> secondQString) {
                if (rhs.firstQInt == this -> firstQInt) {
                    if (rhs.secondQInt == this -> secondQInt) {
                        if (rhs.firstQReal == this -> firstQReal) {
                            if (rhs.secondQReal == this -> secondQReal) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

GameProperties::Type GameProperties::getType() const {
    return type;
}
void GameProperties::setType(Type type) {
    this -> type = type;
}

QString GameProperties::getFirstQString() const {
    return firstQString;
}
void GameProperties::setFirstQstring(QString firstQString) {
    this -> firstQString = firstQString;
}

QString GameProperties::getSecondQString() const {
    return secondQString;
}
void GameProperties::setSecondQstring(QString secondQString) {
    this -> secondQString = secondQString;
}

quint64 GameProperties::getFirstQInt() const {
    return firstQInt;
}
void GameProperties::setFirstQInt(quint64 firstQInt) {
    this -> firstQInt = firstQInt;
}

quint64 GameProperties::getSecondQInt() const {
    return secondQInt;
}
void GameProperties::setSecondQInt(quint64 secondQInt) {
    this -> secondQInt = secondQInt;
}

qreal GameProperties::getFirstQReal() const {
    return firstQReal;
}
void GameProperties::setFirstQReal(qreal firstQReal) {
    this -> firstQReal = firstQReal;
}

qreal GameProperties::getSecondQReal() const {
    return secondQReal;
}
void GameProperties::setSecondQReal(qreal secondQReal) {
    this -> secondQReal = secondQReal;
}

quint8 GameProperties::getQuintType() const {
    return static_cast<quint8>(this -> type);
}
void GameProperties::setQuintType(quint8 type) {
    this -> type = static_cast<GameProperties::Type>(type);
}
/*End TCP-options*/