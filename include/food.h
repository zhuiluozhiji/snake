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
    food(board& b);
    void make_food();
};