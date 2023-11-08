#include <iostream>
#include <fstream>
#include <string>
#include "nodedata.h"
#include "graphl.h"
#include <climits>

GraphL::GraphL()
{
    size = 0;
    for (int i = 1; i < MAX_NODES; i++){
        arrList[i].edgeHead->nextEdge = nullptr;
        arrList[i].edgeHead->adjGraphNode = 0;
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
    
}

void GraphL::displayGraph()
{

}

void GraphL::depthFirstSearch()
{

}
