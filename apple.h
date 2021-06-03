//
// Created by lauri on 03/06/2021.
//

#ifndef WORM_APPLE_H
#define WORM_APPLE_H


#include <utility>
#include <memory>

class Apple {
public:
    Apple() = delete;
    Apple(int, int);
    void reset(int, int);
    bool is_set(int, int);
private:
    std::unique_ptr<std::pair<int, int>> m_coordinates;
};


#endif //WORM_APPLE_H
