#pragma once
#include "board.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>


class food {
public:
    board& b;
    bool bonus_live;
    int bonus_score;
    int bonus_live_time;
    std::pair<int, int> bonus_position;
    food(board& b);
    void food_pos(celltype t = APPLE);
    void make_food();
};