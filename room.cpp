#include "room.h"

Room::Room(const std::string& description) : description(description) {

    exits["north"] = nullptr;
    exits["south"] = nullptr;
    exits["east"] = nullptr;
    exits["west"] = nullptr;



}

void Room::setDescription(const std::string &description){
    this->description = description;
}

std::string Room::getDescription() const{
    return description;
}

void Room::setExits(Room *north, Room *east, Room *south, Room *west){

    exits["north"] = north;
    exits["south"] = south;
    exits["east"] = east;
    exits["west"] = west;

}

void Room::setExits(const std::string &direction, Room *room){
    exits[direction] = room;
}

Room* Room::getExit(const std::string &direction) const{
    auto it = exits.find(direction);
    if (it != exits.end()) {
        return it->second;
    }
    return nullptr;
}

void Room::setConnectingRoom(const std::string &direction, Room *room){
    exits[direction] = room;
}

Room* Room::getConnectingRoom(const std::string &direction) const{
    auto it = exits.find(direction);
    if (it != exits.end()){
        return it -> second;
    }
    return nullptr;
}
