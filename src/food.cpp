#include "../include/food.h"

extern int foodSpawnTimer;
extern int bonusSpawnCounter;


#define FOOD_SPAWN_TIME 200

using namespace std;



food::food(board & b) : b(b) , bonus_live(false) , bonus_live_time(0),  bonus_score(0), bonus_position(pair<int, int>(-1, -1)) {}

void food::food_pos(celltype t){
    while(true){
        int x = rand() % BOARD_SIZE;
        int y = rand() % BOARD_SIZE;
        if(b.cells[x][y].type == EMPTY){

            b.cells[x][y].type = t;
            if(t == BONUS) {
                bonus_position = pair<int, int>(x, y); // store bonus food position
            }
            b.cells[x][y].score_val = (t == BONUS) ? bonus_score : 1; // bonus food gives more score
            break;
        }
    }
}
void food::make_food(){//it is the one to be called in main function
    if(bonus_live){
        bonus_live_time++;
        if(bonus_live_time <= BONUS_LIVE_TIME / 4){
            bonus_score = BONUS_MAX_SCORE; // bonus food gives more score
        }
        else if(bonus_live_time <= BONUS_LIVE_TIME / 2){
            bonus_score = BONUS_MAX_SCORE / 2; // bonus food gives less score
        }
        else if(bonus_live_time <= BONUS_LIVE_TIME * 3 / 4){
            bonus_score = BONUS_MAX_SCORE / 4; // bonus food gives even less score
        }
        else if(bonus_live_time <= BONUS_LIVE_TIME) {
            bonus_score = 2; // after bonus time, it becomes normal food
        }
        else if(bonus_live_time > BONUS_LIVE_TIME){
            bonus_live = false;
            bonus_score = 0;
            bonus_live_time = 0;
            b.cells[bonus_position.first][bonus_position.second].type = EMPTY;
        }
        b.cells[bonus_position.first][bonus_position.second].score_val = bonus_score; // keep bonus food on the board
    }
    if(foodSpawnTimer < FOOD_SPAWN_TIME){
        foodSpawnTimer++;
        return;
    }
    celltype t = APPLE; // default food type
    foodSpawnTimer = 0;
    bonusSpawnCounter++;

    if(bonusSpawnCounter >= BONUS_SPAWN_COUNT){
        bonusSpawnCounter = 0;
        // spawn bonus food
        t = BONUS;
        bonus_live = true;
        bonus_live_time = 0; //和函数开头的bonus独立维护中同样有这句话置0 重复
    }
    //if board is full , while will be a dead loop!! to be optimized
    food_pos(t);
    cout << "bonus_score = " << bonus_score << endl;
}
