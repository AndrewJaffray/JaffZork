#ifndef PLAYER_H
#define PLAYER_H


#include "room.h"
class Player
{
public:
    explicit Player(Room* startRoom);
    void moveTo(Room* newRoom);
    void setCurrentRoom(Room* room);
    Room* getCurrentRoom() const;

private:
    Room* currentRoom;
};

#endif // PLAYER_H
