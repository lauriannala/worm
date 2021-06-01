//
// Created by lauri on 01/06/2021.
//

#ifndef WORM_WORM_H
#define WORM_WORM_H


#include <vector>

class Worm {
public:
    Worm() = delete;
    Worm(int, int, int);
    bool is_set(int, int);
private:
    std::vector<std::pair<int, int>> m_coordinates;
};


#endif //WORM_WORM_H
