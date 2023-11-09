// ------------------------------------------------ graphl.h -------------------------------------------------------
//
// George Vu, Kylan Mlanao CSS343
// 10/24/2023
// 11/8/2023
// --------------------------------------------------------------------------------------------------------------------
// Purpose - to implement depth first search in a graph using an adjacency list
// --------------------------------------------------------------------------------------------------------------------
// This class is able to build it's list using an ifstream txtfile in buildGraph. It is also able to display the graph
// in a list order, as well perform depth first search on the graph.
// --------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include "nodedata.h"
#include <climits>
#include <iomanip>

using namespace std;

const static int MAX_NODES = 100;
class GraphL
{
public:

    // ------------------------------------GraphL------------------------------------------------------------
    // Description: default constructor, initializes all the pointers in the graphNode array arrList, as well
    // as the size
    // ------------------------------------------------------------------------------------------------------
    GraphL();
    
    // ------------------------------------~GraphL-----------------------------------------------------------
    // Description: destructor, deletes all the nodes in arrList and frees all memory left over in GraphL
    // ------------------------------------------------------------------------------------------------------   
    ~GraphL();   

    // ------------------------------------buildGraph------------------------------------------------------------
    // Description: builds the data in arrList from the inputed text file, setting up all linked lists in arrList
    // ----------------------------------------------------------------------------------------------------------
    void buildGraph(ifstream& file);

    // ------------------------------------displayGraph------------------------------------------------------
    // Description: function displays the info of the graph printing each node in the node with its associated
    // data and list of edges that originate from that node. 
    // ------------------------------------------------------------------------------------------------------
    void displayGraph();

    // ------------------------------------depthFirstSearch--------------------------------------------------
    // Description: this functions performs DFS on the graph and displays the nodes in order of DFS until 
    // all nodes visited. uses depthFirstSearchHelper to do so.
    // ------------------------------------------------------------------------------------------------------
    void depthFirstSearch();


private:
    int size;
    struct EdgeNode;
    struct GraphNode {
        EdgeNode * edgeHead;
        NodeData * data;
        bool visited;
    };

    struct EdgeNode {
        int adjGraphNode;
        EdgeNode* nextEdge;
    };

    GraphNode arrList[MAX_NODES];

    // ------------------------------------depthFirstSearchHelper--------------------------------------------
    // Description: Recursive helper function to traverse the graph starting from node "v" and marks visted 
    // nodes. Prints the node number, sets it as visited, then recursively goes through the adjacent nodes not
    // yet visited. repeated until all nodes visited
    // ------------------------------------------------------------------------------------------------------
    void depthFirstSearcherHelper(int v);
    
};