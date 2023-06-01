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


//creating the maze
struct node create_node();
struct poss_path makeposs(int strtcoord[2], int nextcoord[2], int weight);
void create_maze();
void get_available();
void expand();


//findpath