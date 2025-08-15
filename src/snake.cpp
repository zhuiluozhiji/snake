#include "../include/snake.h"

extern int dirSpawnTimer;
extern int score;


using namespace sf;
using namespace std;



snake::snake(board& b) : b(b) {
    b.cells[15][15].type = HEAD;
    b.cells[15][16].type = BODY;
    b.cells[15][17].type = BODY;
    b.cells[15][18].type = BODY;

    body.push_back({15, 15});
    body.push_back({15, 16});
    body.push_back({15, 17});
    body.push_back({15, 18});
}


void snake::failure_dect(int x, int y){// x,y is the newly arrived pos of head
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
}

void snake::eat(int x, int y, int tail_x, int tail_y){// x,y is the newly arrived pos of head
    //eat detection
    if(b.cells[x][y].type == APPLE || b.cells[x][y].type == BONUS){
        body.push_back({tail_x, tail_y}); // add a new body segment at the tail position
        b.cells[tail_x][tail_y].type = BODY; // update the tail cell type to BODY
        score += b.cells[x][y].score_val; // update score
    } else {
        // if not eating, just update tail position
        b.cells[tail_x][tail_y].type = EMPTY;
    }
    //b.cells[tail_x][tail_y].dir remains still!! 继承前尾巴的方向
}

void snake::update(){
// last pressed key during the round just ended
    if(dirSpawnTimer < SPEED_TIME){
        dirSpawnTimer++;
    if(Keyboard::isKeyPressed(Keyboard::A)){
        b.cells[body[0].first][body[0].second].dir = LEFT;
    } else if(Keyboard::isKeyPressed(Keyboard::D)){
        b.cells[body[0].first][body[0].second].dir = RIGHT;
    } else if(Keyboard::isKeyPressed(Keyboard::W)){
        b.cells[body[0].first][body[0].second].dir = UP;
    } else if(Keyboard::isKeyPressed(Keyboard::S)){
        b.cells[body[0].first][body[0].second].dir = DOWN;
    }
        return;
    }

    dirSpawnTimer = 0;

    int tail_x = body[body.size() - 1].first;
    int tail_y = body[body.size() - 1].second;
    direction head_dir = b.cells[body[0].first][body[0].second].dir;
    //update position and dir
    for(size_t i = body.size() - 1; i > 0; i--){
        body[i] = body[i - 1];
        //b.cells[body[i].first][body[i].second].dir = b.cells[body[i - 1].first][body[i - 1].second].dir;
    }
    int x = body[0].first;// temporary head x(may fail to exit)
    int y = body[0].second;// temporary head y
    switch (b.cells[x][y].dir) {
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
    failure_dect(x, y);
//success moving
    body[0].first = x;
    body[0].second = y;


    eat(x, y, tail_x, tail_y); // check if eating food and update body


    //update celltype : only need to update head and tail
    b.cells[body[1].first][body[1].second].type = BODY;
    b.cells[body[0].first][body[0].second].type = HEAD;

    // headcell direction (this loop can also detect pressed direction for next round)
    if(Keyboard::isKeyPressed(Keyboard::A)){
        b.cells[body[0].first][body[0].second].dir = LEFT;
    } else if(Keyboard::isKeyPressed(Keyboard::D)){
        b.cells[body[0].first][body[0].second].dir = RIGHT;
    } else if(Keyboard::isKeyPressed(Keyboard::W)){
        b.cells[body[0].first][body[0].second].dir = UP;
    } else if(Keyboard::isKeyPressed(Keyboard::S)){
        b.cells[body[0].first][body[0].second].dir = DOWN;
    }
    else{        //otherwise head-direction remains still
        b.cells[body[0].first][body[0].second].dir = (head_dir);
    }


    cout << "x =  " << body[0].first << ", y = " << body[0].second << " , Direction = " <<  static_cast<int>(b.cells[body[0].first][body[0].second].dir) << ",  score = " << score << endl;

}

