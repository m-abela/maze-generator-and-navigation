#include <stdio.h>
#include <stdlib.h>

struct cost{
    int order;
    int coord[2];
    int visited;
};

struct cost nodecosts[16];
int costrep = 1;

struct cost path[20];
int pathrep = 0;

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

