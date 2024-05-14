#include "gameengine.h"
#include "room.h"
#include "player.h"
#include <QDebug>

GameEngine::GameEngine(QObject *parent) : QObject(parent) {
    setupRooms();
    player = new Player(rooms["cabin"]);
}

GameEngine::~GameEngine() {
    delete player;
    for (auto& pair : rooms) {
        delete pair.second;
    }
}

void GameEngine::startGame() {
    emit updateStatus("Game started. Navigate the rooms!");
}

void GameEngine::setupRooms() {
    // Create rooms
    rooms["cabin"] = new Room("You are in your log cabin in the woods.");
    rooms["forest"] = new Room("You enter the magical forest.");
    rooms["path"] = new Room("You are on an old dirt path.");

    rooms["cabin"]->addItem("Key");
    rooms["forest"]->addItem("Knife");
    rooms["path"]->addItem("Book");

    // Setup room links
    linkRooms();

    // Initial player room
    //player->setCurrentRoom(rooms["hall"]);
    emit playerMoved(rooms["cabin"]->getDescription().c_str());
}

void GameEngine::linkRooms() {
    // Assuming Room has setExits(Room* north, Room* east, Room* south, Room* west)
    rooms["cabin"]->setExits(nullptr, rooms["forest"], nullptr, rooms["path"]);
    rooms["forest"]->setExits(nullptr, nullptr, nullptr, rooms["cabin"]);
    rooms["path"]->setExits(nullptr, rooms["cabin"], nullptr, nullptr);
}

void GameEngine::movePlayer(const QString& direction) {
    Room* currentRoom = player->getCurrentRoom();

    std::string dir = direction.toStdString();

    qDebug() << "Current Room Description:" << QString::fromStdString(currentRoom->getDescription());

    qDebug() << "Attempting to move to: " << QString::fromStdString(dir);
    Room* nextRoom = currentRoom->getExit(dir);

    if (nextRoom) {
        player->setCurrentRoom(nextRoom);

        QString description = QString::fromStdString(nextRoom->getDescription());
        qDebug() << "Moved to room:" << description;

        emit playerMoved(description);
    } else {
        emit updateStatus("There is no room in that direction.");
    }
}

Player* GameEngine::getPlayer() const {
    return player;
}

void GameEngine::playerInteract(const QString& action) {
    // Example interaction
    if (action == "look") {
        Room* currentRoom = player->getCurrentRoom();

        QString roomDescription = QString::fromStdString(currentRoom->getDescription());
        emit updateStatus("Looking around: " + roomDescription);
    }
}
