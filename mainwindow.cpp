#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gameengine.h"
#include "player.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow),
    gameEngine(new GameEngine(this)) {

    ui->setupUi(this);
    connectSignals();
    gameEngine->startGame();
    gameEngine->setupRooms();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::connectSignals() {
    connect(ui->northButton, &QPushButton::clicked, [this]() { gameEngine->movePlayer("north"); });
    connect(ui->southButton, &QPushButton::clicked, [this]() { gameEngine->movePlayer("south"); });
    connect(ui->eastButton, &QPushButton::clicked, [this]() { gameEngine->movePlayer("east"); });
    connect(ui->westButton, &QPushButton::clicked, [this]() { gameEngine->movePlayer("west"); });

    connect(ui->lookButton, &QPushButton::clicked, this, &MainWindow::look);
    connect(ui->pickUpButton, &QPushButton::clicked, this, &MainWindow::pickup);
    connect(ui->interactButton, &QPushButton::clicked, this, &MainWindow::interact);
    connect(ui->inventoryButton, &QPushButton::clicked, this, &MainWindow::showInventory);


    connect(gameEngine, &GameEngine::playerMoved, this, [this](const QString& description) {
        ui->textDisplay->append(description);
    });

    connect(gameEngine, &GameEngine::updateStatus, this, [this](const QString& status) {
        ui->textDisplay->append(status);
    });
}

void MainWindow::look(){
    Room* currentRoom = gameEngine->getPlayer()->getCurrentRoom();
    QString description = QString::fromStdString(currentRoom->getDescription());

    std::vector<std::string> items = currentRoom->getItems();
    if (!items.empty()) {
        description += "\nItems in the room: ";
        for (const auto& item : items) {
            description += "\n- " + QString::fromStdString(item);
        }
    } else {
        description += "\nThere are no items in the room. ";
    }
    ui->textDisplay->append(description);
}

void MainWindow::pickup() {

    Room* currentRoom = gameEngine->getPlayer()->getCurrentRoom();
    std::vector<std::string> items = currentRoom->getItems();
    if (!items.empty()) {
        std::string item = items.front();
        gameEngine->getPlayer()->pickUpItem(item);
        ui->textDisplay->append("You picked up: " + QString::fromStdString(item));
    } else {
        ui->textDisplay->append("There are no items to pick up.");
    }
}

void MainWindow::interact(){
    //need to put in interact logic here
    ui->textDisplay->append("interact button clicked");
}

void MainWindow::showInventory() {
    std::vector<std::string> inventory = gameEngine->getPlayer()->getInventory();
    if (!inventory.empty()) {
        QString inventoryText = "Inventory: ";
        for (const auto& item : inventory) {
            inventoryText += "\n- " + QString::fromStdString(item);
        }
        ui->textDisplay->append(inventoryText);
    } else {
        ui->textDisplay->append("Your inventory is empty. ");
    }
}
