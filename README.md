# Compiling and runnning

In terminal, navigate to this project root

$ mkdir build

$ cd build

$ cmake..

$ make

Now to run
$ ./graph

If you want to run with a file use '<'. If you wanted to use example.txt that comes with this project, execute:

$ ./graph < ../example.txt

# Documentation

## Edge

### Bidirect graph

Use the following functions

setBidirect()

setUnidirect()

### Edge definition

Edge from vertice a to b. Creates vertices a and b if needed. Ex:

a->b 

Alternative

a b 

Obs:

2->3 #means add edge from vertice 2 to vertice 3


Edge from vertice a to b with weight (c)

obs: c needs to be a positive number. The interpreter considers it to be a double value

Ex:

a->b 2.3

b->a 4

Alternative:

a b 2.3

b a 4

Obs:

2->3 4 #means add edge from vertice 2 to vertice 3 with weight 4

# Functions

isConnected(a, b) #runs a DFS to check if a and b are connected

dist(a, b) #runs a Dijikstra and prints the minimum distance between a and b, -1 if not connected

numEdges()

numVerts()

print()

adjList()

adjList(v) #adj List only for vertice v

degree(v)

mst() #runs a prim in the graph and prints the cost of a mst
