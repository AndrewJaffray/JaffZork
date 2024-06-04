#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <algorithm>

//template class for an inventory with items of type T
template <typename T>
class Inventory {
public:
    void addItem(const T& item);
    void removeItem(const T& item);
    bool hasItem(const T& item) const;
    std::vector<T> getItems() const;

private:
    std::vector<T> items;
};

template <typename T>
void Inventory<T>::addItem(const T& item) {
    items.push_back(item); //adds the item to the end of a vector
}

template <typename T>
void Inventory<T>::removeItem(const T& item) {
    //finds the item in the vector
    auto it = std::find(items.begin(), items.end(), item);
    if (it != items.end()) { //removes the item if it's found
        items.erase(it);
    }
}

template <typename T>
bool Inventory<T>::hasItem(const T& item) const {
    //checks if the item is in the vector and returns true if it is
    return std::find(items.begin(), items.end(), item) != items.end();
}

template <typename T>
std::vector<T> Inventory<T>::getItems() const {
    //returns a copy of the vector of items
    return items;
}

#endif // INVENTORY_H
