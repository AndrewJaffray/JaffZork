#ifndef ITEM_H
#define ITEM_H

#include "GameEntity.h"
#include <string>

class Item : public GameEntity {

public:
    Item(const std::string& itemName);
    std::string getName() const;
    void interact() override;

private:
    std::string name;
};
#endif // ITEM_H
