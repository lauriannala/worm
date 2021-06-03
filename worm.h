//
// Created by lauri on 01/06/2021.
//

#ifndef WORM_WORM_H
#define WORM_WORM_H


#include <vector>
#include <memory>

enum MoveDirection : int {
    UP = 0,
    DOWN = 1,
    RIGHT = 2,
    LEFT = 3
};

class Worm {
public:
    Worm() = delete;
    Worm(int, int, int);
    bool is_set(int, int);
    bool has_collisions(int requested_x, int requested_y);
    void set_direction(MoveDirection);
    void reset(int x, int y, int length);
    void move();
private:
    std::unique_ptr<std::vector<std::pair<int, int>>> m_coordinates;
    std::unique_ptr<MoveDirection> m_direction;
};

#endif //WORM_WORM_H
