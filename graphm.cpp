#include <iostream>
#include <fstream>
#include "graphm.h"

using namespace std;

GraphM::GraphM()
{
    size = 0;
    for(int i = 0; i < MAXNODES; i++)
    {
        for(int j = 0; j < MAXNODES; j++)
        {
            C[i][j] = 0;
            T[i][j].dist = INT_MAX;
            T[i][j].visited = false;
            T[i][j].path = 0;
        }
    }

}

GraphM::~GraphM()
{
}

void GraphM::buildGraph(ifstream &file)
{
}

void GraphM::insertEdge(int from, int to, int weight)
{
}

void GraphM::removeEdge(int from, int to)
{
}

void GraphM::findShortestPath()
{
}

void GraphM::displayAll()
{
}

void GraphM::display(int from, int to)
{
}
