import random
maze = []

available = []
walls = []
current = [0,0]
done = 1

class node:
    def __init__(self):
        self.visited = False
        self.up = random.randrange(1,10)
        self.right = random.randrange(1,10)
        self.down = random.randrange(1,10)
        self.left = random.randrange(1,10)

class info:
    def __init__(self, coord, direction, weight, goto):
        self.coordinates = coord
        self.direction = direction
        self.weight = weight
        self.goto = goto

    def get_weight(self):
        return self.weight

    def get_coord(self):
        return self.coordinates

class wallyes:
    def __init__(self, coord, nextcoord):
        self.coord = coord
        self.nextcoord = nextcoord
    def get_coord(self):
        return self.coord

    def get_nexrcoord(self):
        return self.nextcoord

#get available
def get_available():
    #print(current)
    up = maze[current[0]][current[1]].up
    down = maze[current[0]][current[1]].down
    left = maze[current[0]][current[1]].left
    right = maze[current[0]][current[1]].right
    weight = [up,down,left,right]
    name = ["up", "down", "left", "right"]
    direc = [[current[0], current[1]+1], [current[0], current[1]-1], [current[0]-1, current[1]], [current[0]+1, current[1]]]

    for i in range(4):
        for j in range(len(direc[i])):
            if (direc[j][0] > 3) or (direc[j][1] > 3):
                break
        if (direc[j][0] > 3) or (direc[j][1] > 3):
            continue


        if -1 in direc[i]:
            continue

        if ((weight[i] != 0)) and (maze[direc[i][0]][direc[i][1]].visited == False):
            #print(direc[i], weight[i])
            available.append(info(current, name[i], weight[i], [direc[i][0],direc[i][1]]))


def expand():
    global current
    global done
    done += 1
    get_available()
    lowest = info([1,1], -10, 101, [100,100])
    for i in range(len(available)):
        if (available[i].get_weight() < lowest.get_weight()):
            lowest = available[i]
    available.remove(lowest)
    walls.append(wallyes(lowest.coordinates, lowest.goto))
    current = lowest.goto
    maze[lowest.goto[0]][lowest.goto[1]].visited = True
    printmaze()
    print()

def printmaze():
    for i in range(4):
        line = ""
        for j in range(4):
            if maze[i][j].visited == False:
                line += "W"
            if maze[i][j].visited == True:
                line += "V"
        print(line)


cost2 = [[0,[0,0],False]]
pp = [[0,0]]

def check_neighbours(num):
    #print(len(cost2))
    for t in range(len(cost2)):
        coord = cost2[t][1]
        cost = cost2[t][0]
        options = ([coord[0] + 1, coord[1]], [coord[0] - 1, coord[1]], [coord[0], coord[1] + 1], [coord[0], coord[1] - 1])
        for k in range(4):
            for j in range(len(walls)):
                #print((walls[j]).coord, coord, walls[j].nextcoord, options[k], cost)

                if options[k] in pp:
                    continue
                if (((walls[j].coord == coord) and (walls[j].nextcoord == options[k])) or ((walls[j].coord == options[k]) and (walls[j].nextcoord == coord))):
                    num -=1
                    cost2.append([cost + 1, options[k], False])
                    pp.append(options[k])
                    #print("YEET")

            #print()
        cost2[t][2] = True

path = []
def traverse(coord):
    print(path)
    cost = 0
    if path[-1][0] < 1:
        print("yeep")
        return [0,0]
    for i in range(len(cost2)):
        if cost2[i][1] == coord:
            cost = cost2[i][0]
            print(cost2[i][0])
            break

    for i in range(len(cost2)):
        for j in range(len(walls)):
            if (cost2[i][0] == (cost-1)) and (((cost2[i][1] == walls[j].nextcoord) and (coord == walls[j].coord)) or ((cost2[i][1] == walls[j].coord) and (coord == walls[j].nextcoord))):
                path.append(cost2[i][1])
                return traverse(cost2[i][1])





if __name__ == '__main__':
    for i in range(4):
        maze.append([node(), node(), node(), node()])
    # make unreachable
    maze[0][0].visited = True
    for i in range(4):
        maze[0][i].up = 0
        maze[i][0].left = 0
        maze[3][i].down = 0
        maze[i][3].right = 0

    while current[0] < 3:
        expand()
    path.append(current)
    for i in range(len(walls)):
        print(walls[i].coord, walls[i].nextcoord)

    for i in range(20):
        check_neighbours(done)
    traverse(current)
