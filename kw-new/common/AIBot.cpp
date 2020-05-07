#include "AIBot.h"

AIBot::AIBot() {
    Player();
}

AIBot::AIBot(QString name, Player::Team team) {
    Player(name, team);
}
