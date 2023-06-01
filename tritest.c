#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>

int x,y = 0;
int x_co[3] = {60, 110, 160};
int y_co[3]= {100, 200, 100};
int rotate[3][4][2] = {{{-100,0}, {0,100}, {100,0}, {0,-100}}, {{50,50}, {50,-50}, {-50,-50}, {-50,50}}, {{0,-100}, {-100,0}, {0,100}, {100,0}}};
int forward_move[4][2] = {{0,120}, {120,0}, {0,-120}, {-120,0}};
int direction = 0; // down, right, up, left



void left(){
    
    if (direction++ > 2){
        direction = 0;
    }
    printf("%d\n", direction);
    for (int i = 0; i < 3; i++){
        x_co[i] += rotate[i][direction][0];
        y_co[i] += rotate[i][direction][1];
    }
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
}


void forward(){
    for(int i =0; i<3; i++){
        x_co[i] += forward_move[direction][0];
        y_co[i] += forward_move[direction][1];

    }

}

int main(void)
{
    setWindowSize(600, 600);
    foreground();
    setColour(black);
    fillRect(60,100,100,100);
    setColour(blue);
    fillPolygon(3, x_co, y_co);
    for(int i =0; i<20; i++){
        sleep(2000);
right();
forward();
        clear();
        setColour(black);
        fillRect(60,100,100,100);
        setColour(blue);
        fillPolygon(3, x_co, y_co);   
    }
   
 
    
}
