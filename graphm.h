#include <iostream>
#include <fstream>
#include "nodedata.h"
#include <climits>

using namespace std;

const static int MAXNODES = 100;

class GraphM
{
public:

    GraphM();

    ~GraphM();

    void buildGraph(ifstream& file);
    
    void insertEdge(int from, int to, int weight);

    void removeEdge(int from, int to);

    void findShortestPath();

    void displayAll();

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

    int findSmallest(int arr[], int lo, int hi, TableType otherArr[]);
    void findPath(int from, int to);
    void printNodes(int from, int to);
};