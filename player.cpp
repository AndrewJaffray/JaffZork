#include "player.h"

//constructor for the player class
Player::Player(Room* startRoom) : currentRoom(startRoom) {}

void Player::moveTo(Room *newRoom) {
    if (newRoom != nullptr) {
        currentRoom = newRoom;
    }
}

void Player::setCurrentRoom(Room *room){
    this->currentRoom = room;
}

Room* Player::getCurrentRoom() const {
    return currentRoom;
}

void Player::pickUpItem(const std::string &item){
    if (currentRoom->hasItem(item)) {
        inventory.push_back(item);
        currentRoom->removeItem(item);
    }
}

void Player::dropItem(const std::string &item){
    auto it = std::find(inventory.begin(), inventory.end(), item);
    if (it != inventory.end()) {
        inventory.erase(it);
        currentRoom->addItem(item);
    }
}

bool Player::hasItem(const std::string &item) const{
    return std::find(inventory.begin(),inventory.end(),item) != inventory.end();
}

std::vector<std::string> Player::getInventory() const {
    return inventory;
}
