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
    static map<string, Graph*> readAllFiles();
    static void read_stadium_graph();
    static void read_shiping_graph();
    static void read_tourism_graph();
    static void read_realgraph1();
    static void read_realgraph2();
    static void read_realgraph3();

};

#endif
