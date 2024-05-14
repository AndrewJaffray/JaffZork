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

    void setExits(Room* north, Room* east, Room* south, Room* west);
    void setExits(const std::string& direction, Room* room);
    Room* getExit(const std::string& direction) const;


    void addItem(const std::string& item);
    void removeItem(const std::string& item);
    bool hasItem(const std::string& item) const;
    std:: vector<std::string> getItems() const;

private:
    std::string description;
    std::map<std::string, Room*> exits;
    std:: vector<std::string> items;
};

#endif // ROOM_H
