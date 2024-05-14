#include "room.h"

Room::Room(const std::string& description) : description(description) {}

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

void Room::addItem(const std::string &item) {
    items.push_back(item);
}

void Room::removeItem(const std::string &item){
    auto it = std::find(items.begin(), items.end(), item);
    if (it != items.end()) {
        items.erase(it);
    }
}

bool Room::hasItem(const std::string &item) const {
    return std::find(items.begin(), items.end(), item) != items.end();
}

std::vector<std::string> Room::getItems() const {
    return items;
}


