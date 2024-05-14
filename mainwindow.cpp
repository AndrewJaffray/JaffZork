#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gameengine.h"
#include "player.h"
#include <QDebug>
#include <array>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),

    gameEngine(new GameEngine(this)) {

    ui->setupUi(this);
    setStyleSheet("QMainWindow{ background-image: url(:/new/images/fantasyBackground.png); background-repeat: no-repeat; background-position center; }");
    setupImages();
    connectSignals();
    gameEngine->startGame();
    gameEngine->setupRooms();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setupImages(){

    int labelWidth = 300;
    int labelHeight = 300;

    std::array<QPair<QLabel*, QString>, 9> labels = {{
        {ui->northLabel, ":/new/images/northPicture.png"},
        {ui->southLabel, ":/new/images/southPicture.png"},
        {ui->eastLabel, ":/new/images/eastPicture.png"},
        {ui->westLabel, ":/new/images/westPicture.png"},
        {ui->fantasyLabel, ":/new/images/fantasySquare.png"},
        {ui->pickUpLabel, ":/new/images/PickUpImage.png"},
        {ui->inventoryLabel, ":/new/images/InventoryImage.png"},
        {ui->interactLabel, ":/new/images/InteractImage.png"},
        {ui->lookLabel, ":/new/images/lookImage.png"}
    }};


    for (const auto& labelPair : labels) {
        QLabel* label = labelPair.first;
        QString imagePath = labelPair.second;
        QPixmap image(imagePath);
        image = image.scaled(labelWidth, labelHeight, Qt::KeepAspectRatio);
        label->setPixmap(image);
        label->setScaledContents(true);
        label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        label->installEventFilter(this);
    }
    qDebug() << "Images setup complete";
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event) {

    if (event->type() == QEvent::MouseButtonPress) {
        qDebug() << "Mouse button pressed on: " << watched;

        if (watched == ui->northLabel) {
            qDebug() << "North label clicked";
            gameEngine -> movePlayer("north");
            return true;
        } else if (watched == ui->southLabel) {
            gameEngine -> movePlayer("south");
            return true;
        } else if (watched == ui->eastLabel) {
            gameEngine -> movePlayer("east");
            return true;
        } else if (watched == ui->westLabel) {
            gameEngine -> movePlayer("west");
            return true;
        } else if (watched == ui->pickUpLabel) {
            pickup();
            return true;
        } else if (watched == ui->inventoryLabel) {
            showInventory();
            return true;
        } else if (watched == ui->interactLabel) {
            interact();
            return true;
        } else if (watched == ui->lookLabel) {
            look();
            return true;
        }

    }
    return QMainWindow::eventFilter(watched,event);
}

void MainWindow::connectSignals() {

    connect(gameEngine, &GameEngine::playerMoved, this, [this](const QString& description) {
        ui->textDisplay->append(description);
    });

    connect(gameEngine, &GameEngine::updateStatus, this, [this](const QString& status) {
        ui->textDisplay->append(status);
    });
    qDebug() << "Signals connected";

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
