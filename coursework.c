#include "graphics.h"
#include "stdio.h"
#include "string.h"
#include "stdbool.h"
void setWindowSize(int,int);
const int waitTime = 100;
const int cellSize = 50;
const int moveDistance = 8;
const int robotCoords[4][3][2] = {{{25, 0}, {50, 50}, {0, 50}},
                                  {{0, 0}, {50, 25}, {0, 50}},
                                  {{0, 0}, {50, 0}, {25, 50}},
                                  {{0, 25}, {50, 0}, {50, 50}}};
int x_co[] = {0,50, 0};
int y_co[] = {50, 75, 100};
int dir =2;


int draw_maze(int maze[11][11])
{
    background(); // Must draw on the background layer.
    int row=0,col=0,x_co=0,y_co=0;
    int i,j;
    for (row=0;row<11;row++)
    {
        for (col=0;col<11;col++)
        {
            if (maze[col][row] == 1)
            {
                //drawRect(x_co,y_co,50,50);
                setColour(black);
                fillRect(x_co,y_co,50,50);
            }
            else if (maze[col][row] == 0)
            {
                drawRect(x_co,y_co,50,50);
            }
            else
            {
                setColour(gray);
                fillRect(x_co,y_co,50,50);
                
            }
            x_co += 50;
        }
        y_co+=50;
        x_co =0;
    }
}
void update()
{
  // Clear the existing content, otherwise squares will just be added
  // and to what is already there.
  clear();
  clear();
  fillPolygon(3, x_co, y_co);
  sleep(waitTime);
  }
void forward()
{
    foreground();
    setColour(blue);
    bool exit=false;
    int i=0;
    if (dir==1)
    {
        for (i=0;i<3;i++)
        {
            y_co[i] = y_co[i]-50;

        }
    }
    else if (dir==2)
    {
        for (i=0;i<3;i++)
        {
            x_co[i]+=50;

        }
    }
    else if (dir==3)
    {
        for (i=0;i<3;i++)
        {
            y_co[i] +=50;

        }
    }
    else
    {
        for (i=0;i<3;i++)
        {
            x_co[i]=x_co[i] -50;

        }
    }

   
    update();
//    clear();
//    fillPolygon(3, x_co, y_co);
    
}
void rotate_right()
{
    foreground();
    setColour(blue);
    if (dir==4)
    {
        dir ==1;
    }
    else
    {
        dir++;
    }
    int i=1;
    int tempx =x_co[0];
    int tempy =y_co[0];
    x_co[0] = tempx+robotCoords[dir][0][0];
    y_co[0] = tempy+robotCoords[dir][0][1];
    x_co[1] = tempx+robotCoords[dir][1][0];
    y_co[1] = tempy+robotCoords[dir][1][1];
    x_co[2] = tempx+robotCoords[dir][2][0];
    y_co[2] = tempy+robotCoords[dir][2][1]; 
    update();

}
void rotate_left()
{
    foreground();
    setColour(blue);
    int tempx =x_co[0];
    int tempy =y_co[0];
    x_co[0] =tempx+robotCoords[dir][0][0];
    y_co[0] = tempy+robotCoords[dir][0][1];
    x_co[1] = tempx +robotCoords[dir][1][0];
    y_co[1] = tempy+robotCoords[dir][1][1];
    x_co[2] = tempx+robotCoords[dir][2][0];
    y_co[2] = tempy+robotCoords[dir][2][1];
    
    update();
}
int followright(int maze[11][11])
{
    int i=0, x_pos = x_co[0] / 50, y_pos = y_co[0] / 50;
    
    
    forward(); 
    rotate_right(x_pos,y_pos,x_co,y_co); 
    x_pos = x_co[0] / 50;
    y_pos = y_co[0]/50; 
    forward();
    forward();
    forward();
    forward();
   
    
}

// Control the animation step-by-step
void move(int maze[11][11])
{
  // The animated shape is on the foreground (top) layer, which must be
  // selected.
  foreground();
  setColour(blue);
  int i=0,solve=0;
  int x_co[] = {0,50, 0};
  int y_co[] = {50, 75, 100};
  bool exit =false;

  update(x_co,y_co);
  sleep(waitTime);
//  while (solve==0)
//  {
//    solve = followright(maze);
//  }
  followright(maze);

}
    
int main(void)
{
    setWindowSize(700,700);
    FILE *maze_file; // declaration of file pointer
    int maze[11][11],x,y;
    int pos_x,pos_y;
    maze_file = fopen("maze.txt","r");// opening of file
    for (y=0;y<11;y++)
    {
        for(x=0;x<11;x++)
        {
            fscanf(maze_file,"%i",&maze[x][y]);
            printf("%d",maze[x][y]);
        }
        printf("\n");
    }
   
    fclose(maze_file); // closing file
    draw_maze(maze);

    move(maze);
    return 0;	
}