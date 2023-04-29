#include <fstream>
#include <sstream>
#include <iostream>
#include "Reading.h"

map<string, Graph> graphs_map;

void Reading::read_stadium_graph(){
    Graph graph = Graph();
    string nodeA, nodeB;
    double cost;
    int verify = 0;
    char c1;
    ifstream in("../Project2Graphs/Toy-Graphs/stadiums.csv");
    if (!in.is_open()) exit(EXIT_FAILURE);

    for (string line; getline(in, line);) {
        istringstream iss(line);
        if (verify == 0) {
            verify++;
            continue;
        }
        getline(iss, nodeA, ',');
        getline(iss,nodeB, ',');
        iss >> cost >> c1;

        Node NODEa = Node(nodeA);
        Node NODEb = Node(nodeB);
        if(graph.nodesMAP.find(nodeA) == graph.nodesMAP.end()) graph.nodesMAP.emplace(nodeA, NODEa);
        if(graph.nodesMAP.find(nodeB) == graph.nodesMAP.end()) graph.nodesMAP.emplace(nodeB, NODEb);
        graph.addSegment(nodeA, nodeB, cost);
    }
    graphs_map.insert({"Stadium", graph});

}
map<string, Graph> Reading::readAllFiles(){
    read_stadium_graph();
    return graphs_map;
}