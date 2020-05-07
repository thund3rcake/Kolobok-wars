#ifndef AIBOT_H
#define AIBOT_H

#include <Player.h>


class AIBot: public Player {
public:
    enum State {Attack, Pursuit, Patrol, Escape};

    AIBot();
    AIBot(QString name, Team team);


private:
    State state;

};

#endif // AIBOT_H
