#ifndef PLAYER_H
#define PLAYER_H


#include "room.h"
#include <vector> //includes vector container for storing items
#include <string>

class Player
{
public:
    Player(Room* startRoom); //constructor that initializes the player in a starting room.
    void moveTo(Room* newRoom); //Moves the player to a new room.
    void setCurrentRoom(Room* room); //Sets the player's current room.

    Room* getCurrentRoom() const; //the const qualifier means this function does not modify the Player object.

    void pickUpItem(const std::string& item); //Adds an item to the player's inventory.
    void dropItem(const std::string& item); //Removes an item from the player's inventory.

    bool hasItem(const std:: string& item) const; //The const qualifier means this function does not modify the Player object.

    std::vector<std::string> getInventory() const;
    //Returns a copy of the player's inventory.
    //The const qualifier means this function does not modify the Player object.

private:
    Room* currentRoom;
    std::vector<std::string> inventory;
};

#endif // PLAYER_H
