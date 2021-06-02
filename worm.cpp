//
// Created by lauri on 01/06/2021.
//

#include "worm.h"

Worm::Worm(int x, int y, int length) {
    m_coordinates = std::make_unique<std::vector<std::pair<int, int>>>();
    m_coordinates->emplace_back(x, y);

    for (int i = 0; i <= length; i++) {
        m_coordinates->emplace_back(x, y + i);
    }

    m_direction = std::make_unique<MoveDirection>(MoveDirection::UP);
}

bool Worm::is_set(int requested_x, int requested_y) {
    auto pred = [requested_x, requested_y](const std::pair<int, int> &pair) {
        return pair.first == requested_x && pair.second == requested_y;
    };
    return std::any_of(m_coordinates->begin(), m_coordinates->end(), pred);
}

void Worm::set_direction(MoveDirection direction) {
    m_direction = std::make_unique<MoveDirection>(direction);
    printf("Direction set %i \n", direction);
}

void Worm::move() {
    bool first_coordinate = true;
    int previous_x = -1;
    int previous_y = -1;
    for (auto & coord : *m_coordinates) {

        if (first_coordinate) {
            previous_x = coord.first;
            previous_y = coord.second;

            int new_x = coord.first;
            int new_y = coord.second;

            switch (*m_direction) {
                case UP:
                    new_y = previous_y - 1;
                    break;
                case DOWN:
                    new_y = previous_y + 1;
                    break;
                case RIGHT:
                    new_x = previous_x + 1;
                    break;
                case LEFT:
                    new_x = previous_x - 1;
                    break;
                default:
                    break;
            }

            coord = std::pair<int, int>(new_x, new_y);
            first_coordinate = false;
        } else {
            int new_x = previous_x;
            int new_y = previous_y;

            previous_x = coord.first;
            previous_y = coord.second;

            coord = std::pair<int, int>(new_x, new_y);
        }
    }
}
