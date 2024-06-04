#include "gameengine.h"
#include "room.h"
#include <QDebug>

//this constructor initialises GameEngine and calls setupRooms to create and link the rooms
//the player is initialised in the room "cabin"
GameEngine::GameEngine(QObject *parent) : QObject(parent) {
    setupRooms();
    player = new Player(rooms["cabin"]);
}
//this deletes the player and all dynamically allocated room objects to prevent memory leaks
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
    // Creates rooms
    rooms["cabin"] = new Room("You are in your log cabin in the woods.");
    rooms["forest"] = new Room("You enter the magical forest.");
    rooms["path"] = new Room("You are on an old dirt path.");
    rooms["castle"] = new Room("you enter a large castle, a chest lies before you");

    // adds items to specific rooms
   // rooms["forest"]->addItem("Key");
    rooms["path"]->addItem("Key");

    // Setups room links
    linkRooms();

    // Initial player room
    emit playerMoved(rooms["cabin"]->getDescription().c_str());
}

void GameEngine::linkRooms() {
    // Room has the exits (north, east, south, west)
    //this sets the specific exits for each room
    rooms["cabin"]->setExits(nullptr, rooms["forest"], nullptr, rooms["path"]);
    rooms["forest"]->setExits(nullptr, nullptr, nullptr, rooms["cabin"]);
    rooms["path"]->setExits(rooms["castle"], rooms["cabin"], nullptr, nullptr);
    rooms["castle"]->setExits(nullptr, nullptr, rooms["path"], nullptr);

}

//this moves the player to the room in the direction chosen
//the method updates the current room if the move is valid and emits the description of the new room
//if the move is invalid, it emits an update saying there is no room

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

//this returns a pointer to the player object
Player* GameEngine::getPlayer() const {
    return player;
}


void GameEngine::playerInteract() {
    // Example interaction
    if (player) {
        Room* currentRoom = player->getCurrentRoom();
    if (currentRoom && currentRoom->getDescription() == "you enter a large castle, a chest lies before you" && player->hasItem("Key")) {
            emit gameOver("You have unlocked the chest and found the treasure! Game over.");


    } else if (currentRoom && currentRoom->getDescription() == "You enter the magical forest.") {
        emit updateStatus("You have hit a spiky tree and taken 25 damage");
        int health =player->health -=25;
       // int health = player->getHealth();
        QString healthStr = QString::number(health); // This converts int to QString
        emit updateStatus("Health: " + healthStr);
    } else {
        emit updateStatus("You cannot use an item here.");

    }
    }
}
