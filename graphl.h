#include <iostream>
#include <fstream>
#include "nodedata.h"
#include <climits>

using namespace std;

const static int MAX_NODES = 100;
class GraphL
{
public:
    GraphL();

    ~GraphL();   

    void buildGraph(ifstream& file);

    void displayGraph();

    void depthFirstSearch();


private:
    int size;
    struct EdgeNode;
    struct GraphNode {
        EdgeNode * edgeHead;
        NodeData * data;
        bool visited;
    };

    struct EdgeNode {
        int adjGraphNode;
        EdgeNode* nextEdge;
    };

    GraphNode arrList[MAX_NODES];
    
};