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
    // for (int source = 1; source <= size; source++)
    // {
    //     for (int i = 1; i <= size; i++)
    //     {
    //         int vIndex = findSmallest(C[source], 1, size, T[source]);
    //         T[source][vIndex].visited = true;
    //         for (int j = i; j <= size; j++)
    //         {
    //             int w = j;
    //             if (!T[source][w].visited)
    //             {
    //                 T[source][w].dist = min(T[source][w].dist, T[source][vIndex].dist + C[vIndex][w]);
    //             }
    //         }
    //     }
    // }
    for (int source = 1; source <= size; source++)
    {
        for (int i = 1; i <= size; i++)
        {
            T[source][i].visited = false;
            T[source][i].dist = MAXNODES;
            T[source][i].path = 0;
        }

        T[source][source].dist = 0;

        for (int j = 1; j <= size; j++)
        {
            int minDist = MAXNODES;
            int v = -1;

            for (int w = 1; w <= size; w++)
            {
                if (!T[source][w].visited && T[source][w].dist < minDist)
                {
                    minDist = T[source][w].dist;
                    v = w;
                }
            }

            if (v == -1)
            {
                break;
            }

            T[source][v].visited = true;

            for (int w = 1; w <= size; w++)
            {
                if (!T[source][w].visited && C[v][w] && T[source][v].dist != MAXNODES && T[source][v].dist + C[v][w] < T[source][w].dist)
                {
                    T[source][w].dist = T[source][v].dist + C[v][w];
                    T[source][w].path = v;
                }
            }
        }
    }
}

void GraphM::displayAll()
{
    // cout << "Description" << setw(18) << "From node" << setw(12) << "To node" << setw(12) << "Dijkstra's" << setw(12) << "Path" << setw(12) << endl;
    // for (int i = 1; i <= size; i++)
    // {
    //     cout << data[i] << setw(18);
    //     for (int j = 1; j <= size; j++)
    //     {
    //         cout << i << setw(12) << j << setw(12) << endl;
    //     }
    // }
    cout << "Description" << setw(20) << "From node" << setw(10) << "To node" << setw(14) << "Dijkstra's" << setw(7) << "Path" << endl;

    for (int from = 1; from <= size; from++)
    {
        cout << data[from] << endl;

        for (int to = 1; to <= size; to++)
        {
            if (from != to)
            {
                cout << setw(27) << from;
                cout << setw(10) << to;

                if (T[from][to].dist == MAXNODES)
                {
                    cout << setw(12) << "----" << endl;
                }
                else
                {
                    cout << setw(12) << T[from][to].dist << setw(7);
                    cout << from << ' ';
                    findPath(from, to);
                    cout << to << endl;
                }
            }
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
    for (int i = 1; i <= size; i++)
    {
        if (arr[i] < hi && (otherArr[i].visited == false))
        {
            hi = arr[i];
            loIndex = i;
        }
    }

    return loIndex;
}

void GraphM::findPath(int from, int to)
{
    if (from == to){
        cout << from << ' ';
    }

    else if(T[from][to].path == 0){
        cout << "No path found";
    }
    else {
        findPath(from, T[from][to].path);
        cout << to << ' ';
    }
}