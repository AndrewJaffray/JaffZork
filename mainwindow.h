#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "gameengine.h"

    class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    GameEngine* gameEngine;
    QTextEdit* textDisplay;
    QPushButton* northButton;
    QPushButton* southButton;
    QPushButton* eastButton;
    QPushButton* westButton;

    void setupUI();
    void connectSignals();
};

#endif // MAINWINDOW_H

