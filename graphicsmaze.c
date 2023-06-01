#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>


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
    fillRect(60, 100, 60, 60);
    
    for(int i = pathrep-1; i >-1; i--){
        sleep(500);
        int x = (60 + (120*path[i].coord[1]));
        int y = 100 + (120*path[i].coord[0]);
        clear();
        fillRect(x, y, 60, 60);
    }

}
