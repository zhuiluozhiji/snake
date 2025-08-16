#include "../include/UI.h"

using namespace sf;
using namespace std;

extern int score;
extern RenderWindow window;
extern bool game_over;


// 静态成员变量定义（必须加上类名和作用域）
sf::Font UI::font;
sf::Text UI::score_text;
sf::Text UI::failure_text;

void UI::init() {
    if (!font.loadFromFile("Fonts/weiruanyahei.ttf")) {
        cerr << "Error loading font" << endl;
    }
    
    score_text.setFont(font);
    score_text.setCharacterSize(24);
    score_text.setString("Score: 0");
    score_text.setFillColor(Color::Black);
    score_text.setPosition(BOARD_SIZE * CELL_SIZE / 2 - score_text.getGlobalBounds().width / 2, 10);
    score_text.setStyle(Text::Bold);

    failure_text.setFont(font);
    failure_text.setCharacterSize(48);
    failure_text.setString("Game Over!");
    failure_text.setFillColor(Color::Red);
    failure_text.setPosition(BOARD_SIZE * CELL_SIZE / 2 - failure_text.getGlobalBounds().width / 2, BOARD_SIZE * CELL_SIZE / 2 - failure_text.getGlobalBounds().height / 2);
}

void UI::show_score(){
    score_text.setString("Score: " + to_string(score));
    window.draw(score_text);
}
void UI::failure(){
    game_over = true;
    window.draw(failure_text);
}