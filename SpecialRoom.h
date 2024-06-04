#ifndef SPECIALROOM_H
#define SPECIALROOM_H

#include "room.h"
#include <QObject>

class SpecialRoom : public Room, public QObject {
    Q_OBJECT
 public :
     SpecialRoom(const std::string& description) : Room(description) {}
void describe() const override {
        Room -> getDescription()
     };

};



#endif // SPECIALROOM_H
