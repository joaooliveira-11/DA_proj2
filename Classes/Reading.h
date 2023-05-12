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
    Graph* read_stadium_graph();
    Graph* read_shiping_graph();
    Graph* read_tourism_graph();
    Graph* read_realgraph1();
    Graph* read_realgraph2();
    Graph* read_realgraph3();

};

#endif
