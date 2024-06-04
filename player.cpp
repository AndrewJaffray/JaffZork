#include "player.h"
#include "QApplication"



//constructor for the player class, initializes the player in the starting room
Player::Player(Room* startRoom) : health(100), currentRoom(startRoom) {}

void Player::moveTo(Room *newRoom) {
    if (newRoom != nullptr) { // Checks if the new room is not null
        currentRoom = newRoom; //updates the current room to the new room
    }
}

void Player::setCurrentRoom(Room *room){
    this->currentRoom = room; //set the current room to the room pointer
}

Room* Player::getCurrentRoom() const {
    return currentRoom;
}

void Player::pickUpItem(const std::string &item){
    if (currentRoom->hasItem(item)) {
        inventory.addItem(item); //adds the item to the player's inventory
        currentRoom->removeItem(item); //removes the item from the current room
    }
}

void Player::dropItem(const std::string &item){
    //finds the item in the inventory

    //checks if the item is in the inventory
        inventory.removeItem(item); //removes the item from inventory
        currentRoom->addItem(item); //adds the item to the current room
    }


bool Player::hasItem(const std::string &item) const{
    //returns true if the item is found in the inventory
    return inventory.hasItem(item);
}

std::vector<std::string> Player::getInventory() const {
    //returns the player's inventory as a vector of strings
    return inventory.getItems();
}
void Player::gameOver() {
    QApplication::quit();
 }

