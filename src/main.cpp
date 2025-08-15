#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>


using namespace sf;
using namespace std;

#define BOARD_SIZE 20
#define CELL_SIZE 40
#define SPEED_TIME 5
#define FOOD_SPAWN_TIME 200

int dirSpawnTimer = 0;
int foodSpawnTimer = 0;

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
    RectangleShape shape;

    cell(celltype t = EMPTY, direction d = UP) : type(t), dir(d) {
        shape.setSize(Vector2f(CELL_SIZE, CELL_SIZE));
        shape.setFillColor(Color::Magenta);
    }

};

class board{
public:
    vector<vector<cell>> cells;


    board(){
        cells.resize(BOARD_SIZE, vector<cell>(BOARD_SIZE));
        for(size_t i = 0; i < cells.size(); i++){
            for(size_t j = 0; j < cells[i].size(); j++){
                cells[i][j] = cell();
                cells[i][j].shape.setPosition(j * CELL_SIZE, i * CELL_SIZE);
            }
        }
    }

    void draw(RenderWindow& window){
        for(size_t i = 0; i < cells.size(); i++){
            for(size_t j = 0; j < cells[i].size(); j++){
                if(cells[i][j].type == BODY){
                    cells[i][j].shape.setFillColor(Color::Yellow);
                } else if(cells[i][j].type == FOOD){
                    cells[i][j].shape.setFillColor(Color::Red);
                } else if(cells[i][j].type == HEAD){
                    cells[i][j].shape.setFillColor(Color::Green);
                } else if(cells[i][j].type == EMPTY){
                    cells[i][j].shape.setFillColor(Color::White);
                }
                // Draw the cell
                window.draw(cells[i][j].shape);
            }
        }
    }

    void food(){
        if(foodSpawnTimer < FOOD_SPAWN_TIME){
            foodSpawnTimer++;
            return;
        }
        foodSpawnTimer = 0;
        while(true){
            int x = rand() % BOARD_SIZE;
            int y = rand() % BOARD_SIZE;
            if(cells[x][y].type == EMPTY){
                cells[x][y].type = FOOD;
                break;
            }
        }
    }



};

//specially designed for signal updating
class snake : public board{
public:
    vector<pair<int, int>> body;


    snake() : board() {
        cells[15][15].type = HEAD;
        cells[15][16].type = BODY;
        cells[15][17].type = BODY;
        cells[15][18].type = BODY;

        body.push_back({15, 15});
        body.push_back({15, 16});
        body.push_back({15, 17});
        body.push_back({15, 18});
    }

    void update(){
// last pressed key during the round just ended
        if(dirSpawnTimer < SPEED_TIME){
            dirSpawnTimer++;
        if(Keyboard::isKeyPressed(Keyboard::A)){
            cells[body[0].first][body[0].second].dir = LEFT;
        } else if(Keyboard::isKeyPressed(Keyboard::D)){
            cells[body[0].first][body[0].second].dir = RIGHT;
        } else if(Keyboard::isKeyPressed(Keyboard::W)){
            cells[body[0].first][body[0].second].dir = UP;
        } else if(Keyboard::isKeyPressed(Keyboard::S)){
            cells[body[0].first][body[0].second].dir = DOWN;
        }
            return;
        }

        dirSpawnTimer = 0;

        int tail_x = body[body.size() - 1].first;
        int tail_y = body[body.size() - 1].second;
        direction head_dir = cells[body[0].first][body[0].second].dir;
        //update position and dir
        for(size_t i = body.size() - 1; i > 0; i--){
            body[i] = body[i - 1];
            cells[body[i].first][body[i].second].dir = cells[body[i - 1].first][body[i - 1].second].dir;
        }
        int x = body[0].first;// temporary head x(may fail to exit)
        int y = body[0].second;// temporary head y
        switch (cells[x][y].dir) {
            case UP:
                x -= 1;
                break;
            case DOWN:
                x += 1;
                break;
            case LEFT:
                y -= 1;
                break;
            case RIGHT:
                y += 1;
                break;
        }

//failure detection
        if(x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE){
            cout << "Game Over! You hit the wall!" << endl;
            exit(0);
            return;
        }
        for(size_t i = 1; i < body.size(); i++){
            if(body[i].first == x && body[i].second == y){
                cout << "Game Over! You hit yourself!" << endl;
                exit(0);
                return;
            }
        }
//success moving
        body[0].first = x;
        body[0].second = y;
//eat detection
        if(cells[x][y].type == FOOD){
            body.push_back({tail_x, tail_y}); // add a new body segment at the tail position
            cells[tail_x][tail_y].type = BODY; // update the tail cell type to BODY
        } else {
            // if not eating, just update tail position
            cells[tail_x][tail_y].type = EMPTY;
        }



        //update celltype : only need to update head and tail
        cells[body[1].first][body[1].second].type = BODY;
        cells[body[0].first][body[0].second].type = HEAD;

        // headcell direction (this loop can also detect pressed direction for next round)
        if(Keyboard::isKeyPressed(Keyboard::A)){
            cells[body[0].first][body[0].second].dir = LEFT;
        } else if(Keyboard::isKeyPressed(Keyboard::D)){
            cells[body[0].first][body[0].second].dir = RIGHT;
        } else if(Keyboard::isKeyPressed(Keyboard::W)){
            cells[body[0].first][body[0].second].dir = UP;
        } else if(Keyboard::isKeyPressed(Keyboard::S)){
            cells[body[0].first][body[0].second].dir = DOWN;
        }
        else{        //otherwise head-direction remains still
            cells[body[0].first][body[0].second].dir = (head_dir);
        }


        cout << "x =  " << body[0].first << ", y = " << body[0].second << " , Direction = " <<  static_cast<int>(cells[body[0].first][body[0].second].dir) << endl;

    }

    // void draw_head(RenderWindow & window){
    //     for(size_t i = 0; i < cells.size(); i++){
    //         for(size_t j = 0; j < cells[i].size(); j++){
    //             if(cells[i][j].type == BODY){
    //                 cells[i][j].shape.setFillColor(Color::Yellow);
    //             } else if(cells[i][j].type == FOOD){
    //                 cells[i][j].shape.setFillColor(Color::Red);
    //             } else if(cells[i][j].type == HEAD){
    //                 cells[i][j].shape.setFillColor(Color::Green);
    //             } else if(cells[i][j].type == EMPTY){
    //                 cells[i][j].shape.setFillColor(Color::White);
    //             }
    //             // Draw the cell
    //         }
    //     }

    //     window.draw(cells[body[0].first][body[0].second].shape);
    // }

};



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

    snake s;


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
        s.food();



        window.clear(Color::Black);
//DRAW
        s.draw(window);



        window.display();
    }

    return 0;
}