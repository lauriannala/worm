//
// Created by lauri on 03/06/2021.
//

#include "apple.h"

Apple::Apple(int x, int y) {
    reset(x, y);
}

void Apple::reset(int x, int y) {
    m_coordinates = std::make_unique<std::pair<int, int>>(std::pair<int, int>(x, y));
}

bool Apple::is_set(int x, int y) {
    return m_coordinates->first == x && m_coordinates->second == y;
}
