#include "../include/board.h"




using namespace sf;
using namespace std;

cell::cell(celltype t , direction d) : type(t), dir(d) {
    shape.setSize(Vector2f(CELL_SIZE, CELL_SIZE));
    shape.setFillColor(Color::Magenta);
}


board::board(){
    cells.resize(BOARD_SIZE, vector<cell>(BOARD_SIZE));
    for(size_t i = 0; i < cells.size(); i++){
        for(size_t j = 0; j < cells[i].size(); j++){
            cells[i][j] = cell();
            cells[i][j].shape.setPosition(j * CELL_SIZE, i * CELL_SIZE);
        }
    }
}

void board::draw(RenderWindow& window){
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