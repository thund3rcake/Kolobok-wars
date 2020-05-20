#include "aibot.h"
#include "Datagramms.h"
#include "GameWorldConsts.h"
#include "sharedtypes.h"
#include "playerthread.h"
#include "sharedobject.h"
#include <QLinkedList>
#include "aibot.h"
#include "utilityalgorithms.h"
#include "Entity.h"

AIBot::AIBot(Shared & sharedData, MovingObjectProperties props) {
   state = Patrol;
   team = props.getTeam();
   hp = props.getHp();
   // head = props->getHead();
   weapon = props.getWeapon();
   position = props.getPosition();
   id = props.getId();
   patrolPoints = UtilityAlgorithms::selectPolygon(sharedData, consts::patrolEdgeMinLength);
   currentPatrolIndex = -1;
   qDebug() << "aiBot constructor finished, patrol positions: " << patrolPoints;
   qsrand(time(NULL));

}

AIBot::~AIBot()
{
    patrolPoints.clear();
    patrolPath.clear();
    firedBullets.clear();
}


bool AIBot::isVisible(QPointF playerPos, Shared & sharedData) {
    QVector2D move = QVector2D(playerPos.x() - position.x(), playerPos.y() - position.y());
    quint16 distance = move.length();
    qreal moveTime = distance / consts::velocity;
    QPointF unitIncrement = (move / moveTime).toPointF();

    // split the vector into unit moves; if any of the moves is irrelevant ==> dot is not visible
    for(int i = 0; i < qCeil(moveTime); i++)
        if(!sharedData.gameMap.get()->isDotAvailable((position + unitIncrement).toPoint()))
            return false;
    return true;
}

void AIBot::attack(MovingObjectProperties playerProps)
{
    fire(playerProps.getPosition(), 0);
}

void AIBot::escape(MovingObjectProperties playerProps, Shared &sharedData)
{
    // move opposite direction
    QVector2D moveDirection = (-1) * QVector2D(playerProps.getPosition() - position);
    float moveDistance = moveDirection.length() / consts::velocity;
    moveDirection.normalize();
    QVector2D intent = moveDirection * moveDistance;
    QPoint nextPos = position.toPoint() + intent.toPoint();
    float nextDist;
    if(!sharedData.gameMap.get()->isDotAvailable(nextPos))
        do {
            double phi = qrand() % 360;
            intent = QVector2D(cos(phi), sin(phi));
            nextPos = position.toPoint() + intent.toPoint();
            nextDist = QVector2D(nextPos - playerProps.getPosition()).length();
        } while(!sharedData.gameMap.get()->isDotAvailable(nextPos) && nextDist <= moveDistance);
    this->intent = intent;
}

void AIBot::pursuit(MovingObjectProperties playerProps, Shared & sharedData)
{
    /*QVector2D intent = UtilityAlgorithms::getMoveIntent(
                position,
                playerProps.getPosition(),
                sharedData,
                consts::stride);

    this->intent = intent;*/
}

void AIBot::patrol(Shared &sharedData)
{
    double prob = rand() % consts::changePathProb;
    if(prob >= consts::changePathProb - 1) {
        patrolPoints = UtilityAlgorithms::selectPolygon(sharedData, consts::patrolEdgeMinLength);
    }
    bool calcPathFlag = false;
    if(currentPatrolIndex == -1 ||
            UtilityAlgorithms::arePointsClose(position, patrolPoints.at(currentPatrolIndex), consts::stride)) {
        qDebug() << "patrol: switching target!";
        currentPatrolIndex += 1;
        currentPatrolIndex %= consts::patrolPointsCount;
        calcPathFlag = true;
    }

    qDebug() << "Patrol: target = " << patrolPoints.at(currentPatrolIndex) << " position = " << position;

    QLinkedList<QPointF> * path = new QLinkedList<QPointF>;

    QVector2D intent = UtilityAlgorithms::getMoveIntent(
                position,
                patrolPoints.at(currentPatrolIndex),
                sharedData,
                consts::stride,
                path);


    this->intent = intent;
}


void AIBot::fire(QPointF target, int type) {
    // TODO: implement
}

void AIBot::switchState(Shared & sharedData) {
    // for now, the logic is: bot's movement is dependent on the nearest player to it.
    // TODO: smarter system
    MovingObjectProperties nearestPlayerProps;
    foreach (PlayerThread * player, sharedData.playerById.get())
        if (!(player->isFinished()) && player->getId() != id) {
            // find the nearest player
            nearestPlayerProps = player->getMovProperties();
        }

    //qDebug() << "[switchState] nearestPlayerPos: " << nearestPlayerProps.getPosition() << " botPos: " << position;

    switch (state) {
        case Attack:
            if(hp <= consts::hpEscape) {
                qDebug() << "state: Attack --> Escape";
                state = Escape;
            }

            if(!isVisible(nearestPlayerProps.getPosition(), sharedData)) {
                qDebug() << "state: Attack --> Patrol";
                state = Patrol;
            }

            break;
        case Pursuit:
            if(isVisible(nearestPlayerProps.getPosition(), sharedData)) {
                qDebug() << "state: Pursuit --> Attack";
                state = Attack;
            }
            // TODO: player is dead ==> patrol
            break;
        case Patrol:
            /*if(isVisible(nearestPlayerProps.getPosition(), sharedData) && hp <= consts::hpEscape) {
                qDebug() << "state: Patrol --> Escape";
                state = Escape;
            }

            if(isVisible(nearestPlayerProps.getPosition(), sharedData) && hp > consts::hpEscape) {
                qDebug() << "state: Patrol --> Attack";
                state = Attack;
            }
            break; */
        case Escape:
            if(!isVisible(nearestPlayerProps.getPosition(), sharedData)) {
                qDebug() << "state: Escape --> Patrol";
                state = Patrol;
            }
            break;
        default:
            break;
    }
}

MovingObjectProperties AIBot::action(Shared & sharedData, MovingObjectProperties currentProps) {
    // for now, the logic is: bot's movement is dependent on the nearest player to it.
    // TODO: smarter system
    MovingObjectProperties nearestPlayerProps;
    MovingObjectProperties newProps = MovingObjectProperties();
    foreach (PlayerThread * player, sharedData.playerById.get())
        if (!(player->isFinished()) && player->getId() != id) {
            // find the nearest player
            nearestPlayerProps = player->getMovProperties();
        }

    switch (state) {
        case Attack:
            attack(nearestPlayerProps);
            break;
        case Pursuit:
            pursuit(nearestPlayerProps, sharedData);
            break;
        case Patrol:
            // patrol
            patrol(sharedData);
            break;
        case Escape:
            // escape
            escape(nearestPlayerProps, sharedData);
            break;
        default:
            break;
    }
    newProps.setIntent(intent);
    newProps.setHp(hp);
    newProps.setWeapon(weapon);
    return newProps;
}

void AIBot::setProperties(MovingObjectProperties props)
{
    position = props.getPosition();
    hp = props.getHp();
    head = props.getHead();
}


