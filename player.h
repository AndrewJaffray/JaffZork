#ifndef PLAYER_H
#define PLAYER_H


#include "room.h"
#include <vector>
#include <string>

class Player
{
public:
    Player(Room* startRoom);
    void moveTo(Room* newRoom);
    void setCurrentRoom(Room* room);
    Room* getCurrentRoom() const;

    void pickUpItem(const std::string& item);
    void dropItem(const std::string& item);
    bool hasItem(const std:: string& item) const;
    std::vector<std::string> getInventory() const;

private:
    Room* currentRoom;
    std::vector<std::string> inventory;
};

#endif // PLAYER_H
