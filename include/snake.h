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


class snake {
public:
    board& b;// 持有一个 board 的引用
    std::vector<std::pair<int, int>> body;


    snake(board& b);

    void update();

};