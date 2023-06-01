#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>

//declares structures with appropriate data types to store data
struct node { 
  int up;
  int left;
  int right;
  int down;         
  int visited;
};

struct poss_path { 
  int start_coord[2];
  int next_coord[2];
  int weight;
};

struct wall_exist{
    int start_coord[2];
    int next_coord[2];
};

//declare maze, walls and iterators
struct node maze[4][4];
struct poss_path available[25];
int pp = 0;
struct wall_exist walls[25];
int wallit = 0;

int current[2] = {0,0};

//assign random weights for paths between nodes for prims algorithm
struct node create_node(){
    struct node x;
    x.up = rand() % 20;
    x.left = rand() % 20;
    x.right = rand() % 20;
    x.down = rand() % 20;
    x.visited = 0;
    return x;
}

//create data for possible path
struct poss_path makeposs(int strtcoord[2], int nextcoord[2], int weight){
    struct poss_path x;
    for (int i = 0; i < 2; i++){
        x.start_coord[i] = strtcoord[i];
        x.next_coord[i] = nextcoord[i];
    }
    x.weight = weight;
    return x;
}

//create grid of empty nodes for maze
void create_maze(){
    for (int i =0; i<4; i++){
        for (int j =0; j<4; j++){
            maze[i][j] = create_node();
        }    
    }
    maze[0][0].visited = 1;

    for (int i =0; i< 4; i++){
        maze[0][i].up = 0;
        maze[i][0].left = 0;
        maze[3][i].down = 0;
        maze[i][3].right = 0;
    }
}

//gets available paths that can be taken from particular node
void get_available(){
    struct node temp = maze[current[0]][current[1]];
    int weight[] = {temp.up, temp.down, temp.left, temp.right};
    int posspath[4][2] = {{current[0],(current[1]+1)}, {current[0], (current[1]-1)}, {(current[0]-1), current[1]}, {(current[0]+1), current[1]}};
    for (int i = 0; i < 4; i ++){
        if((posspath[i][0] < 0) || (posspath[i][1] < 0) || (posspath[i][1] > 3) || (posspath[i][0] > 3)){
            continue;
        }
        if ((weight[i] != 0) && (maze[posspath[i][0]][posspath[i][1]].visited == 0)){
            available[pp] = makeposs(current, posspath[i], weight[i]);
        }
    }
}

//takes path of lowest node and creates maze
void expand(){
    for(int z = 0; z<16; z++){
        get_available();
        struct poss_path lowest;
        int lowest_weight = 201;

        for(int i = 0; i< pp+1; i++){
            if (available[i].weight < lowest_weight){
                lowest_weight = available[i].weight;
                lowest = available[i];
            }
        }
        struct wall_exist wall;
        wall.start_coord[0] = current[0];
        wall.start_coord[1] = current[1];
        wall.next_coord[0] = lowest.next_coord[0];
        wall.next_coord[1] = lowest.next_coord[1];
        walls[wallit] = wall;
        wallit++;

        current[0] = lowest.next_coord[0];
        current[1] = lowest.next_coord[1];

        maze[lowest.next_coord[0]][lowest.next_coord[1]].visited = 1;
    }
}

struct cost{
    int order;
    int coord[2];
    int visited;
};
struct cost nodecosts[16];
int costrep = 1;
struct cost path[20];
int pathrep = 0;

//calculates cost from start to every node in maze
void check_neighbours(){
    for (int z = 0; z<10; z++){

        for (int i = 0; i< costrep; i++){
            if(nodecosts[i].visited == 1){
                continue;
            }
            int coord[2];
            coord[0] =  nodecosts[i].coord[0];
            coord[1] = nodecosts[i].coord[1];
            
            int cost = nodecosts[i].order;

            int posspath[4][2] = {{coord[0],(coord[1]+1)}, {coord[0], (coord[1]-1)}, {(coord[0]-1), coord[1]}, {(coord[0]+1), coord[1]}};
            for(int j = 0; j<4; j++){
                for (int k = 0; k < wallit; k++){
                    if(((walls[k].start_coord[0] == coord[0]) && (walls[k].start_coord[1] == coord[1])) &&((walls[k].next_coord[0] == posspath[j][0]) && (walls[k].next_coord[1] == posspath[j][1]))){
                        struct cost x;
                        x.coord[0] = posspath[j][0];
                        x.coord[1] = posspath[j][1];
                        x.order = cost+1;
                        nodecosts[costrep] = x;
                        costrep++;
                    }
                }
            }
            nodecosts[i].visited = 1;
        }
    }
    struct cost x;
    x.coord[0] = nodecosts[costrep-1].coord[0];
    x.coord[1] = nodecosts[costrep-1].coord[1];
    x.order = nodecosts[costrep-1].order;
    path[pathrep] = x;
    pathrep++;
}

//using costs calculated, uses dijkstra to traverse the maze
void traverse(){
    while ((path[pathrep-1].order != 1)){
        int cost = path[pathrep-1].order;
        int coord[2] = {path[pathrep-1].coord[0], path[pathrep-1].coord[1]};
        for (int i = costrep; i>0; i--){
            for (int j = 0; j<wallit; j++){
                if((nodecosts[i].order == (cost-1)) && (((walls[j].start_coord[0] == coord[0]) && (walls[j].start_coord[1] == coord[1])) &&((walls[j].next_coord[0] == nodecosts[i].coord[0]) && (walls[j].next_coord[1] == nodecosts[i].coord[1])) || ((walls[j].start_coord[0] == nodecosts[i].coord[0]) && (walls[j].start_coord[1] == nodecosts[i].coord[1])) &&((walls[j].next_coord[0] == coord[0]) && (walls[j].next_coord[1] == coord[1]))))
                {
                    path[pathrep] = nodecosts[i];
                    pathrep++;
                    break;
                }
            }
        }
    }
    
}



//draws the maze + walls
void drawgrid(){
  background();
  setRGBColour(100,100,100);
  fillRect(0,0, 600, 600);
  setColour(black);
  fillRect(40, 80, 500, 500);
  setColour(white);
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 4; j++){
      fillRect(60 + (120*j), 100 + (120*i), 100, 100);
    }
  }
  
  int x, y, x2, y2;
  for (int z = 0; z < wallit; z++){
    x = walls[z].start_coord[1];
    y = walls[z].start_coord[0];
    x2= walls[z].next_coord[1];
    y2 = walls[z].next_coord[0];

    //fills in gaps for the path
    fillRect(60 + (120*x), 100 + (120*y), 100, 100);
    if (x < x2){
      fillRect(160 + (120*x), 100 + (120*(y)), 20, 100);
    }
    else if (x > x2){
      fillRect(40 + (120*x), 100 + (120*(y)), 20, 100);
    }
    else if (y > y2)
    {
        fillRect(60 + (120*x), 80+(120*y), 100, 20);
    }
    else if (y < y2)
    {
      fillRect(60 + (120*x), 200+(120*y), 100, 20);
    }
  }
  setColour(green);
  fillRect(60 + (120*x), 100 + (120*y), 100, 100);
  fillRect(60 , 100, 100, 100);
  
}

//dcelares variables used for player
int x,y = 0;
int x_co[3] = {60, 110, 160};
int y_co[3]= {100, 200, 100};
int rotate[3][4][2] = {{{-100,0}, {0,100}, {100,0}, {0,-100}}, {{50,50}, {50,-50}, {-50,-50}, {-50,50}}, {{0,-100}, {-100,0}, {0,100}, {100,0}}}; //determines rotation of triangle
int forward_move[4][2] = {{0,120}, {120,0}, {0,-120}, {-120,0}};
int direction = 0; // down, right, up, left

void update(){
    foreground();
    setColour(blue);
    sleep(500);
    clear();
    fillPolygon(3, x_co, y_co);
}

void left(){
    if (direction++ > 2){
        direction = 0;
    }
    for (int i = 0; i < 3; i++){
        x_co[i] += rotate[i][direction][0];
        y_co[i] += rotate[i][direction][1];
    }
    update();
}

void right(){
    for (int i = 0; i < 3; i++){
        x_co[i] -= rotate[i][direction][0];
        y_co[i] -= rotate[i][direction][1];
    }
    direction--;
    if (direction < 0){
        direction = 3;
    }
    update();
}


void forward(){
    for(int i =0; i<3; i++){
        x_co[i] += forward_move[direction][0];
        y_co[i] += forward_move[direction][1];
    }
    update();
}

//moves player through the maze
void move()
{
    update();
    for(int i = pathrep-1; i >-1; i--){
        if((path[i].coord[1] == x) && (path[i].coord[0] ==y)){
            continue;
        }
        if (direction == 0){
            if(path[i].coord[1] > x){
                left();
            }
            else if(path[i].coord[1] < x){
                right();
            }
        }
        if (direction == 1){
            if(path[i].coord[0] > y){
                right();
            }
            else if(path[i].coord[0] < y){
                left();
            }
        }
        if (direction == 2){
            if(path[i].coord[1] > x){
                right();
            }
            else if(path[i].coord[1] < x){
                left();
            }
        }
        if (direction == 3){
            if(path[i].coord[0] > y){
                left();
            }
            else if(path[i].coord[0] < y){
                right();
            }
        }
        forward();
        x= path[i].coord[1];
        y= path[i].coord[0];
    }
}

int main(void)
{
    create_maze();
    expand();
    check_neighbours();
    traverse();
    setWindowSize(600, 600);
    drawgrid();
    move();
}