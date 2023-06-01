#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>

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

struct node maze[4][4];
struct poss_path available[20];
int pp = 0;
struct wall_exist walls[100];
int wallit = 0;

int current[2] = {0,0};

void set_available(){
    struct poss_path x;
    x.start_coord[0] = -1;
    x.start_coord[1] = -1;
    x.next_coord[0] = -1;
    x.next_coord[0] = -1;
    x.weight = 201;
    for (int i =0; i<20; i++){
        available[i] = x;
    }
}

void set_walls(){
    struct wall_exist x;
    x.start_coord[0] = -1;
    x.start_coord[1] = -1;
    x.next_coord[0] = -1;
    x.next_coord[1] = -1;
    for (int i = 0; i < 100; i++){
        walls[i]=x;
    }
}

struct node create_node(){
    struct node x;
    x.up = rand() % 20;
    x.left = rand() % 20;
    x.right = rand() % 20;
    x.down = rand() % 20;
    x.visited = 0;
    return x;
}

struct poss_path makeposs(int strtcoord[2], int nextcoord[2], int weight){
    struct poss_path x;
    for (int i = 0; i < 2; i++){
        x.start_coord[i] = strtcoord[i];
        x.next_coord[i] = nextcoord[i];
    }
    x.weight = weight;
    return x;
}

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

void print_maze(){
    for (int i = 0; i < 4; i++){
        char line[4];
        for(int j =0; j<4; j++){
            if (maze[i][j].visited == 0){
                printf("w");
            }
            else{
                printf("v");
            }
        }
        printf("\n");
    }
    printf("\n");
}

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

void expand(){
    for(int z = 0; z<10; z++){
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


        //printf("%d %d\n", lowest.next_coord[0], lowest.next_coord[1]);
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

void setcost(){
    struct cost x;
    x.order = -1;
    x.coord[0] = -10;
    x.coord[1] = -10;
    x.visited = 0;
    for (int i = 0; i<16; i++){
        nodecosts[i] = x;
    }

    nodecosts[0].coord[0] = 0;
    nodecosts[0].coord[1] = 0;
    nodecosts[0].order = 0;
}

//taking the 
void check_neighbours(){
    for (int z = 0; z<10; z++){

    for (int i = 0; i< costrep; i++){
        //printf("%d\n", i);
        if(nodecosts[i].visited == 1){
            //printf("node %d %d visited\n", nodecosts[i].coord[0], nodecosts[i].coord[1]);
            continue;
        }
        int coord[2];
        coord[0] =  nodecosts[i].coord[0];
        coord[1] = nodecosts[i].coord[1];
        
        int cost = nodecosts[i].order;
        //printf("%d %d checking %d\n", coord[0], coord[1], (cost+1));

        //printf("%d %d\n", coord[0], coord[1]);
        int posspath[4][2] = {{coord[0],(coord[1]+1)}, {coord[0], (coord[1]-1)}, {(coord[0]-1), coord[1]}, {(coord[0]+1), coord[1]}};
        for(int j = 0; j<4; j++){
            for (int k = 0; k < wallit; k++){
                if(((walls[k].start_coord[0] == coord[0]) && (walls[k].start_coord[1] == coord[1])) &&((walls[k].next_coord[0] == posspath[j][0]) && (walls[k].next_coord[1] == posspath[j][1]))){
                    //printf("yeet\n");
                    //printf("%d %d yis\n", posspath[j][0], posspath[j][1]);
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
}

struct cost path[20];
int pathrep = 0;

void traverse(){
    while ((path[pathrep-1].order != 1)){
        int cost = path[pathrep-1].order;
        int coord[2] = {path[pathrep-1].coord[0], path[pathrep-1].coord[1]};
        //printf("%d %d %d\n", cost, coord[0], coord[1]);
        for (int i = costrep; i>0; i--){
            for (int j = 0; j<wallit; j++){

                //printf("%d %d %d\n", nodecosts[i].order, nodecosts[i].coord[0], nodecosts[i].coord[1]);
                if((nodecosts[i].order == (cost-1)) && (((walls[j].start_coord[0] == coord[0]) && (walls[j].start_coord[1] == coord[1])) &&((walls[j].next_coord[0] == nodecosts[i].coord[0]) && (walls[j].next_coord[1] == nodecosts[i].coord[1])) || ((walls[j].start_coord[0] == nodecosts[i].coord[0]) && (walls[j].start_coord[1] == nodecosts[i].coord[1])) &&((walls[j].next_coord[0] == coord[0]) && (walls[j].next_coord[1] == coord[1]))))
                {
                    //printf("[%d %d] ", nodecosts[i].coord[0], nodecosts[i].coord[1]);
                    path[pathrep] = nodecosts[i];
                    pathrep++;
                    break;
                }
            }
        }
        //printf("\n");
    }
    
}

const int width = 600;
const int height = 600;
const int waitTime = 25;
const int squareSize = 60;
const int moveDistance = 8;

// Set the background contents, which is then always displayed and
// not modified.

void drawgrid(){
  background();
  setRGBColour(100,100,100);
  fillRect(0,0, 600, 600);
  setColour(black);
  fillRect(40, 80, 480, 20);
  fillRect(40, 80, 20, 480);
  fillRect(520, 80, 20, 480);
  fillRect(40, 560, 500, 20);
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 4; j++){
      fillRect(60 + (120*j), 100 + (120*i), 100, 100);
    }
  }
  
  int x, y, x2, y2;
  setColour(white);
  for (int z = 0; z < wallit; z++){
    x = walls[z].start_coord[1];
    y = walls[z].start_coord[0];
    x2= walls[z].next_coord[1];
    y2 = walls[z].next_coord[0];


    //printf("%d %d %d %d", x,y,x2,y2);
    fillRect(60 + (120*x), 100 + (120*y), 100, 100);
    if (x < x2){
      
      fillRect(160 + (120*x), 100 + (120*(y)), 20, 100);
    }
    if (x > x2){
      
      fillRect(40 + (120*x), 100 + (120*(y)), 20, 100);
    }
    if (y > y2)
    {
        fillRect(60 + (120*x), 80+(120*y), 100, 20);
    }

    if (y < y2)
    {
      //printf("%d %d %d %d", x,y,x2,y2);
      fillRect(60 + (120*x), 200+(120*y), 100, 20);
    }
  }
  setColour(green);
  fillRect(60 + (120*x), 100 + (120*y), 100, 100);
  fillRect(60 , 100, 100, 100);
  
}

void move()
{
    foreground();
    setColour(blue);
    fillRect(60, 100, squareSize, squareSize);
    
    for(int i = pathrep-1; i >-1; i--){
        sleep(500);
        int x = (60 + (120*path[i].coord[1]));
        int y = 100 + (120*path[i].coord[0]);
        clear();
        fillRect(x, y, squareSize, squareSize);
    }

}

int main(void)
{
    create_maze();
    set_available();
    expand();
    setcost();
    check_neighbours();
    struct cost x;
    x.coord[0] = nodecosts[costrep-1].coord[0];
    x.coord[1] = nodecosts[costrep-1].coord[1];
    x.order = nodecosts[costrep-1].order;
    path[pathrep] = x;
    pathrep++;


    traverse();
    setWindowSize(width, height);
    drawgrid();
    move();
}