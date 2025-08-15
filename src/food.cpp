#include "../include/food.h"

extern int foodSpawnTimer;

#define FOOD_SPAWN_TIME 200


food::food(board & b) : b(b) {}


void food::make_food(){
    if(foodSpawnTimer < FOOD_SPAWN_TIME){
        foodSpawnTimer++;
        return;
    }
    foodSpawnTimer = 0;
//if board is full , while will be a dead loop!! to be optimized
    while(true){
        int x = rand() % BOARD_SIZE;
        int y = rand() % BOARD_SIZE;
        if(b.cells[x][y].type == EMPTY){
            b.cells[x][y].type = FOOD;
            break;
        }
    }
}
