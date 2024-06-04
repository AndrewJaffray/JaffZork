#ifndef ITEMCONTAINER_H
#define ITEMCONTAINER_H

#include <vector>

template <typename T>
class ItemContainer {
    std::vector<T> items;
public:
    void addItem(const T& item) {
        items.push_back(item);
    }
    void removeItem(const T& item) {
        items.erase(std::remove(items.begin(), items.end(), item), items.end());

    }
    T getItem(int index) const {
        return items.at(index);
    }
};

#endif // ITEMCONTAINER_H
