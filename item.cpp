#include "item.h"
#include <string>


Item::Item(const std::string& itemName) : name(itemName) {}

std::string Item::getName() const {
    return name;
}



