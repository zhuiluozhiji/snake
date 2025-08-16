# pragma once

enum GameState { START, PLAYING, GAME_OVER };


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




class UI {
public:
    static sf::Font font;
    static sf::Text score_text;
    static sf::Text failure_text;

    static void init();

    static void show_score();
    static void failure();
};
