#include <fstream>
#include <sstream>
#include <iostream>
#include "Reading.h"

Graph* Reading::read_toygraphs(int input){
    string path;
    switch (input) {
        case 1:
            path = "../Project2Graphs/Toy-Graphs/shipping.csv";
            break;
        case 2:
            path = "../Project2Graphs/Toy-Graphs/stadiums.csv";
            break;
        default:
            break;
    }

    Graph* graph = new Graph();
    string nodeA, nodeB;
    double cost;
    int verify = 0;
    char c1;
    ifstream in(path);
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
        if(graph->nodesMAP.find(nodeA) == graph->nodesMAP.end()) graph->nodesMAP.emplace(nodeA, NODEa);
        if(graph->nodesMAP.find(nodeB) == graph->nodesMAP.end()) graph->nodesMAP.emplace(nodeB, NODEb);
        graph->addSegment(nodeA, nodeB, cost);
        graph->addSegment(nodeB, nodeA, cost);
    }
    return graph;
}

Graph* Reading::read_tourism_graph(){
    Graph* graph = new Graph();
    string nodeA, nodeB;
    string labelA, labelB;
    double cost;
    int verify = 0;
    char c1;
    ifstream in("../Project2Graphs/Toy-Graphs/tourism.csv");
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
        getline(iss,labelA, ',');
        getline(iss,labelB, ',');

        Node NODEa = Node(nodeA);
        Node NODEb = Node(nodeB);
        if(graph->nodesMAP.find(nodeA) == graph->nodesMAP.end()) graph->nodesMAP.emplace(nodeA, NODEa);
        if(graph->nodesMAP.find(nodeB) == graph->nodesMAP.end()) graph->nodesMAP.emplace(nodeB, NODEb);
        graph->addSegment(nodeA, nodeB, cost);
        graph->addSegment(nodeB, nodeA, cost);
    }
    return graph;
}

Graph* Reading::read_realgraphs(int input){
    string nodespath, edgespath;
    switch (input) {
        case 1:
            nodespath = "../Project2Graphs/Real-World-Graphs/graph1/nodes.csv";
            edgespath = "../Project2Graphs/Real-World-Graphs/graph1/edges.csv";
            break;
        case 2 :
            nodespath = "../Project2Graphs/Real-World-Graphs/graph2/nodes.csv";
            edgespath = "../Project2Graphs/Real-World-Graphs/graph2/edges.csv";
            break;
        case 3:
            nodespath = "../Project2Graphs/Real-World-Graphs/graph3/nodes.csv";
            edgespath = "../Project2Graphs/Real-World-Graphs/graph3/edges.csv";
            break;
        default:
            break;
    }
    Graph* graph = new Graph();
    string nodeA, nodeB;
    string node;
    double cost;
    double latitude, longitude;
    int verify = 0;
    char c1;
    ifstream in(nodespath);
    if (!in.is_open()) exit(EXIT_FAILURE);

    for (string line; getline(in, line);) {
        istringstream iss(line);
        if (verify == 0) {
            verify++;
            continue;
        }
        getline(iss, node, ',');
        iss >> longitude >> c1;
        iss >> latitude >> c1;

        Node NODE = Node(node);
        NODE.setLONG(longitude);
        NODE.setLAT(latitude);

        if(graph->nodesMAP.find(node) == graph->nodesMAP.end()) graph->nodesMAP.emplace(node, NODE);
    }

    ifstream in2(edgespath);
    if (!in2.is_open()) exit(EXIT_FAILURE);

    for (string line; getline(in2, line);) {
        istringstream iss2(line);
        if (verify == 0) {
            verify++;
            continue;
        }
        getline(iss2, nodeA, ',');
        getline(iss2,nodeB, ',');
        iss2 >> cost >> c1;

        graph->addSegment(nodeA, nodeB, cost);
        graph->addSegment(nodeB, nodeA, cost);
    }
    return graph;
}

Graph* Reading::read_fullyconectedGraphs(int input){
    string edgespath;
    switch (input) {
        case 25:
            edgespath = "../Project2Graphs/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_25.csv";
            break;
        case 50 :
            edgespath = "../Project2Graphs/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_50.csv";
            break;
        case 75:
            edgespath = "../Project2Graphs/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_75.csv";
            break;
        case 100:
            edgespath = "../Project2Graphs/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_100.csv";
            break;
        case 200:
            edgespath = "../Project2Graphs/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_200.csv";
            break;
        case 300:
            edgespath = "../Project2Graphs/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_300.csv";
            break;
        case 400:
            edgespath = "../Project2Graphs/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_400.csv";
            break;
        case 500:
            edgespath = "../Project2Graphs/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_500.csv";
            break;
        case 600:
            edgespath = "../Project2Graphs/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_600.csv";
            break;
        case 700:
            edgespath = "../Project2Graphs/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_700.csv";
            break;
        case 800:
            edgespath = "../Project2Graphs/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_800.csv";
            break;
        case 900:
            edgespath = "../Project2Graphs/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_900.csv";
            break;
        default:
            break;
    }

    Graph* graph = new Graph();
    string nodeA, nodeB;
    double cost;
    char c1;
    ifstream in(edgespath);
    if (!in.is_open()) exit(EXIT_FAILURE);

    for (string line; getline(in, line);) {
        istringstream iss(line);
        getline(iss, nodeA, ',');
        getline(iss,nodeB, ',');
        iss >> cost >> c1;

        Node NODEa = Node(nodeA);
        Node NODEb = Node(nodeB);
        if(graph->nodesMAP.find(nodeA) == graph->nodesMAP.end()) graph->nodesMAP.emplace(nodeA, NODEa);
        if(graph->nodesMAP.find(nodeB) == graph->nodesMAP.end()) graph->nodesMAP.emplace(nodeB, NODEb);
        graph->addSegment(nodeA, nodeB, cost);
        graph->addSegment(nodeB, nodeA, cost);
    }
    return graph;
}
