// ------------------------------------------------ graphm.cpp -------------------------------------------------------
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
#include <string>
#include <climits>
#include <iomanip>
#include "graphm.h"

using namespace std;

// ------------------------------------GraphM------------------------------------------------------------
// Description: default constructor, initializes all data of T and C arrays aswell as setting size to 0.
// ------------------------------------------------------------------------------------------------------
GraphM::GraphM()
{
    size = 0;
    for (int i = 0; i < MAXNODES; i++)
    {
        for (int j = 0; j < MAXNODES; j++)
        {
            C[i][j] = INT_MAX;
            T[i][j].dist = INT_MAX;
            T[i][j].visited = false;
            T[i][j].path = 0;
        }
    }
}

// ------------------------------------buildGraph--------------------------------------------------------
// Description: buildGraph function reads data from the provided input file and constructs a weighted 
// graph. It reads the size of the graph, creates nodes with associated data, and adds weighted edges 
// between nodes according to the data in the input file given uses the insertEdge function to do so.
// ------------------------------------------------------------------------------------------------------
void GraphM::buildGraph(ifstream &file)
{
    string s;

    file >> size;
    if (size == 0)
    {
        return;
    }

    getline(file, s);
    for (int i = 1; i <= size; i++)
    {
        getline(file, s);
        data[i] = NodeData(s);
    }

    int from, to, weight;
    file >> from >> to >> weight;
    if (from == 0 && to == 0 && weight == 0)
    {
        return;
    }

    while (true)
    {
        if (from == 0 && to == 0 && weight == 0)
        {
            break;
        }

        insertEdge(from, to, weight);

        if (file.eof())
        {
            file.close();
            break;
        }
        file >> from >> to >> weight;
    }
}

// ------------------------------------insertEdge--------------------------------------------------------
// Description: Inserts an edge between two nodes in a weighted graph. Sets weight of edge node "from" to 
// node "to" to the specified "weight" value.
// ------------------------------------------------------------------------------------------------------
void GraphM::insertEdge(int from, int to, int weight)
{
    C[from][to] = weight;
}

// ------------------------------------removeEdge--------------------------------------------------------
// Description: function removes and edge between two nodes in weighted graph by setting the edge's 
// weight to a large value. It alsos resets the entire graph by reinitializing the data.
// ------------------------------------------------------------------------------------------------------
void GraphM::removeEdge(int from, int to)
{
    C[from][to] = INT_MAX;
    size = 0;
    for (int i = 0; i < MAXNODES; i++)
    {
        for (int j = 0; j < MAXNODES; j++)
        {
            T[i][j].dist = INT_MAX;
            T[i][j].visited = false;
            T[i][j].path = 0;
        }
    }
}

// ------------------------------------findShortestPath--------------------------------------------------
// Description: This function calculates the shortest paths between nodes in a weighted graph using 
// Dijkstra's algorithm. It iterates over each node and finds the shortest path from the node to all other 
// nodes in the graph while maintaining the path information in the T array.
// ------------------------------------------------------------------------------------------------------
void GraphM::findShortestPath()
{

    for (int source = 1; source <= size; source++)
    {
        T[source][source].dist = 0;
        for(int i = 1; i <= size; i++)
        {
        
            int v = findSmallest(C[source], 1, size, T[source]); 
            T[source][v].visited = true;

            for(int w = 1; w <= size; w++)
            {
                if((C[v][w] != INT_MAX))
                {
                    if(T[source][w].visited == false)
                    {
                        T[source][w].dist = min(T[source][w].dist, T[source][v].dist + C[v][w]);


                        if((T[source][v].dist + C[v][w]) == T[source][w].dist)
                        {
                            T[source][w].path = v;
                        }
        
                    }
                }
            }

        }
    }
}

// ------------------------------------displayAll--------------------------------------------------------
// Description: this function displays all the paths from each node to each other node, that were found
// in findShortestPath, as well as their distance as well
// ------------------------------------------------------------------------------------------------------
void GraphM::displayAll()
{
    cout << "Description" << setw(20) << "From node" << setw(10) << "To node" << setw(14) << "Dijkstra's" << setw(9) << "Path" << endl;

    for (int from = 1; from <= size; from++)
    {
        cout << data[from] << endl;

        for (int to = 1; to <= size; to++)
        {
            if (from != to)
            {
                cout << setw(27) << from;
                cout << setw(10) << to;

                if (T[from][to].dist != INT_MAX)
                {
                    cout << setw(11) << T[from][to].dist << setw(13);
                    findPath(from, to);
                    cout << endl;
                }
                else
                {
                    cout << setw(11) << "----" << endl;
                }
            }
        }
    }
}

// ------------------------------------display-----------------------------------------------------------
// Description: this function displays the shortest path and its distance while also printing out the 
// node names between two nodes "from" and "to" in the weighted graph.
// ------------------------------------------------------------------------------------------------------
void GraphM::display(int from, int to)
{
    cout << endl;
    if(T[from][to].dist != INT_MAX)
    {
        cout << setw(4) << from << setw(9) << to << setw(10) << T[from][to].dist << setw(12);
    }
    else
    {
        cout << setw(4) << from << setw(9) << to << setw(10) << "----";
        cout << endl;
    }
    
    if (T[from][to].dist != INT_MAX){
        findPath(from, to);
        cout << endl;
        printNodes(from, to);
    }
}

// ------------------------------------findSmallest---------------------------------------------------------
// Description: this is a helper function to find the v index for the node from the TableType T. It compares
/// to find the closest node to which ever node is the current "from" node in findShortestPath
// ---------------------------------------------------------------------------------------------------------
int GraphM::findSmallest(int arr[], int lo, int hi, TableType otherArr[])
{
    hi = INT_MAX;
    int loIndex = 0;
    for (int i = 1; i <= size; i++)
    {
        if ((otherArr[i].dist < hi) && (otherArr[i].visited == false))
        {
            hi = otherArr[i].dist;
            loIndex = i;
        }
    }

    return loIndex;
}

// ------------------------------------findPath----------------------------------------------------------
// Description: This is a recursive function the finds and prints the path from node "from" to node "to".
// It checks if a path exist, and if so, it will recursively trace back the path using the T matrix to 
// to print each node in the path.
// ------------------------------------------------------------------------------------------------------
void GraphM::findPath(int from, int to)
{
    if (from == to){
        cout << from;
    }
    else if(T[from][to].path == 0){
        cout << "No path found";
    }
    else {
        findPath(from, T[from][to].path);
        cout << ' ' << to;
    }
}

// ------------------------------------printNodes--------------------------------------------------------
// Description: recursive function that prints the data(names) associated with the nodes along the path 
//from node "from" to node "to" in the graph.
// ------------------------------------------------------------------------------------------------------
void GraphM::printNodes(int from, int to)
{
    if(from == to)
    {
        cout << data[from] << endl << endl;
    }
    else if(T[from][to].path == 0)
    {
        cout << "No path found";
    }
    else
    {
        printNodes(from, T[from][to].path);
        cout << data[to] << endl << endl;
    }
}