#include "gameengine.h"
#include "room.h"
#include "player.h"

GameEngine::GameEngine(QObject *parent) : QObject(parent) {
    setupRooms();
    player = new Player(rooms["hall"]);
}

GameEngine::~GameEngine() {
    delete player;
    for (auto& pair : rooms) {
        delete pair.second;
    }
}

void GameEngine::setupRooms() {
    // Create rooms
    rooms["hall"] = new Room("You are in a long, dark hallway.");
    rooms["kitchen"] = new Room("You are in a dusty kitchen with an old stove.");
    rooms["library"] = new Room("You are in a quiet, old library filled with books.");

    // Setup room links
    linkRooms();

    // Initial player room
    //player->setCurrentRoom(rooms["hall"]);
    emit playerMoved(rooms["hall"]->getDescription().c_str());
}

void GameEngine::linkRooms() {
    // Assuming Room has setExits(Room* north, Room* east, Room* south, Room* west)
    rooms["hall"]->setExits(nullptr, rooms["kitchen"], nullptr, rooms["library"]);
    rooms["kitchen"]->setExits(nullptr, nullptr, nullptr, rooms["hall"]);
    rooms["library"]->setExits(nullptr, rooms["hall"], nullptr, nullptr);
}

void GameEngine::startGame() {
    emit updateStatus("Game started. Navigate the rooms!");
}

void GameEngine::movePlayer(const QString& direction) {
    Room* currentRoom = player->getCurrentRoom();

    std::string dir = direction.toStdString();
    Room* nextRoom = currentRoom->getExit(dir);

    if (nextRoom) {
        player->setCurrentRoom(nextRoom);

        QString description = QString::fromStdString(nextRoom->getDescription());
        emit playerMoved(description);
    } else {
        emit updateStatus("There is no room in that direction.");
    }
}

void GameEngine::playerInteract(const QString& action) {
    // Example interaction
    if (action == "look") {
        Room* currentRoom = player->getCurrentRoom();

        QString roomDescription = QString::fromStdString(currentRoom->getDescription());
        emit updateStatus("Looking around: " + roomDescription);
    }
}
