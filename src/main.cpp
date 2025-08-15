#include "../include/board.h"
#include "../include/snake.h"
#include "../include/food.h"


int dirSpawnTimer = 0;
int foodSpawnTimer = 0;



using namespace sf;
using namespace std;




int main()
{
    // Initialize a random seed (only call once at the beginning of the program)
    srand(time(0));
    RenderWindow window(VideoMode(CELL_SIZE * BOARD_SIZE, CELL_SIZE * BOARD_SIZE), "10x10 Chessboard");
    window.setFramerateLimit(60);



    Clock clock;
    float dt;
    float multiplier = 60.f;
    //DEFINE
    board gb;
    snake s(gb);
    food f(gb);


    while (window.isOpen())
    {
        
        Event event;
        while (window.pollEvent(event))
        {
            
            if (event.type == Event::Closed)
                window.close();
        }
        dt = clock.restart().asSeconds();
//UPDATE
        s.update();
        f.make_food();



        window.clear(Color::Black);
//DRAW
        gb.draw(window);



        window.display();
    }

    return 0;
}