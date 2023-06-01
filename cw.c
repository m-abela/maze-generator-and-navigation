#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "genmaze.c"
/*
struct wall_exist{
    int start_coord[2];
    int next_coord[2];
};

struct wall_exist walls[100];
int wallit = 4;

void wallvalues(){
    struct wall_exist q;
    q.start_coord[0] = 0;
    q.start_coord[1] = 0;

    q.next_coord[0] = 1;
    q.next_coord[1] = 0;

    walls[0] = q;

    q.start_coord[0] = 1;
    q.start_coord[1] = 0;

    q.next_coord[0] = 2;
    q.next_coord[1] = 0;

    walls[1] = q;

    q.start_coord[0] = 2;
    q.start_coord[1] = 0;

    q.next_coord[0] = 3;
    q.next_coord[1] = 0;
    walls[2] = q;
}

*/

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
    for (int z = 0; z<5; z++){

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
    while (path[pathrep-1].coord[0] > 0){
        int cost = path[pathrep-1].order;
        int coord[2] = {path[pathrep-1].coord[0], path[pathrep-1].coord[1]};
        //printf("%d %d %d\n", cost, coord[0], coord[1]);
        for (int i = 0; i<costrep; i++){
            for (int j = 0; j<wallit; j++){
                //printf("%d %d %d\n", nodecosts[i].order, nodecosts[i].coord[0], nodecosts[i].coord[1]);
                if(nodecosts[i].order == (cost-1))
                {
                    printf("[%d %d] ", nodecosts[i].coord[0], nodecosts[i].coord[1]);
                    path[pathrep] = nodecosts[i];
                    pathrep++;
                    break;
                }
            }
        }
    }
    
}

int main () {
    create_maze();
    set_available();
    expand();

    wallvalues();
    setcost();
    check_neighbours();
    struct cost x;
    x.coord[0] = 3;
    x.coord[1] = 0;
    x.order = 3;
    path[pathrep] = x;
    pathrep++;
    traverse();

    for (int i = pathrep;  i > -1; i--){
        printf("%d %d %d\n", path[i].coord[0], path[i].coord[1], path[i].order);
    }
} 