#ifndef ROOM_H
#define ROOM_H
#include <string>
#include <map>
#include<vector>

class Room
{
public:
    Room(const std::string& description);
    void setDescription(const std::string& description);
    std::string getDescription() const;

    void setExits(Room* north, Room* east, Room* south, Room* west); // sets the exits to other rooms in the N,S,E,W directions
    void setExits(const std::string& direction, Room* room); //overloaded method that sets an exit in a specific direction
    Room* getExit(const std::string& direction) const; //returns the room specified in that direction


    void addItem(const std::string& item); //adds an item to the room
    void removeItem(const std::string& item); //removes an item from the room
    bool hasItem(const std::string& item) const; //checks if the room contains a specific item
    std:: vector<std::string> getItems() const; //returns a list of all items in the room

private:
    std::string description;
    std::map<std::string, Room*> exits; // a map that links the directions to other Room objects
    std:: vector<std::string> items; //a vector of strings representing items present in the room
};

#endif // ROOM_H
