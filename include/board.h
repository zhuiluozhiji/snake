#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#define BOARD_SIZE 20
#define CELL_SIZE 40
#define SPEED_TIME 5




enum celltype{
    EMPTY,
    BODY,
    FOOD,
    HEAD
};

enum direction{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class cell{
public:
    celltype type;
    direction dir;
    sf::RectangleShape shape;

    cell(celltype t = EMPTY, direction d = UP);

};


class board{
public:
    std::vector<std::vector<cell>> cells;


    board();

    void draw(sf::RenderWindow& window);

};