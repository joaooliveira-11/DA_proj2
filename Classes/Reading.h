#ifndef DA_PROJ2_READING_H
#define DA_PROJ2_READING_H


#include <string>
#include <map>
#include "Graph.h"
#include "Node.h"
#include "Segment.h"

using namespace std;

class Reading {
public:
    Graph* read_toygraphs(int input);
    Graph* read_tourism_graph();
    Graph* read_realgraphs(int input);
    Graph* read_fullyconectedGraphs(int input);

};

#endif
