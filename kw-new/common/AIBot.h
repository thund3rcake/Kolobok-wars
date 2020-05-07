#ifndef AIBOT_H
#define AIBOT_H

#include <Player.h>
#include <CommonGlobal.h>



class KW_COMMON_EXPORT AIBot: Player {
public:
    enum State {Attack, Pursuit, Patrol, Escape};

    AIBot();
    AIBot(QString name, Team team);


private:
    State     state;

};

#endif // AIBOT_H
