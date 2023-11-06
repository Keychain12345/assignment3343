#include <iostream>
#include <fstream>
#include <string>
#include <climits>
#include "graphm.h"

using namespace std;

GraphM::GraphM()
{
    size = 0;
    for (int i = 0; i < MAXNODES; i++)
    {
        for (int j = 0; j < MAXNODES; j++)
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

void GraphM::insertEdge(int from, int to, int weight)
{
    C[from][to] = weight;
}

void GraphM::removeEdge(int from, int to)
{
    
}

void GraphM::findShortestPath()
{
    for(int source = 1; source <= size; source++)
    {
        T[source][source].dist = 0;
        
        for(int i = 1; i <= size; i++)
        {
            if(!T[source][i].visited)
            {
                T[source][i].visited = true;
            }
            
            
        }
    }
}

void GraphM::displayAll()
{
}

void GraphM::display(int from, int to)
{
}
