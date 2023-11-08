#include <iostream>
#include <fstream>
#include <string>
#include "nodedata.h"
#include "graphl.h"
#include <climits>
#include <iomanip>

GraphL::GraphL()
{
    size = 0;
    for (int i = 1; i < MAX_NODES; i++){
        arrList[i].edgeHead = nullptr;
        arrList[i].data = nullptr;
        arrList[i].visited = false;
    }
}

GraphL::~GraphL()
{
    
}

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
        // EdgeNode * toInsert = new EdgeNode;
        // EdgeNode * current;
        // toInsert->adjGraphNode = to;
        // toInsert->nextEdge = nullptr;

        // //damn bro that's wild
        // if((arrList[from].edgeHead == nullptr) || arrList[from].edgeHead->adjGraphNode >= toInsert->adjGraphNode)
        // {
        //     toInsert->nextEdge = arrList[from].edgeHead;
        //     arrList[from].edgeHead = toInsert;
        // }
        // else
        // {
        //     current = arrList[from].edgeHead;
        //     while(current->nextEdge != nullptr && current->nextEdge->adjGraphNode < toInsert->adjGraphNode)
        //     {
        //         current - current->nextEdge;
        //     }
        //     toInsert->nextEdge = current->nextEdge;
        //     current->nextEdge = toInsert;
        // }
        
        if (file.eof())
        {
            file.close();
            break;
        }
        
        file >> from >> to;
    }
}

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
    }
}

void GraphL::depthFirstSearch()
{
    cout << "Depth-first ordering:";

    for (int v = 1; v <= size; v++){
        if(!arrList[v].visited){
            depthFirstSearcherHelper(v);
        }
    }

    cout << endl;
}

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
