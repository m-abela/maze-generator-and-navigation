Description of program:
Program generates maze using prims algorithm by assigning random weights to each path between the nodes.

It then uses Dijkstra to calculate costs for each node and traverses the path calculated

This data is then fed to the robot which is animated to pass through the maze

commands to run program:
gcc -o maze mazecw.c graphics.c   
./maze | java -jar drawapp-2.0.jar

