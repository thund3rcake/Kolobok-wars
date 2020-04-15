#include "BroadcastSender.h"

int main() {
    BroadcastSender mySender("myServer", "myMap", 0, 111, 12);
    mySender.run();
    //return 0
}
