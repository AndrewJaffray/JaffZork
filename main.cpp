#include <QApplication>
#include "mainwindow.h"

    int main(int argc, char *argv[]) {
    QApplication app(argc, argv);  // Initialize the QApplication object

    MainWindow window;  // Create the main window
    window.show();      // Show the main window

    return app.exec();  // Enter the main event loop and wait until exit() is called
}
