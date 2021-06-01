//
// Created by lauri on 01/06/2021.
//

#include "worm.h"

Worm::Worm(int x, int y, int length) {
    m_coordinates.emplace_back(x, y);

    for (int i = 0; i <= length; i++) {
        m_coordinates.emplace_back(x, y + i);
    }
}

bool Worm::is_set(int requested_x, int requested_y) {
    auto pred = [requested_x, requested_y](const std::pair<int, int> &pair) {
        return pair.first == requested_x && pair.second == requested_y;
    };
    return std::any_of(m_coordinates.begin(), m_coordinates.end(), pred);
}
