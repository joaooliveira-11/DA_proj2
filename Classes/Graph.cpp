#include <limits>
#include <queue>
#include "Graph.h"
#include "Node.h"
#include "PQ.h"
#include <iostream>
#include <math.h>
#include <stack>

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

double Graph::degreesToRadians(double coord) {
    return coord * M_PI / 180.0;
}

double Graph::HaversineDist(string nodeA, string nodeB){
    double longitudeA = nodesMAP.find(nodeA)->second.getLONG();
    double longitudeB = nodesMAP.find(nodeB)->second.getLONG();
    double latitudeA = nodesMAP.find(nodeA)->second.getLAT();
    double latitudeB = nodesMAP.find(nodeB)->second.getLAT();

    double deltaLatitude = degreesToRadians(latitudeB) - degreesToRadians(latitudeA);
    double deltaLongitude = degreesToRadians(longitudeB) - degreesToRadians(longitudeA);

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
                mutablePQ.decreaseKey(&nodesMAP.find(nodeDestID)->second);
            }
        }
        nodesMAP.find(nodestartID)->second.setVisited(true);
    }
    for(auto& pair : nodesMAP){
        pair.second.setVisited(false);
    }

    vector<string> preOrder;
    return preOrderWalk("0",primVisit,&preOrder);
}

double Graph::preOrderWalk(string nodeID, vector<string>& primVisit, vector<string> *preOrder) {
    nodesMAP.find(nodeID)->second.setVisited(true);
    preOrder->push_back(nodeID);

    for (size_t i = 0; i < primVisit.size(); i++) {
        const string& next_node = primVisit[i];
        auto& nextNode = nodesMAP.find(next_node)->second;
        auto* nextPath = nextNode.getPath();

        if (nextPath != nullptr && nextPath->getNodeA() == nodeID && !nextNode.isVisited()) {
            preOrderWalk(next_node, primVisit, preOrder);
        }
    }

    if (nodesMAP.find(nodeID)->second.getPath() == nullptr) {
        double totalCost = 0.0;
        preOrder->push_back("0");

        for (int i = 0; i < preOrder->size() - 1; i++) {
            int nodeA = std::stoi((*preOrder)[i]);
            int nodeB = std::stoi((*preOrder)[i + 1]);

            if (dists[nodeA][nodeB] != std::numeric_limits<double>::infinity()) {
                totalCost += dists[nodeA][nodeB];
                cout << nodeA << " -> " << nodeB << " || distance: " << dists[nodeA][nodeB] << " || type: "
                     << "direct connection" << endl;
            } else {
                Node NODEA = nodesMAP.find((*preOrder)[i])->second;
                Node NODEB = nodesMAP.find((*preOrder)[i + 1])->second;

                double distance = 0;

                if (NODEA.isLongSET() && NODEA.isLatSET() && NODEB.isLongSET() && NODEB.isLatSET()) {
                    distance = HaversineDist(NODEA.getID(), NODEB.getID());
                    totalCost += distance;
                }

                cout << nodeA << " -> " << nodeB << " || distance: " << distance << " || type: "
                     << "Haversine connection" << endl;
            }
        }

        cout << "Triangular Inequality Cost: " << totalCost << endl;
        return totalCost;
    }
    return 0.0;
}

void Graph::preorder_helper(string node, vector<string> *preOrder, Graph* mst){
    mst->nodesMAP.find(node)->second.setVisited(true);
    preOrder->push_back(node);
    for(auto segment : mst->nodesMAP.find(node)->second.getOutgoing()){
        if(!(mst->nodesMAP.find(segment->getNodeB())->second.isVisited())) preorder_helper(segment->getNodeB(), preOrder, mst);
    }
}

double Graph::primMST2(){
    Graph *mst = new Graph();
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
                mutablePQ.decreaseKey(&nodesMAP.find(nodeDestID)->second);
            }
        }
        nodesMAP.find(nodestartID)->second.setVisited(true);
    }
    for(auto pair : nodesMAP){
        auto path = pair.second.getPath();
        if(path!= nullptr){
            if (mst->nodesMAP.find(path->getNodeA()) == mst->nodesMAP.end()) {
                Node node = Node(path->getNodeA());
                mst->nodesMAP.emplace(node.getID(), node);
            }
            if (mst->nodesMAP.find(path->getNodeB()) == mst->nodesMAP.end()) {
                Node node = Node(path->getNodeB());
                mst->nodesMAP.emplace(node.getID(), node);
            }
            mst->nodesMAP.find(path->getNodeA())->second.addOutgoing(path);
        }
    }
    vector<string> preOrder;
    return preOrderWalk2("0", primVisit, &preOrder, mst);
}
double Graph::preOrderWalk2(string nodeID, vector<string>& primVisit, vector<string> *preOrder, Graph *mst){
    mst->nodesMAP.find(nodeID)->second.setVisited(true);
    preOrder->push_back(nodeID);

    for(auto itr = primVisit.begin(); itr != primVisit.end(); itr++){
        if(!(mst->nodesMAP.find(*itr)->second.isVisited())){
            preorder_helper(*itr,preOrder,mst);
        }
    }
    if (nodesMAP.find(nodeID)->second.getPath() == nullptr) {
        double totalCost = 0.0;
        preOrder->push_back("0");

        for (int i = 0; i < preOrder->size() - 1; i++) {
            int nodeA = std::stoi((*preOrder)[i]);
            int nodeB = std::stoi((*preOrder)[i + 1]);

            if (dists[nodeA][nodeB] != std::numeric_limits<double>::infinity()) {
                totalCost += dists[nodeA][nodeB];
                cout << nodeA << " -> " << nodeB << " || distance: " << dists[nodeA][nodeB] << " || type: "
                     << "direct connection" << endl;
            } else {
                Node NODEA = nodesMAP.find((*preOrder)[i])->second;
                Node NODEB = nodesMAP.find((*preOrder)[i + 1])->second;

                double distance = 0;

                if (NODEA.isLongSET() && NODEA.isLatSET() && NODEB.isLongSET() && NODEB.isLatSET()) {
                    distance = HaversineDist(NODEA.getID(), NODEB.getID());
                    totalCost += distance;
                }

                cout << nodeA << " -> " << nodeB << " || distance: " << distance << " || type: "
                     << "Haversine connection" << endl;
            }
        }

        cout << "Triangular Inequality Cost: " << totalCost << endl;
        return totalCost;
    }
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

vector<string> Graph::nearestNeightbour(string origin){

    for(auto &i : nodesMAP){
        i.second.setVisited(false);
        i.second.setDist(numeric_limits<double>::infinity());
    }


    string next =  origin;
    string previous;
    vector<string> tour;
    double total = 0.0;
    do{
        tour.push_back(next);
        nodesMAP.find(next)->second.setDist(total);
        previous = next;
        auto res = getNearest(next, origin);
        total += res.first;
        next  = res.second;
        cout << previous << " -> " << next << " || distance: " << dists[stoi(previous)][stoi(next)] << " || type: "
             << "direct connection" << endl;
    }while(next != origin);
    tour.push_back("0");
    cout << "Nearest Neighbor Aproximation: "  << total << endl;
    return tour;
}


double Graph::swapNodes(int i, int j){
    return nodesMAP.find(to_string(i))->second.getDist() - nodesMAP.find(to_string(j))->second.getDist();
}

void Graph::compareTriangular(){
    if (graphreport.elapsedBacktrack == 0 || graphreport.distBacktrack == 0 || graphreport.elapsedTriangular == 0 || graphreport.distTriangular == 0) {
        cout << "Comparison Data Unavailable: Backtrack and Triangular Inequality algorithms have not been run yet." << endl;
    } else {
        double ratioTime = (graphreport.elapsedTriangular / graphreport.elapsedBacktrack) * 100;
        double ratioDist = ((graphreport.distTriangular / graphreport.distBacktrack) * 100) - 100;
        cout << "Triangular Inequality Aproximation Analysis:" << endl;
        cout << "-----------------------------------------------" << endl;
        cout << "The Triangular Inequality approximation takes " << ratioTime << "% of the time it takes the Backtracking algorithm." << endl;
        cout << "The Triangular Inequality approximation distance is " << ratioDist << "% longer than the Backtracking algorithm distance." << endl;
    }
    cout << endl;
}
void Graph::compareTriangular2(){
    if (graphreport.elapsedBacktrack == 0 || graphreport.distBacktrack == 0 || graphreport.elapsedTriangular2 == 0 || graphreport.distTriangular2 == 0) {
        cout << "Comparison Data Unavailable: Backtrack and Triangular Inequality Second Version algorithms have not been run yet." << endl;
    } else {
        double ratioTime = (graphreport.elapsedTriangular2 / graphreport.elapsedBacktrack) * 100;
        double ratioDist = ((graphreport.distTriangular2 / graphreport.distBacktrack) * 100) - 100;
        cout << "Triangular Inequality Second Version Aproximation Analysis:" << endl;
        cout << "--------------------------------------------------------------" << endl;
        cout << "The second version of Triangular Inequality approximation takes " << ratioTime << "% of the time it takes the Backtracking algorithm." << endl;
        cout << "The second version of Triangular Inequality approximation distance is " << ratioDist << "% longer than the Backtracking algorithm distance." << endl;
    }
    cout << endl;
}
void Graph::compareNN(){
    if (graphreport.elapsedBacktrack == 0 || graphreport.distBacktrack == 0 || graphreport.elapsedNN == 0 || graphreport.distNN == 0) {
        cout << "Comparison Data Unavailable: Backtrack and Nearest Neighbor with 2-opt Optimization algorithms have not been run yet." << endl;
    } else {
        double ratioTime = (graphreport.elapsedNN / graphreport.elapsedBacktrack) * 100;
        double ratioDist = ((graphreport.distNN / graphreport.distBacktrack) * 100) - 100;
        cout << "Nearest Neighbor with 2-opt Optimization Analysis:" << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "The Nearest Neighbor with 2-opt optimization takes " << ratioTime << "% of the time it takes the Backtracking algorithm." << endl;
        cout << "The Nearest Neighbor with 2-opt optimization approximation distance is " << ratioDist << "% longer than the Backtracking algorithm distance." << endl;
    }
    cout << endl;
}

void Graph::compareChristofides(){
    if (graphreport.elapsedBacktrack == 0 || graphreport.distBacktrack == 0 || graphreport.elapsedCristo == 0 || graphreport.distCristo == 0) {
        cout << "Comparison Data Unavailable: Backtrack and Christofides algorithms have not been run yet." << endl;
    } else {
        double ratioTime = (graphreport.elapsedCristo / graphreport.elapsedBacktrack) * 100;
        double ratioDist = ((graphreport.distCristo / graphreport.distBacktrack) * 100) - 100;
        cout << "Christofides Aproximation Analysis:" << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "The Christofides approximation takes " << ratioTime << "% of the time it takes the Backtracking algorithm." << endl;
        cout << "The Christofides approximation distance is " << ratioDist << "% longer than the Backtracking algorithm distance." << endl;
    }
    cout << endl;
}

set<Segment*, Graph::SegmentComparator> Graph::christofidesPrim(){
    MutablePriorityQueue<Node> mutablePQ;
    set<Segment*, SegmentComparator> segments_mst;

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
        const string nodestartID = nodeOrig->getID();
        for(auto segment : nodeOrig->getOutgoing()){
            const string nodeDestID = segment->getNodeB();
            if(!(nodesMAP.find(nodeDestID)->second.isVisited()) && segment->getCost() < nodesMAP.find(nodeDestID)->second.getDist()){
                nodesMAP.find(nodeDestID)->second.setDist(segment->getCost());
                nodesMAP.find(nodeDestID)->second.setPath(segment);
                mutablePQ.decreaseKey(&nodesMAP.find(nodeDestID)->second);
            }
        }
        nodesMAP.find(nodestartID)->second.setVisited(true);
    }

    for(auto& pair : nodesMAP){
        if(pair.second.getPath() != nullptr){
            string nodestart = pair.second.getPath()->getNodeA();
            string nodedest = pair.second.getPath()->getNodeB();
            nodesMAP.find(nodestart)->second.incrementDegree(1);
            nodesMAP.find(nodedest)->second.incrementDegree(1);
            segments_mst.insert(pair.second.getPath());
            segments_mst.insert(new Segment (pair.second.getPath()->getNodeB(), pair.second.getPath()->getNodeA(), pair.second.getPath()->getCost()));

        }
        pair.second.setVisited(false);
    }

    return segments_mst;
}


void Graph::ChristophidesOdddegree(vector<pair<string, bool>>& oddDegree){
    for(auto pair : nodesMAP){
        if((pair.second.getDegree() > 0) && ((pair.second.getDegree() % 2) == 1)){
            oddDegree.emplace_back(pair.second.getID(), false);
        }
    }
}

set<Segment*, Graph::SegmentComparator> Graph::christofidesPerfectMatch(vector<pair<string, bool>>& oddDegree){
    set<Segment*, SegmentComparator> perfect_match;
    for(auto &node1 : oddDegree){
        if(!node1.second){
            node1.second = true;
            double min_dist = numeric_limits<double>::infinity();
            int match = -1;
            for(auto node2 = 0; node2 < oddDegree.size(); node2++) {
                if (dists[stoi(node1.first)][stoi(oddDegree[node2].first)] < min_dist && !oddDegree[node2].second) {
                    match = node2;
                    min_dist = dists[stoi(node1.first)][stoi(oddDegree[node2].first)];
                }
            }
            if(match != -1){
                oddDegree[match].second = true;
                perfect_match.insert(new Segment(node1.first, oddDegree[match].first, dists[stoi(node1.first)][stoi(oddDegree[match].first)]));
                perfect_match.insert(new Segment(oddDegree[match].first, node1.first, dists[stoi(node1.first)][stoi(oddDegree[match].first)]));
            }
        }
    }
    return perfect_match;
}
void Graph::EulerianCycle(set<Segment*, Graph::SegmentComparator> &christograph, vector<string>& eulerianpath){
    std::stack<string> stack;
    std::set<Segment*> visited;
    stack.push("0");

    while (!stack.empty()) {
        string current_node = stack.top();

        bool find_edge = false;
        for (auto it = christograph.begin(); it != christograph.end(); ++it) {
            Segment* edge = *it;
            if ((nodesMAP.find(edge->getNodeA())->second.getID() == current_node) && (visited.find(edge) == visited.end())) {
                visited.insert(edge);
                stack.push(edge->getNodeB());
                find_edge = true;
                break;
            }
        }

        if (!find_edge) {
            eulerianpath.push_back(stack.top());
            stack.pop();
        }
    }
}

double Graph::christofidesAlgo(){
    set<Segment*, SegmentComparator> mst_segments = christofidesPrim();
    vector<pair<string, bool>>oddDegree;
    ChristophidesOdddegree(oddDegree);
    set<Segment*, SegmentComparator> perfect_match = christofidesPerfectMatch(oddDegree);


    for(auto seg : perfect_match){
        if(mst_segments.find(seg) == mst_segments.end()) mst_segments.insert(seg);
    }

    vector<string> eulerianpath;
    EulerianCycle(mst_segments, eulerianpath);

    vector<string>finalPath;
    for (string node : eulerianpath) {
        if(!(nodesMAP.find(node)->second.isVisited())){
            finalPath.push_back(node);
            nodesMAP.find(node)->second.setVisited(true);
        }
    }

    finalPath.push_back("0");
    double distance = 0;

    for(int i = 0; i < finalPath.size() - 1; i++) {
        int nodeA = std::stoi(finalPath[i]);
        int nodeB = std::stoi(finalPath[i + 1]);
        if (dists[nodeA][nodeB] != std::numeric_limits<double>::infinity()) {
            distance += dists[nodeA][nodeB];
            cout << nodeA << " -> " << nodeB << " || distance: " << dists[nodeA][nodeB] << " || type: "
                 << "direct connection" << endl;
        }
    }
    cout << "Christofides Aproximation: " << distance << endl;

    return distance;
}

