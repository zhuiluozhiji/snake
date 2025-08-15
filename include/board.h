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
#define FOOD_SPAWN_TIME 200
#define BONUS_SPAWN_COUNT 5
#define BONUS_LIVE_TIME 800
#define BONUS_GRADE 4
#define BONUS_MAX_SCORE 16



enum celltype{
    EMPTY,
    BODY,
    APPLE,
    BONUS,
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
    int score_val; 
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