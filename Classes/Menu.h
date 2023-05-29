#ifndef DA_PROJ2_MENU_H
#define DA_PROJ2_MENU_H

#include "Graph.h"
#include "Reading.h"
#include <iostream>

class Menu {
public:
    static void readmenu();
    static void TSPalgorithmsSubmenu(Graph* graph);
    static double TSPbacktrack(Graph* graph);
    static void TSPtriangularInequality(Graph* graph);
    static double printElapsedTime(timeval start, timeval end);
};


#endif