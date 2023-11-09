// ------------------------------------------------ graphl.cpp -------------------------------------------------------
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
#include <string>
#include "nodedata.h"
#include "graphl.h"
#include <climits>
#include <iomanip>


// ------------------------------------GraphL------------------------------------------------------------
// Description: default constructor, initializes all the pointers in the graphNode array arrList, as well
// as the size
// ------------------------------------------------------------------------------------------------------
GraphL::GraphL()
{
    size = 0;
    for (int i = 1; i < MAX_NODES; i++){
        arrList[i].edgeHead = nullptr;
        arrList[i].data = nullptr;
        arrList[i].visited = false;
    }
}

// ------------------------------------~GraphL-----------------------------------------------------------
// Description: destructor, deletes all the nodes in arrList and frees all memory left over in GraphL
// ------------------------------------------------------------------------------------------------------
GraphL::~GraphL()
{
    for(int i = 0; i <= size; i++)
    {
        EdgeNode * current = arrList[i].edgeHead;
        delete arrList[i].data;
        while(current != nullptr)
        {
            EdgeNode* temp = current;
            current = current->nextEdge;
            delete temp;
        }
    }
}

// ------------------------------------~buildGraph-----------------------------------------------------------
// Description: builds the data in arrList from the inputed text file, setting up all linked lists in arrList
// ----------------------------------------------------------------------------------------------------------
void GraphL::buildGraph(ifstream &file)
{
    string s;

    file >> size;
    if(size == 0)
    {
        return;
    }

    getline(file, s);
    for (int i = 1; i <= size; i++)
    {
        getline(file, s);
        arrList[i].data = new NodeData(s);
    }

    int from, to;
    file >> from >> to;

    if (from == 0 && to == 0)
    {
        return;
    }

    while (true){
        if (from == 0 && to == 0)
        {
            break;
        }

        if (arrList[from].edgeHead == NULL)
        {
            EdgeNode *node = new EdgeNode;
            node->adjGraphNode = to;
            arrList[from].edgeHead = node;
            arrList[from].edgeHead->nextEdge = NULL;
        }
        else
        {
            EdgeNode *node = new EdgeNode;
            node->adjGraphNode = to;
            node->nextEdge = arrList[from].edgeHead;
            arrList[from].edgeHead = node;
        }     
        if (file.eof())
        {
            file.close();
            break;
        }
        
        file >> from >> to;
    }
}

// ------------------------------------displayGraph------------------------------------------------------
// Description: function displays the info of the graph printing each node in the node with its associated
// data and list of edges that originate from that node. 
// ------------------------------------------------------------------------------------------------------
void GraphL::displayGraph()
{
    cout << "Graph: " << endl;
    for(int from = 1; from <= size; from++)
    {
        cout << "Node" << from << "         " << *arrList[from].data << endl << endl;
        
        EdgeNode* current = arrList[from].edgeHead;

        while(current != nullptr){
            cout << setw(6) << "edge" << setw(3) << from << setw(3) << current->adjGraphNode << endl;
            current = current->nextEdge;
        }
        cout << endl;
    }
}

// ------------------------------------depthFirstSearch--------------------------------------------------
// Description: this functions performs DFS on the graph and displays the nodes in order of DFS until 
// all nodes visited. uses depthFirstSearchHelper to do so.
// ------------------------------------------------------------------------------------------------------
void GraphL::depthFirstSearch()
{
    cout << "Depth-first ordering:";

    for (int v = 1; v <= size; v++){
        if(!arrList[v].visited){
            depthFirstSearcherHelper(v);
        }
    }

    cout << endl << endl;
}

// ------------------------------------depthFirstSearchHelper--------------------------------------------
// Description: Recursive helper function to traverse the graph starting from node "v" and marks visted 
// nodes. Prints the node number, sets it as visited, then recursively goes through the adjacent nodes not
// yet visited. repeated until all nodes visited
// ------------------------------------------------------------------------------------------------------
void GraphL::depthFirstSearcherHelper(int v)
{
    cout << setw(3) << v;
    arrList[v].visited = true;
    auto current = arrList[v].edgeHead;

    
    while (current != nullptr){
        if (!arrList[current->adjGraphNode].visited){
            depthFirstSearcherHelper(current->adjGraphNode);
        }

        current = current->nextEdge;
    }
}
