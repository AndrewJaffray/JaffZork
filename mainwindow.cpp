#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gameengine.h"
#include "player.h"
#include <QDebug>
#include <array>


//the constructor for MainWindow that initialises UI and GameEngine
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), //call the parent class constructor
    ui(new Ui::MainWindow), //initialises the UI object

    gameEngine(new GameEngine(this)) { //nitialises the game engine


    ui->setupUi(this); //sets up the UI components
    //background image
    setStyleSheet("QMainWindow{ background-image: url(:/new/images/fantasyBackground.png); background-repeat: no-repeat; background-position center; }");
    setupImages(); //setus up the images for the labels
    connectSignals(); //connects the signals and slots for the game
    gameEngine->startGame(); //starts game engine
    gameEngine->setupRooms(); //sets up the rooms
}

MainWindow::~MainWindow() {
    delete ui; //deletes the UI object to free memory
}

void MainWindow::setupImages(){

    int labelWidth = 300;
    int labelHeight = 300;

    //defines an array of label and image pairs
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

    //loops through each label and sets its image
    for (const auto& labelPair : labels) {
        QLabel* label = labelPair.first; //gets the label pointer
        QString imagePath = labelPair.second; // gets the image path
        QPixmap image(imagePath); //loads the image
        //this scales the image to fit the label
        image = image.scaled(labelWidth, labelHeight, Qt::KeepAspectRatio);
        label->setPixmap(image); //set the pixmap of the label
        label->setScaledContents(true);
        label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored); //sets the size policy
        label->installEventFilter(this); //install an event filter for the label
    }
    qDebug() << "Images setup complete"; //confirmation message to terminal
}

//event filter to handle custom events
bool MainWindow::eventFilter(QObject *watched, QEvent *event) {

    if (event->type() == QEvent::MouseButtonPress) { //checks if the event is a mouse clicked
        qDebug() << "Mouse button pressed on: " << watched;

        if (watched == ui->northLabel) { //north label pressed
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
            gameEngine -> playerInteract();
            return true;
        } else if (watched == ui->lookLabel) {
            look();
            return true;
        }

    }
    //call the base class event filter
    return QMainWindow::eventFilter(watched,event);
}

void MainWindow::connectSignals() {

    // Connect the playerMoved signal to a function that updates the text display
    connect(gameEngine, &GameEngine::playerMoved, this, [this](const QString& description) {
        ui->textDisplay->append(description);
    });

    //same thing for updating the status
    connect(gameEngine, &GameEngine::updateStatus, this, [this](const QString& status) {
        ui->textDisplay->append(status);
    });

    //and gameOver
    connect(gameEngine, &GameEngine::gameOver, this, &MainWindow::onGameOver);

    qDebug() << "Signals connected";

}

void MainWindow::onGameOver(const QString &message){
    ui->textDisplay->append(message);
}

void MainWindow::look(){
    // Get the current room of the player
    Room* currentRoom = gameEngine->getPlayer()->getCurrentRoom();
    //get the description of the current room
    QString description = QString::fromStdString(currentRoom->getDescription());

    // Get the items in the room
    std::vector<std::string> items = currentRoom->getItems();
    if (!items.empty()) {
        description += "\nItems in the room: "; //append the items header to the description
        for (const auto& item : items) {
            description += "\n- " + QString::fromStdString(item); //append each item to the description
        }
    } else {
        description += "\nThere are no items in the room. ";
    }
    //append the final message to the text display box
    ui->textDisplay->append(description);
}

void MainWindow::pickup() {
    //get the current room of the player
    Room* currentRoom = gameEngine->getPlayer()->getCurrentRoom();
    //get the items in the room
    std::vector<std::string> items = currentRoom->getItems();
    if (!items.empty()) {
        std::string item = items.front(); //get the first item
        gameEngine->getPlayer()->pickUpItem(item); //pick up that item
        //append the message to the text display including the specific item
        ui->textDisplay->append("You picked up: " + QString::fromStdString(item));
    } else {
        ui->textDisplay->append("There are no items to pick up.");
    }
}

void MainWindow::interact(){
    //I need to put specific interact logic here
    ui->textDisplay->append("interact button clicked");
}

void MainWindow::showInventory() {
    //get the player's inventory
    std::vector<std::string> inventory = gameEngine->getPlayer()->getInventory();
    if (!inventory.empty()) {
        QString inventoryText = "Inventory: "; //initialise the inventory text
        for (const auto& item : inventory) { //loop through the inventory
            inventoryText += "\n- " + QString::fromStdString(item); //append each item to the inventory text
        }
        ui->textDisplay->append(inventoryText); //append the final inventory
    } else {
        ui->textDisplay->append("Your inventory is empty. ");
    }
}
