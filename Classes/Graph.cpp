#include <limits>
#include <queue>
#include "Graph.h"
#include "Node.h"
#include "PQ.h"
#include <iostream>
#include <math.h>
#include <set>
#include <algorithm>

Graph::~Graph() {

}

Graph::Graph() {
    for (int i = 0; i < 10000; i++) {
        dists[i] = new double[10000];
        for (int j = 0; j < 10000; j++) {
            if (i == j) {
                dists[i][j] = 0;
            } else {
                dists[i][j] = std::numeric_limits<double>::infinity();
            }
        }
    }
}

bool Graph::addSegment(string _nodeA, string _nodeB, double _cost) {
    auto v1 = nodesMAP.find(_nodeA);
    auto v2 = nodesMAP.find(_nodeB);
    if (v1 == nodesMAP.end() || v2 == nodesMAP.end()) return false;
    Segment *s = new Segment(_nodeA, _nodeB, _cost);
    v1->second.addOutgoing(s);
    v2->second.addIncoming(s);
    int indexA = std::stoi(_nodeA);
    int indexB = std::stoi(_nodeB);
    dists[indexA][indexB] = _cost;
    return true;
}

double Graph::degreesToRadians(double degrees) {
    return degrees * M_PI / 180.0;
}

double Graph::HaversineDist(string nodeA, string nodeB){
    double longitudeA = nodesMAP.find(nodeA)->second.getLONG();
    double longitudeB = nodesMAP.find(nodeB)->second.getLONG();
    double latitudeA = nodesMAP.find(nodeA)->second.getLAT();
    double latitudeB = nodesMAP.find(nodeB)->second.getLAT();

    double deltaLatitude = degreesToRadians(latitudeB - latitudeA);
    double deltaLongitude = degreesToRadians(longitudeB - longitudeA);

    double a = std::sin(deltaLatitude / 2.0) * std::sin(deltaLatitude / 2.0) +
               std::cos(degreesToRadians(latitudeA)) * std::cos(degreesToRadians(latitudeB)) *
               std::sin(deltaLongitude / 2.0) * std::sin(deltaLongitude / 2.0);

    double c = 2.0 * std::atan2(std::sqrt(a), std::sqrt(1.0 - a));

    double distance = 6371.0 * c * 1000;
    return distance;
}

void Graph::resetNodes(){
    for(auto& pair: nodesMAP){
        pair.second.setVisited(false);
        pair.second.setDist(0);
        pair.second.setPath(nullptr);
        pair.second.setQueuIndex(0);
    }
}

void Graph::savepath(int n, int current_path[], int path[]) {
    for (unsigned i = 0; i < n; i++) {
        path[i] = current_path[i];
    }
}

double Graph::TSPRec(double currDist, double *minDist, int currentIndx, int n, int currentPath[], int path[]) {
    if (currentIndx == n) {
        currDist += dists[currentPath[currentIndx - 1]][currentPath[0]];
        if (currDist < *minDist) {
            *minDist = currDist;
            savepath(n, currentPath, path);
        }
    } else {
        for (int i = 0; i < n; i++) {
            int node = i;
            if (!(nodesMAP.find(to_string(node))->second.isVisited())) {
                if (currDist + dists[currentPath[currentIndx - 1]][node] < *minDist) {
                    currentPath[currentIndx] = node;
                    nodesMAP.find(to_string(node))->second.setVisited(true);
                    TSPRec(currDist + dists[currentPath[currentIndx - 1]][node], minDist, currentIndx + 1, n,
                           currentPath, path);
                    nodesMAP.find(to_string(node))->second.setVisited(false);
                }
            }
        }
    }
    return *minDist;
}

double Graph::primMST() {
    MutablePriorityQueue<Node> mutablePQ;
    vector<string> primVisit;

    for (auto& pair : nodesMAP) {
        pair.second.setVisited(false);
        pair.second.setDist(numeric_limits<double>::infinity());
        mutablePQ.insert(&pair.second);
    }

    nodesMAP.find("0")->second.setDist(0);
    nodesMAP.find("0")->second.setPath(nullptr);
    nodesMAP.find("0")->second.setVisited(true);
    mutablePQ.decreaseKey(&nodesMAP.find("0")->second);

    while (!mutablePQ.empty()) {
        Node* nodeOrig = mutablePQ.extractMin();
        primVisit.push_back(nodeOrig->getID());
        //cout << nodeOrig->getID() << endl;
        const string nodestartID = nodeOrig->getID();
        for(auto segment : nodeOrig->getOutgoing()){
            const string nodeDestID = segment->getNodeB();
            if(!(nodesMAP.find(nodeDestID)->second.isVisited()) && segment->getCost() < nodesMAP.find(nodeDestID)->second.getDist()){
                nodesMAP.find(nodeDestID)->second.setDist(segment->getCost());
                nodesMAP.find(nodeDestID)->second.setPath(segment);
                nodesMAP.find(nodestartID)->second.incrementDegree(1);
                mutablePQ.decreaseKey(&nodesMAP.find(nodeDestID)->second);
            }
        }
        nodesMAP.find(nodestartID)->second.setVisited(true);
    }
/*
    /// para o christophides
    vector<string> oddDegree;
    for(auto pair : nodesMAP){
        if((pair.second.getDegree() > 0) && ((pair.second.getDegree() % 2) == 1)){
            oddDegree.push_back(pair.second.getID());
        }
    }

    for(auto p : oddDegree){
        cout << p<<endl;
    }




    vector<vector<double>> costMatrix(oddDegree.size(), vector<double>(oddDegree.size(), numeric_limits<double>::infinity()));
    for (auto node :oddDegree) {
        int nodeA = stoi(node);
        for(auto s : nodesMAP.find(node)->second.getIncoming()){
            int nodeB = stoi(s->getNodeA());
            for(auto c : oddDegree) {
                if(c == s->getNodeA()) {
                    costMatrix[nodeA][nodeB] = s->getCost();
                }
            }
        }
    }

    hungarianAlgorithm(costMatrix);
*/

    ///para a triangular

    for(auto& pair : nodesMAP){
        pair.second.setVisited(false);
    }
    vector<string> preOrder;
    return preOrderWalk("0",primVisit,&preOrder);

}


//incomplete
void Graph::hungarianAlgorithm(vector<vector<double>> matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    vector<double> row_mins(cols, 0.0);
    vector<double> col_mins(rows, 0.0);

    //find row minimum
    for (int i = 0; i < rows; i++) {
        double row_min = numeric_limits<double>::infinity();
        for (int j = 0; j < cols; j++) {
            if (matrix[j][i] < row_min) {
                row_min = matrix[j][i];
            }
            row_mins[i] = row_min;
        }
    }
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            matrix[i][j] = matrix[i][j] == 0 ?  0 :  matrix[i][j] - row_mins[i];
        }
    }

    //find column minimum
    for (int i = 0; i < cols; i++) {
        double col_min = numeric_limits<double>::infinity();
        for (int j = 0; j < rows; j++) {
            if (matrix[i][j] < col_min) {
                col_min = matrix[i][j];
            }
            col_mins[i] = col_min;
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[j][i] == 0.0 ? (matrix[j][i] - col_mins[i]) : 0.0;
        }
    }
    //reduce matrix


}


double Graph::preOrderWalk(string nodeID, vector<string> primVisit, vector<string> *preOrder) {
    nodesMAP.find(nodeID)->second.setVisited(true);
    preOrder->push_back(nodeID);
    for (auto next_node: primVisit) {
        if (nodesMAP.find(next_node)->second.getPath() != nullptr) {
            if (nodesMAP.find(next_node)->second.getPath()->getNodeA() == nodeID &&
                !(nodesMAP.find(next_node)->second.isVisited())) {
                preOrderWalk(next_node, primVisit, preOrder);
            }
        }
    }
    if (nodesMAP.find(nodeID)->second.getPath() == nullptr) {
        double totalcost = 0;
        preOrder->push_back("0");
        for (int i = 0; i < preOrder->size() - 1; i++) {
            int nodeA = std::stoi((*preOrder)[i]);
            int nodeB = std::stoi((*preOrder)[i + 1]);
            if (dists[nodeA][nodeB] != std::numeric_limits<double>::infinity()) {
                totalcost += dists[nodeA][nodeB];
                cout << nodeA << " -> " << nodeB << " || distance: " << dists[nodeA][nodeB] << " || type: "
                     << "direct connection" << endl;
            } else {
                Node NODEA = nodesMAP.find( (*preOrder)[i] )->second;
                Node NODEB = nodesMAP.find ( (*preOrder)[i + 1] )->second;
                double distance = 0;
                if(NODEA.isLongSET() &&  NODEA.isLatSET() && NODEB.isLongSET() && NODEB.isLatSET()){
                    distance = HaversineDist(NODEA.getID(), NODEB.getID());
                    totalcost += distance;
                }
                cout << nodeA << " -> " << nodeB << " || distance: " << distance << " || type: " << "Haversine connection" << endl;
            }
        }
        cout << "Triangular Inequality Cost: " << totalcost << endl;
        return totalcost;
    }
    return 0.0;
}

pair<double, string> Graph::getNearest(string next, string origin){
        nodesMAP.find(next)->second.setVisited(true);
        double cost = std::numeric_limits<double>::infinity();
        string dest = "";
        for(auto i = 0; i < nodesMAP.size(); i++) {
            if (!nodesMAP.find(to_string(i))->second.isVisited() && (dists[stoi(next)][i] < cost) && to_string(i) != origin) {
                cost = dists[stoi(next)][i];
                dest = to_string(i);
            }
        }
    if(dest == "") return  { dists[stoi(origin)][stoi(next)], origin};
        return {cost, dest};
}

double Graph::nearestNeightbour(string origin){

    for(auto &i : nodesMAP){
        i.second.setVisited(false);
    }


    string next =  origin;
    string previous;
    double total = 0.0;
    do{
        previous = next;
        auto res = getNearest(next, origin);
        total += res.first;
        next  = res.second;
        /*cout << previous << " -> " << next << " || distance: " << dists[stoi(previous)][stoi(next)] << " || type: "
             << "direct connection" << endl; */
    }while(next != origin);

    return total;
}


