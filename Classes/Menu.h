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

    ///@brief Runs the interactive user menu.
    static void readmenu();

    ///@brief Runs toy graphs submenu
    static void toyGraphs();

    ///@brief Runs real world graphs submenu
    static void realWorldGraphs();

    ///@brief Runs fully connected graphs submenu
    static void fullyConnectedGraphs();

    ///@brief Runs the TSP algorithms menu.
    ///@param graph the graph used in the TSP algorithms
    static void TSPalgorithmsSubmenu(Graph* graph);

    ///@brief Runs the TSP backtrack algorithm.
    ///@param graph the graph used
    static double TSPbacktrack(Graph* graph);

    ///@brief Runs the TSP triangular inequality algorithm.
    ///@note User can choose version 1 or 2 of this algorithm
    ///@param graph the graph used
    static void TSPtriangularInequality(Graph* graph);

    ///@brief Prints the elapsed time
    static double printElapsedTime(timeval start, timeval end);

    ///@brief Runs the TSP nearest Neightbour algorithm.
    ///@param graph the graph used
    static void TSPnearestNeighbor(Graph *graph);

    ///@brief Runs the 2-opt optimization.
    ///@param tour
    ///@param i
    ///@param j
    static void do2Opt(vector<string> &tour, int i, int j);

    ///@brief Runs the graph report
    ///@param graph the graph used
    ///@note Used to compare all algorithms and their time complexity and distance aproximation
    static void graphReport(Graph* graph);
};


#endif
