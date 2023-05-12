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

    Graph* read_fullyconected25();
    Graph* read_fullyconected50();
    Graph* read_fullyconected75();
    Graph* read_fullyconected100();
    Graph* read_fullyconected200();
    Graph* read_fullyconected300();
    Graph* read_fullyconected400();
    Graph* read_fullyconected500();
    Graph* read_fullyconected600();
    Graph* read_fullyconected700();
    Graph* read_fullyconected800();
    Graph* read_fullyconected900();

    Graph* read_realgraph1();
    Graph* read_realgraph2();
    Graph* read_realgraph3();

};

#endif
