#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QString>
#include <map>

    class Room;  // Forward declaration
class Player;  // Forward declaration

class GameEngine : public QObject {
    Q_OBJECT

public:
    explicit GameEngine(QObject* parent = nullptr);
    ~GameEngine();

    void setupRooms();
    void startGame();

public slots:
    void movePlayer(const QString& direction);
    void playerInteract(const QString& action);

signals:
    void updateStatus(const QString& status);
    void playerMoved(const QString& roomDescription);

private:
    Player* player;
    std::map<QString, Room*> rooms;
    void linkRooms();  // Helper to set up connections between rooms
};

#endif // GAMEENGINE_H
