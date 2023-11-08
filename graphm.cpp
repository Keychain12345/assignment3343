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
            C[i][j] = 10000;
            T[i][j].dist = 10000;
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
    if (weight != 10000){
        C[from][to] = weight;
    }
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
        for (int i = 1; i <= MAXNODES; i++)
        {
            for(int j = 1; j <= MAXNODES; j++)
            {
                T[i][j].visited = false;
                T[i][j].dist = abs(10000);
                T[i][j].path = 0;
            }
        }

        // T[source][source].dist = 0;

        // for (int j = 1; j <= size; j++)
        // {
        //     int minDist = MAXNODES;
        //     int v = -1;

        //     for (int w = 1; w <= size; w++)
        //     {
        //         if (!T[source][w].visited && T[source][w].dist < minDist)
        //         {
        //             minDist = T[source][w].dist;
        //             v = w;
        //         }
        //     }

        //     if (v == -1)
        //     {
        //         break;
        //     }

        //     T[source][v].visited = true;

        //     for (int w = 1; w <= size; w++)
        //     {
        //         if (!T[source][w].visited && C[v][w] && T[source][v].dist != MAXNODES && T[source][v].dist + C[v][w] < T[source][w].dist)
        //         {
        //             T[source][w].dist = T[source][v].dist + C[v][w];
        //             T[source][w].path = v;
        //         }
        //     }
        // }
        
        T[source][source].dist = 0;
        for(int i = 1; i <= size; i++)
        {
            cout << "current source " << source << endl;
            int v = findSmallest(C[source], 1, size, T[source]); 
            T[source][v].visited = true;
            cout << "distance from " << source << " to " << v << ": " << T[source][v].dist << endl;

            for(int w = 1; w <= size; w++)
            {
                if(C[v][w] != abs(10000))
                {
                    if(T[source][w].visited == false)
                    {
                        T[source][w].dist = min(T[source][w].dist, T[source][v].dist + C[v][w]);

                        if(T[source][v].dist + C[v][w] < T[source][w].dist)
                        {
                            T[source][w].dist = T[source][v].dist + C[v][w];
                            T[source][w].path = v;
                        }
                        else
                        {
                            T[source][w].path = source;
                        }
                    }
                }
            }

        }
    }
}

void GraphM::displayAll()
{
    cout << "Cost Matrix" << endl;
    for (int from = 1; from <= size; from++)
    {
        for (int to = 1; to <= size; to++)
        {
            if (C[from][to] == 10000)
            {
                cout << "INF\t";
            }
            else
            {
                cout << C[from][to] << "\t";
            }
        }
        cout << endl;
    }
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

                if (T[from][to].dist != 10000)
                {
                    cout << setw(12) << T[from][to].dist << setw(7);
                    cout << from << ' ';
                    findPath(from, to);
                    cout << to << endl;
                }
                else
                {
                    cout << setw(12) << "----" << endl;
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
    hi = 10000;
    int loIndex = 1;
    cout << endl << "current call" << endl;
    for (int i = 1; i <= size; i++)
    {
        cout << otherArr[i].dist << " ";
        if ((otherArr[i].dist < hi) && (otherArr[i].visited == false))
        {
            hi = otherArr[i].dist;
            loIndex = i;
        }
    }

    cout << endl << "final: " << otherArr[loIndex].dist << " node index: " << loIndex << endl << endl;

    return loIndex;
}

void GraphM::findPath(int from, int to)
{
    if (from == to){
        cout << from << ' ';
    }

    else if(T[from][to].path == 0){
        cout << "No path found" << to << ' ';
    }
    else {
        findPath(from, T[from][to].path);
        cout << to << ' ';
    }
}