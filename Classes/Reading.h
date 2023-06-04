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

    ///@brief Reads stadiums and shipping toy graphs
    ///@param input controll which graph to read
    ///@note Store Nodes in an unordered_map and build a graph with vertexes representing Nodes and edges the segments.
    ///@returns A graph with the vertexes being Nodes and the edges being segments
    Graph* read_toygraphs(int input);

    ///@brief Reads the tourism graph
    ///@note Store Nodes in an unordered_map and build a graph with vertexes representing Nodes and edges the segments.
    ///@returns A graph with the vertexes being Nodes and the edges being segments
    Graph* read_tourism_graph();

    ///@brief Reads real world graphs
    ///@param input controll which graph to read
    ///@note Store Nodes in an unordered_map and build a graph with vertexes representing Nodes and edges the segments.
    ///@returns A graph with the vertexes being Nodes and the edges being segments
    Graph* read_realgraphs(int input);

    ///@brief Reads fully connected graphs
    ///@param input controll which graph to read
    ///@note Store Nodes in an unordered_map and build a graph with vertexes representing Nodes and edges the segments.
    ///@returns A graph with the vertexes being Nodes and the edges being segments
    Graph* read_fullyconectedGraphs(int input);

};

#endif
