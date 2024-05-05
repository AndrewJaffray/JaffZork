#include "player.h"

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
