// ------------------------------------------------ graphm.h -------------------------------------------------------
//
// George Vu, Kylan Mlanao CSS343
// 10/24/2023
// 11/8/2023
// --------------------------------------------------------------------------------------------------------------------
// Purpose - to implement Djikstras shortest path algorithm on a graph using an adjacency matrix
// --------------------------------------------------------------------------------------------------------------------
// This class can use find shortest path to find the shortest paths from each node to another node, it also can display
// it all using the display all function or just one specific path using display. It is able to build the graph from an 
// ifstream txt file.
// --------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include "nodedata.h"
#include <climits>

using namespace std;

const static int MAXNODES = 100;

class GraphM
{
public:
    
    // ------------------------------------GraphM------------------------------------------------------------
    // Description: default constructor, initializes all data of T and C arrays aswell as setting size to 0.
    // ------------------------------------------------------------------------------------------------------
    GraphM();

    // ------------------------------------buildGraph--------------------------------------------------------
    // Description: buildGraph function reads data from the provided input file and constructs a weighted 
    // graph. It reads the size of the graph, creates nodes with associated data, and adds weighted edges 
    // between nodes according to the data in the input file given uses the insertEdge function to do so.
    // ------------------------------------------------------------------------------------------------------
    void buildGraph(ifstream& file);
    
    // ------------------------------------insertEdge--------------------------------------------------------
    // Description: Inserts an edge between two nodes in a weighted graph. Sets weight of edge node "from" to 
    // node "to" to the specified "weight" value.
    // ------------------------------------------------------------------------------------------------------
    void insertEdge(int from, int to, int weight);

    // ------------------------------------removeEdge--------------------------------------------------------
    // Description: function removes and edge between two nodes in weighted graph by setting the edge's 
    // weight to a large value. It alsos resets the entire graph by reinitializing the data.
    // ------------------------------------------------------------------------------------------------------
    void removeEdge(int from, int to);

    // ------------------------------------findShortestPath--------------------------------------------------
    // Description: This function calculates the shortest paths between nodes in a weighted graph using 
    // Dijkstra's algorithm. It iterates over each node and finds the shortest path from the node to all other 
    // nodes in the graph while maintaining the path information in the T array.
    // ------------------------------------------------------------------------------------------------------
    void findShortestPath();

    // ------------------------------------displayAll--------------------------------------------------------
    // Description: this function displays all the paths from each node to each other node, that were found
    // in findShortestPath, as well as their distance as well
    // ------------------------------------------------------------------------------------------------------
    void displayAll();

    // ------------------------------------display-----------------------------------------------------------
    // Description: this function displays the shortest path and its distance while also printing out the 
    // node names between two nodes "from" and "to" in the weighted graph.
    // ------------------------------------------------------------------------------------------------------
    void display(int from, int to);

    

private: 
    struct TableType
    {
        bool visited;
        int dist;
        int path;
    };


    NodeData data [MAXNODES];
    int C[MAXNODES][MAXNODES]; //adjacency matrix
    int size;
    TableType T[MAXNODES] [MAXNODES];

    // ------------------------------------findSmallest---------------------------------------------------------
    // Description: this is a helper function to find the v index for the node from the TableType T. It compares
    /// to find the closest node to which ever node is the current "from" node in findShortestPath
    // ---------------------------------------------------------------------------------------------------------
    int findSmallest(int arr[], int lo, int hi, TableType otherArr[]);

    // ------------------------------------findPath----------------------------------------------------------
    // Description: This is a recursive function the finds and prints the path from node "from" to node "to".
    // It checks if a path exist, and if so, it will recursively trace back the path using the T matrix to 
    // to print each node in the path.
    // ------------------------------------------------------------------------------------------------------
    void findPath(int from, int to);

    // ------------------------------------printNodes--------------------------------------------------------
    // Description: recursive function that prints the data(names) associated with the nodes along the path 
    //from node "from" to node "to" in the graph.
    // ------------------------------------------------------------------------------------------------------
    void printNodes(int from, int to);
};