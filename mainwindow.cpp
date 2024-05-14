#include "mainwindow.h"
    MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), gameEngine(new GameEngine(this)) {
    setupUI();
    connectSignals();
    gameEngine->startGame();
    gameEngine->setupRooms();
}

void MainWindow::setupUI() {
    // Main Widget and Layout
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    // Display area for game text
    textDisplay = new QTextEdit(this);
    textDisplay->setReadOnly(true);
    mainLayout->addWidget(textDisplay);

    // Buttons for directions
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    northButton = new QPushButton("North", this);
    southButton = new QPushButton("South", this);
    eastButton = new QPushButton("East", this);
    westButton = new QPushButton("West", this);

    buttonLayout->addWidget(northButton);
    buttonLayout->addWidget(southButton);
    buttonLayout->addWidget(eastButton);
    buttonLayout->addWidget(westButton);

    mainLayout->addLayout(buttonLayout);
    setCentralWidget(centralWidget);
}

void MainWindow::connectSignals() {
    connect(northButton, &QPushButton::clicked, [this]() { gameEngine->movePlayer("north"); });
    connect(southButton, &QPushButton::clicked, [this]() { gameEngine->movePlayer("south"); });
    connect(eastButton, &QPushButton::clicked, [this]() { gameEngine->movePlayer("east"); });
    connect(westButton, &QPushButton::clicked, [this]() { gameEngine->movePlayer("west"); });

    connect(gameEngine, &GameEngine::playerMoved, this, [this](const QString& description) {
        textDisplay->append(description);
    });

    connect(gameEngine, &GameEngine::updateStatus, this, [this](const QString& status) {
        textDisplay->append(status);
    });
}
