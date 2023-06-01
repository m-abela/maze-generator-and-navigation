#include <stdio.h>
#include <stdlib.h>
#include "functions.h"


//declare structures to store appropriate information
struct node maze[4][4];
struct poss_path available[20];
int pathit = 0;
struct wall_exist walls[100];
int wallit = 0;

//assigns random weights to paths between nodes
struct node create_node(){
    struct node x;
    x.up = rand() % 20;
    x.left = rand() % 20;
    x.right = rand() % 20;
    x.down = rand() % 20;
    x.visited = 0;
    return x;
}

//declare global variables for maze, path and walls, and iterators
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

int current[2] = {0,0}; //current node being currently used


//returns structure child for possible path
struct poss_path makeposs(int strtcoord[2], int nextcoord[2], int weight){
    struct poss_path x;
    for (int i = 0; i < 2; i++){
        x.start_coord[i] = strtcoord[i];
        x.next_coord[i] = nextcoord[i];
    }
    x.weight = weight;
    return x;
}

//initiates blank grid of nodes for maze
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

//gets possible paths that could be taken from particular node
void get_available(){
    struct node temp = maze[current[0]][current[1]];
    int weight[] = {temp.up, temp.down, temp.left, temp.right};
    int posspath[4][2] = {{current[0],(current[1]+1)}, {current[0], (current[1]-1)}, {(current[0]-1), current[1]}, {(current[0]+1), current[1]}};
    for (int i = 0; i < 4; i ++){
        if((posspath[i][0] < 0) || (posspath[i][1] < 0) || (posspath[i][1] > 3) || (posspath[i][0] > 3)){
            continue;
        }
        if ((weight[i] != 0) && (maze[posspath[i][0]][posspath[i][1]].visited == 0)){
            available[pathit] = makeposs(current, posspath[i], weight[i]);
        }
    }
}

//chooses node with lowest weight from array of available nodes
void expand(){
    for(int z = 0; z<10; z++){
        get_available();
        struct poss_path lowest;
        int lowest_weight = 201;

        for(int i = 0; i< pathit+1; i++){
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


