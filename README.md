# Renyi-Erdos-RandomGraphs


#########################################################################
* Prior to running the program please change the build configuration to Release and 
not Debug, in order to speed up the execution of the program. *
#########################################################################

Program Goal:
This program will generate 3 CSV files containing the probability and the probability of each feature to occur based on the input probability. 

Running Time:
Approximately ~15 min with Release configured.
Approximately ~30 min with Debug configured.

Attached files:
Main.cpp -- consist of utility functions, Ex functions, and the main driving program function (main)
CreateGraph.h -- Declarations of the class Graph functions.
CreateGraph.cpp -- Functions of the class Graph.



Utility functions:

firstTest, secondTest, thirdTest - These functions handle all of the tests of each based on the assignment feature. 

writeResultToCsv - Writing each probability and each result the the CSV file.

calcThreshold2 , calcThreshold1_3 - Calculate both thresholds for features 1,2,3.

random_prob -- returns true if the probability is bigger than the randomly generated number, Using the following methods:
	*Knuth-B generator:
An engine adaptor that returns shuffled sequences generated with the simple pseudo-random number generator engine .
*uniform_real_distribution:
Produces random floating-point values i, uniformly distributed on the interval [a, b), that is, distributed according to the probability density function:






Ex. functions:

build_random_graph - Adding each edge base on the probability input and the random generator.

connectivity - checks if the graph is connected, returns 1 if Graph is connected else return 0. This function uses the BFS algorithm by checking if one of the vertices is infinity (-1)

diameter - Finding the diameter of the graph using BFS algorithm by getting a list of the distances in of each vertex.
2 BFS runnings are required in order to find the diameter. 

Is_isolated - Checking if a vertex is isolated using the function of the class Graph we built.

Graph Class:

3 constructors:
Graph()
Graph(int v) - Getting num of vertex
Graph(const Graph& other) - Copy constructor
The Graph edges are implemented via Set and the Set is handling all the connections between each vertex in the Graph. 


addEdge - This is the function that handles the connection between each vertex.
Sour = source vertex.
Dest = Destination vertex. 

BFS - BFS algorithm taking input of StartVertex

getV- get the number of vertices

Print_graph - printing each connection -- FOR testing purposes 
