#include "../include/board.h"
#include "../include/snake.h"
#include "../include/food.h"
#include "../include/UI.h"
#include "../include/UI.h"


int dirSpawnTimer = 0;
int foodSpawnTimer = 0;
int bonusSpawnCounter = 0;

int score = 0;

bool paused = false;



using namespace sf;
using namespace std;




GameState state = START;


RenderWindow window(VideoMode(CELL_SIZE * BOARD_SIZE, CELL_SIZE * BOARD_SIZE), "10x10 Chessboard");


int main()
{
    // Initialize a random seed (only call once at the beginning of the program)
    srand(time(0));


    window.setFramerateLimit(60);

    Clock clock;
    float dt;
    float multiplier = 60.f;
    //DEFINE
    board* gb = new board();
    snake* s = new snake(*gb);
    food* f = new food(*gb);
    UI::init(); // Initialize UI static members

    while (window.isOpen())
    {
        
        Event event;
        while (window.pollEvent(event))
        {
            
            if (event.type == Event::Closed)
                window.close();
            if (state == START) {
                // 鼠标点击或按键进入游戏
                if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter) {
                    state = PLAYING;
                }
                if (event.type == Event::MouseButtonPressed) {
                    state = PLAYING;
                }
            }
            else if (state == PLAYING) {
                if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space)
                    paused = !paused;
            }
            else if(state == GAME_OVER){
                if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter) {
                    // 释放旧对象
                    delete gb;
                    delete s;
                    delete f;
                    // 创建新对象
                    gb = new board();
                    s = new snake(*gb);
                    f = new food(*gb);
                    state = PLAYING;
                    score = 0;
                }
                if (event.type == Event::MouseButtonPressed) {
                    // 释放旧对象
                    delete gb;
                    delete s;
                    delete f;
                    // 创建新对象
                    gb = new board();
                    s = new snake(*gb);
                    f = new food(*gb);
                    state = PLAYING;
                    score = 0;
                }                

            }
        }
        window.clear(Color::White);
//UPDATE and DRAW
        if (state == START) {
            // 绘制开始界面
            sf::Font font;
            font.loadFromFile("Fonts/weiruanyahei.ttf");
            sf::Text start_text("Press Enter or Click to Start", font, 36);
            start_text.setFillColor(sf::Color::Blue);
            start_text.setPosition(BOARD_SIZE * CELL_SIZE / 2 - start_text.getGlobalBounds().width / 2,
                                   BOARD_SIZE * CELL_SIZE / 2 - start_text.getGlobalBounds().height / 2);
            window.draw(start_text);
        } else if (state == PLAYING) {
            dt = clock.restart().asSeconds();
            if(!paused) {
                s->update();
                f->make_food();
            }
            gb->draw(window);
            UI::show_score();

        }
        else if(state == GAME_OVER){
            gb->draw(window);
            UI::show_score();
            UI::failure();
            
        } 






        window.display();
    }

    return 0;
}