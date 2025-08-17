# pragma once
#include "board.h"
enum GameState { START, PLAYING, GAME_OVER };


#include <iostream>
#include <cmath>
#include <cstdlib>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>








class UI {
public:
    static sf::Font font;
    static sf::Text score_text;
    static sf::Text failure_text;

    static void init();

    static void show_score();
    static void failure();
};
