#include <fstream>
#include <sstream>
#include <iostream>
#include "Reading.h"

Graph* Reading::read_stadium_graph(){
    Graph* graph = new Graph();
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
        if(graph->nodesMAP.find(nodeA) == graph->nodesMAP.end()) graph->nodesMAP.emplace(nodeA, NODEa);
        if(graph->nodesMAP.find(nodeB) == graph->nodesMAP.end()) graph->nodesMAP.emplace(nodeB, NODEb);
        graph->addSegment(nodeA, nodeB, cost);
        graph->addSegment(nodeB, nodeA, cost);
    }
    return graph;
}

Graph* Reading::read_shiping_graph(){
    Graph* graph = new Graph();
    string nodeA, nodeB;
    double cost;
    int verify = 0;
    char c1;
    ifstream in("../Project2Graphs/Toy-Graphs/shipping.csv");
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

Graph* Reading::read_realgraph1(){
    Graph* graph = new Graph();
    string nodeA, nodeB;
    string node;
    double cost;
    double latitude, longitude;
    int verify = 0;
    char c1;
    ifstream in("../Project2Graphs/Real-World-Graphs/graph1/nodes.csv");
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
        if(graph->nodesMAP.find(node) == graph->nodesMAP.end()) graph->nodesMAP.emplace(node, NODE);
    }

    ifstream in2("../Project2Graphs/Real-World-Graphs/graph1/edges.csv");
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
    }
    return graph;
}

Graph* Reading::read_realgraph2(){
    Graph* graph = new Graph();
    string nodeA, nodeB;
    string node;
    double cost;
    double latitude, longitude;
    int verify = 0;
    char c1;
    ifstream in("../Project2Graphs/Real-World-Graphs/graph2/nodes.csv");
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
        if(graph->nodesMAP.find(node) == graph->nodesMAP.end()) graph->nodesMAP.emplace(node, NODE);
    }

    ifstream in2("../Project2Graphs/Real-World-Graphs/graph2/edges.csv");
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
    }
    return graph;
}

Graph* Reading::read_realgraph3(){
    Graph* graph = new Graph();
    string nodeA, nodeB;
    string node;
    double cost;
    double latitude, longitude;
    int verify = 0;
    char c1;
    ifstream in("../Project2Graphs/Real-World-Graphs/graph3/nodes.csv");
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
        if(graph->nodesMAP.find(node) == graph->nodesMAP.end()) graph->nodesMAP.emplace(node, NODE);
    }

    ifstream in2("../Project2Graphs/Real-World-Graphs/graph3/edges.csv");
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
    }
    return graph;
}

Graph* Reading::read_fullyconected25(){
    Graph* graph = new Graph();
    string nodeA, nodeB;
    double cost;
    char c1;
    ifstream in("../Project2Graphs/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_25.csv");
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
    }
    return graph;
}

Graph* Reading::read_fullyconected50(){
    Graph* graph = new Graph();
    string nodeA, nodeB;
    double cost;
    char c1;
    ifstream in("../Project2Graphs/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_50.csv");
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
    }
    return graph;
}

Graph* Reading::read_fullyconected75(){
    Graph* graph = new Graph();
    string nodeA, nodeB;
    double cost;
    char c1;
    ifstream in("../Project2Graphs/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_75.csv");
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
    }
    return graph;
}

Graph* Reading::read_fullyconected100(){
    Graph* graph = new Graph();
    string nodeA, nodeB;
    double cost;
    char c1;
    ifstream in("../Project2Graphs/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_100.csv");
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
    }
    return graph;
}

Graph* Reading::read_fullyconected200(){
    Graph* graph = new Graph();
    string nodeA, nodeB;
    double cost;
    char c1;
    ifstream in("../Project2Graphs/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_200.csv");
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
    }
    return graph;
}

Graph* Reading::read_fullyconected300(){
    Graph* graph = new Graph();
    string nodeA, nodeB;
    double cost;
    char c1;
    ifstream in("../Project2Graphs/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_300.csv");
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
    }
    return graph;
}

Graph* Reading::read_fullyconected400(){
    Graph* graph = new Graph();
    string nodeA, nodeB;
    double cost;
    char c1;
    ifstream in("../Project2Graphs/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_400.csv");
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
    }
    return graph;
}

Graph* Reading::read_fullyconected500(){
    Graph* graph = new Graph();
    string nodeA, nodeB;
    double cost;
    char c1;
    ifstream in("../Project2Graphs/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_500.csv");
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
    }
    return graph;
}

Graph* Reading::read_fullyconected600(){
    Graph* graph = new Graph();
    string nodeA, nodeB;
    double cost;
    char c1;
    ifstream in("../Project2Graphs/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_600.csv");
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
    }
    return graph;
}

Graph* Reading::read_fullyconected700(){
    Graph* graph = new Graph();
    string nodeA, nodeB;
    double cost;
    char c1;
    ifstream in("../Project2Graphs/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_700.csv");
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
    }
    return graph;
}

Graph* Reading::read_fullyconected800(){
    Graph* graph = new Graph();
    string nodeA, nodeB;
    double cost;
    char c1;
    ifstream in("../Project2Graphs/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_800.csv");
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
    }
    return graph;
}

Graph* Reading::read_fullyconected900(){
    Graph* graph = new Graph();
    string nodeA, nodeB;
    double cost;
    char c1;
    ifstream in("../Project2Graphs/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_900.csv");
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
    }
    return graph;
}