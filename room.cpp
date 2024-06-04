#include "room.h"

//constructor for room, initialises room with a description
Room::Room(const std::string& description) : description(description) {}

void Room::setDescription(const std::string &description){
    this->description = description;
}

std::string Room::getDescription() const{
    return description;
}
//sets the exits for a room in all 4 directions
void Room::setExits(Room *north, Room *east, Room *south, Room *west){

    exits["north"] = north;
    exits["south"] = south;
    exits["east"] = east;
    exits["west"] = west;

}

void Room::setExits(const std::string &direction, Room *room){
    exits[direction] = room; //set the exit in the specified direction
}

Room* Room::getExit(const std::string &direction) const{
    auto it = exits.find(direction); //finds the exit in the specified direction
    if (it != exits.end()) {
        return it->second;
    }
    return nullptr;
}

void Room::addItem(const std::string &item) {
    items.push_back(item); //adds the item to the list of items in a room
}

void Room::removeItem(const std::string &item){
    // finds the item from the list of items
    auto it = std::find(items.begin(), items.end(), item);
    if (it != items.end()) { //checks if the item is found
        items.erase(it);// removes the item from the list of items
    }
}

bool Room::hasItem(const std::string &item) const {
    //returns true if the item is found in the list
    return std::find(items.begin(), items.end(), item) != items.end();
}

std::vector<std::string> Room::getItems() const {
    return items; //returns the list of items in a vector
}


