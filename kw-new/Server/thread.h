#ifndef THREAD_H
#define THREAD_H

#include <sharedtypes.h>

class Thread : public QThread {
public:
    Thread();

    quint16 getId();
    const MovingObjectProperties & getMovProperties();

    virtual void run();
    void stop();

    // MovingObjectProperties WhatTheBotMustDo(...)
    virtual void getProperty(); // { return WhatTheBotMustDo(...); }

private:
    quint16 id;
    Shared & sharedData; // <-- info

    QMutex mutex;
    QTime timer;
    bool stopped;

    QMutex propertiesMutex;
    MovingObjectProperties playerMovProperties; // ~ botMovProperties

};

//class botThread: public Thread {
//    ...
//};

//void botThread::run() {
//    ...

//    while (1) {
//        foreach (Thread * player, sharedData.playerById.get()) {    // <-- players and bots
//            if (!(player->isFinished()) && player->getId() != id) {
//                teamAnalyse(prop.getTeam());
//                positionAnalyse(prop.getPosition());
//                hpAnalyse(prop.getHp());
//                ...
//            }
//            playerMovProperties = WhatTheBotMustDo(...);
//            usleep(100);
//        }
//    }
//}

#endif // THREAD_H
