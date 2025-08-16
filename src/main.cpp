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
bool game_over = false;


using namespace sf;
using namespace std;


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
    board gb;
    snake s(gb);
    food f(gb);
    UI::init(); // Initialize UI static members

    while (window.isOpen())
    {
        
        Event event;
        while (window.pollEvent(event))
        {
            
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space)
                paused = !paused; // 按P键切换暂停状态
        }
        dt = clock.restart().asSeconds();
//UPDATE
        if(!paused && !game_over){
            s.update();
            f.make_food();
        }



        window.clear(Color::Black);
//DRAW
        gb.draw(window);
        UI::show_score();
        if(game_over) UI::failure();

        window.display();
    }

    return 0;
}