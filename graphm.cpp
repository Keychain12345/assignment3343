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