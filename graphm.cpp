#include <iostream>
#include <fstream>
#include <string>
#include <climits>
#include <iomanip>
#include "graphm.h"

using namespace std;

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
           int vIndex = findSmallest(C[source], 1, size, T[source]);
           T[source][vIndex].visited = true;
           for(int j = i; j <= size; j++)
           {
                int w = j;
                if(!T[source][w].visited)
                {
                    T[source][w].dist = min(T[source][w].dist, T[source][vIndex].dist + C[vIndex][w]);
                }
           }
        }
    }
}

void GraphM::displayAll()
{
    cout << "Description" << setw(18) << "From node" << setw(12) << "To node" << setw(12) << "Dijkstra's" << setw(12) << "Path" << setw(12) << endl;
    for(int i = 1; i <= size; i++)
    {
        cout << data[i] << setw(18);
        for(int j = 1; j<= size; j++)
        {
            cout << i << setw(12) << j << setw(12) << endl;
        }
    }
}

void GraphM::display(int from, int to)
{
}

int GraphM::findSmallest(int arr[], int lo, int hi, TableType otherArr[])
{
    hi = INT_MAX;
    int loIndex = 1;
    for(int i = 1; i <= size; i++)
    {
        if(arr[i] < hi && (otherArr[i].visited == false))
        {
            hi = arr[i];
            loIndex = i;
        }
        
    }

    return loIndex;
}