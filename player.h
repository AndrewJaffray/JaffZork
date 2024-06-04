#ifndef PLAYER_H
#define PLAYER_H

#include "GameEntity.h"
#include "room.h"
#include "Inventory.h"
#include <vector> //includes vector container for storing items
#include <string>

using namespace std;

class Player : public GameEntity {
    friend class GameEngine;

public:
    Player(Room* startRoom); //constructor that initializes the player in a starting room.
    void moveTo(Room* newRoom); //Moves the player to a new room.
    void setCurrentRoom(Room* room); //Sets the player's current room.


    Room* getCurrentRoom() const; //the const qualifier means this function does not modify the Player object.

    void pickUpItem(const string& item); //Adds an item to the player's inventory.
    void dropItem(const string& item); //Removes an item from the player's inventory.

    bool hasItem(const string& item) const;

    std::vector<string> getInventory() const;
    //Returns a copy of the player's inventory.
    //The const qualifier means this function doesn't modify the Player object.

    void gameOver() override; //implements the virtual function to end the game
private:
    int health;
    Room* currentRoom; //pointer to the room object
    Inventory<string> inventory;
};

#endif // PLAYER_H
