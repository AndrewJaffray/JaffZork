#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QString>
#include <map>
#include <string>
#include "player.h"
#include "room.h"
#include "GameEntity.h"

class Room;  // informs the compiler that these classes exist
class Player;  // Forward declaration

//This declares the GameEngine class which inherits from QObject
//This enables Qt's signal and slot mechanism
class GameEngine : public QObject {
    Q_OBJECT

    //this constructor can take in a QObject parent, defaulting to 'nullptr'
public:
    explicit GameEngine(QObject* parent = nullptr);
    ~GameEngine(); //Destructor

    void setupRooms();
    void startGame();
    void movePlayer(const QString& direction);
    Player* getPlayer() const; //this function gets the current player

public slots:
    void playerInteract();

signals:
    void updateStatus(const QString& status); //signal to update the game's status
    void playerMoved(const QString& roomDescription); //signal emmited when the player moves, providing the new room's description
    void gameOver (const QString& message); //signal to tell player that the game is over
private:
    Player* player; //pointer to the player object
    std::map<QString, Room*> rooms; //a map that store rooms, where the key is a QString and the value is a pointer to a Room

    void linkRooms();  // Helper to set up connections between
};

#endif // GAMEENGINE_H
