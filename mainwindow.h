#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QPixmap>
#include <QEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "gameengine.h"
#include "ui_mainwindow.h"

    //declares the MainWindow class which inherits from QMainWindow
    class MainWindow : public QMainWindow {
    Q_OBJECT

    //Constructor that optionally takes a parent widget
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow(); //destructor

    // This is an overridden function from QObject that filters events.
    // it's used to intercept and handle events for watched objects.
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

    //slot functions that are connected to signals
private slots:
    void look();
    void pickup();
    void interact();
    void showInventory();


private:
    Ui::MainWindow *ui; //pointer to the UI object, which manages the UI elements
    GameEngine *gameEngine; //pointer to the GameEngine object which handles game logic

    void setupImages();
    void connectSignals();
};

#endif // MAINWINDOW_H

