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
    while (true)
    {
        if(file.eof()){
            cout << "end of file" << endl;
            break;
        }
        file >> size;
        if (size == 0){
            break;
        }
        cout << size;
        for (int i = 1; i <= size + 1; i++)
        {
            getline(file, s);
            cout << s << endl;
            names[i] = s;
        }

        cout << "out of first for loop" << endl;

        int from, to, weight;
        file >> from >> to >> weight;
        if (from == 0 && to == 0 && weight == 0){
            break;
        }
        cout << from << " " << to << " " << weight << endl;

        while (true)
        {
            if (from == 0 && to == 0 && weight == 0)
            {
                cout << "I broke" << endl;
                break;
            }

            insertEdge(from, to, weight);

            if (file.eof())
            {
                break;
            }
            file >> from >> to >> weight;
            cout << from << " " << to << " " << weight << endl;
        }
    }
    // WHERE DID YOU GO?
    // for(;;)
    // {
    //     file >> s;

    //     if(static_cast <char> (s[0]) == '0')
    //     {
    //         cout << "I am called" << endl;
    //         break;
    //     }

    //     if(file.eof())
    //     {
    //         break;
    //     }
    //     cout << s << endl;
    //     tempStore[0] = stoi(s);
    //     file >> s;
    //     cout << s << endl;
    //     tempStore[1] = stoi(s);
    //     file >> s;
    //     cout << s << endl;
    //     tempStore[2] = stoi(s);

    //     insertEdge(tempStore[0], tempStore[1], tempStore[2]);
    // }
    file.close();
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
