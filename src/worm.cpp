//
// Created by lauri on 01/06/2021.
//

#include "../include/worm.h"
#include "../include/config.h"

Worm::Worm(int x, int y, int length) {
    reset(x, y, length);
}

bool Worm::is_set(int requested_x, int requested_y) {
    auto pred = [requested_x, requested_y](const std::pair<int, int> &pair) {
        return pair.first == requested_x && pair.second == requested_y;
    };
    return std::any_of(m_coordinates->begin(), m_coordinates->end(), pred);
}

bool Worm::has_collisions(int requested_x, int requested_y) {
    auto pred = [requested_x, requested_y](const std::pair<int, int> &pair) {
        return pair.first == requested_x && pair.second == requested_y;
    };
    auto matches = std::count_if(m_coordinates->begin(), m_coordinates->end(), pred);
    return matches > 1;
}

void Worm::set_direction(MoveDirection direction) {
    if (*m_direction == MoveDirection::UP && direction == MoveDirection::DOWN)
        return;
    if (*m_direction == MoveDirection::DOWN && direction == MoveDirection::UP)
        return;
    if (*m_direction == MoveDirection::RIGHT && direction == MoveDirection::LEFT)
        return;
    if (*m_direction == MoveDirection::LEFT && direction == MoveDirection::RIGHT)
        return;

    m_direction = std::make_unique<MoveDirection>(direction);
    printf("Direction set %i \n", direction);
}

void Worm::move() {
    bool first_coordinate = true;
    int previous_x = -1;
    int previous_y = -1;
    std::pair<int, int> new_tail;
    if (*m_should_grow) {
        std::copy(m_coordinates->end(), m_coordinates->end(), &new_tail);
    }
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
            
            if (new_x == WIDTH) new_x = 0;
            if (new_y == HEIGHT) new_y = 0;
            if (new_x == -1) new_x = WIDTH;
            if (new_y == -1) new_y = HEIGHT;

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
    if (*m_should_grow) {
        m_coordinates->emplace_back(new_tail);
        m_should_grow = std::make_unique<bool>(false);
    }
}

void Worm::reset(int x, int y, int length) {
    m_coordinates = std::make_unique<std::vector<std::pair<int, int>>>();

    for (int i = 0; i <= (length - 1); i++) {
        m_coordinates->emplace_back(x, y + i);
    }

    m_direction = std::make_unique<MoveDirection>(MoveDirection::UP);
    m_should_grow = std::make_unique<bool>(false);
}

void Worm::grow() {
    m_should_grow = std::make_unique<bool>(true);
}
