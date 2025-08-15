#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>


using namespace sf;
using namespace std;

#define BOARD_SIZE 10
#define CELL_SIZE 40

enum cellcase{
    EMPTY,
    BODY,
    FOOD,
    HEAD
};

class cell{
public:
    cellcase type;
    RectangleShape shape;

    cell(cellcase t = EMPTY) : type(t) {
        shape.setSize(Vector2f(CELL_SIZE, CELL_SIZE));
        //shape.setFillColor(Color::White);
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
                } else {
                    cells[i][j].shape.setFillColor(Color::White);
                }
                // Draw the cell
                window.draw(cells[i][j].shape);
            }
        }
    }
};

int main()
{

    RenderWindow window(VideoMode(CELL_SIZE * BOARD_SIZE, CELL_SIZE * BOARD_SIZE), "10x10 Chessboard");
    window.setFramerateLimit(60);
    //DEFINE

    board b;
    b.cells[0][0].type = HEAD; // Set the head of the snake
    b.cells[0][1].type = BODY; // Set the body of the snake
    b.cells[0][2].type = BODY; // Set the body of the snake
    b.cells[1][2].type = FOOD; // Set the food

    while (window.isOpen())
    {
        
        Event event;
        while (window.pollEvent(event))
        {
            
            if (event.type == Event::Closed)
                window.close();
        }
//UPDATE
        



        window.clear(Color::Black);
//DRAW
        b.draw(window);



        window.display();
    }

    return 0;
}