#ifndef DA_PROJ2_MENU_H
#define DA_PROJ2_MENU_H

#define tourism 0
#define stadiums 1
#define shipping 2
#define RW1 3
#define RW2 4
#define RW3 5
#define FC25 6
#define FC50 7
#define FC75 8
#define FC100 9
#define FC200 10
#define FC300 11
#define FC400 12
#define FC500 13
#define FC600 14
#define FC700 15
#define FC800 16
#define FC900 17

#include "Graph.h"
#include "Reading.h"
#include <iostream>

class Menu {
public:
    static void readmenu();
    static void toyGraphs();
    static void realWorldGraphs();
    static void fullyConnectedGraphs();

    static void TSPalgorithmsSubmenu(Graph* graph);
    static double TSPbacktrack(Graph* graph);
    static void TSPtriangularInequality(Graph* graph);
    static double printElapsedTime(timeval start, timeval end);

    static void TSPnearestNeighbor(Graph *graph);
    static void do2Opt(vector<string> &tour, int i, int j);

    static void graphReport(Graph* graph);
};


#endif
