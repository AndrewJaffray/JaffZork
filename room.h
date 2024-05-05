#ifndef ROOM_H
#define ROOM_H
#include <string>
#include <map>

class Room
{
public:
    Room(const std::string& description);
    void setDescription(const std::string& description);
    std::string getDescription() const;

    void setExits(Room* north, Room* east, Room* south, Room* west);
    void setExits(const std::string& direction, Room* room);
    Room* getExit(const std::string& direction) const;

    void setConnectingRoom(const std::string& direction, Room* room);
    Room* getConnectingRoom(const std::string& direction) const;

private:
    std::string description;
    std::map<std::string, Room*> exits;
};

#endif // ROOM_H
