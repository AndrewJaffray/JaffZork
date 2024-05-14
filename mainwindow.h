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


    class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void look();
    void pickup();
    void interact();
    void showInventory();

private:
    Ui::MainWindow *ui;
    GameEngine *gameEngine;

    void setupImages();
    void connectSignals();
};

#endif // MAINWINDOW_H

