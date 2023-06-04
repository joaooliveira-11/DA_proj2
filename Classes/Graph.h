#ifndef DA_PROJ2_GRAPH_H
#define DA_PROJ2_GRAPH_H

#include <string>
#include <unordered_map>
#include "Node.h"
#include <set>

using namespace std;
class Graph {
private:

public:
    ~Graph();

    ///@brief Constructor of new Graph
    Graph();

    ///@brief Add a segment to the graph
    ///@param _nodeA Origin of the segment
    ///@param _nodeB Destiny of the segment
    ///@param _cost Segment cost
    ///@note Time complexity : O(1)
    ///@returns true if added, false otherwise
    bool addSegment(string _nodeA, string _nodeB, double _cost);

    struct StringHash {
        std::size_t operator()(const string& str) const {
            return 37* hash<string>()(str);
        }
    };

    struct StringEqual {
        bool operator()(const string& str1, const string& str2) const {
            return str1 == str2;
        }
    };

    struct report{
        double elapsedBacktrack, elapsedTriangular, elapsedTriangular2, elapsedNN, elapsedCristo, distBacktrack, distTriangular, distTriangular2, distNN, distCristo;
    };

    std::unordered_map<string, Node, StringHash, StringEqual> nodesMAP;
    double **dists = new double*[10000];
    report graphreport{0, 0, 0, 0,0,0,0,0, 0, 0};

    ///@brief Helper function to save a new optimal path
    ///@param n path size
    ///@param current_path array with the current path
    ///@param path final optimal path
    ///@note Time complexity : O(n), where n is the number of nodes
    ///@note Helper function for the backtrack algorithm
    void savepath(int n, int current_path[], int path[]);

    ///@brief Function for the TSP backtrack algorithm
    ///@param currDist current path distance
    ///@param minDist current min distance
    ///@param currentIndx current path array index
    ///@param currentPath array with the current path
    ///@param path array with the optimal path
    ///@note Time complexity : O(n!), where n is the number of nodes
    ///@returns the TSP backtrack distance
    double TSPRec(double currDist, double *minDist, int currentIndx, int n, int currentPath[], int path[]);

    ///@brief Function to calculate the MST
    ///@note Auxiliar function for the TSP triangular inequality algorithm
    ///@note Time complexity : O(E log V), where E is the number of segments and V the number of nodes
    ///@returns the distance aproximation
    double primMST();

    ///@brief Function to perform a pre-Order walk in the MST
    ///@note Used after prim
    ///@note Auxiliar function for the TSP triangular inequality algorithm
    ///@param nodeID the current node
    ///@param primVisit vector with all nodes and sorted by prim visit
    ///@param preOrder vector with nodes after the pre-Order
    ///@note Time complexity : O(n), where n is the size of primVisit vector
    ///@returns the distance aproximation
    double preOrderWalk(string nodeID,vector<string>&primVisit, vector<string>* preOrder);

    ///@brief Function to calculate the MST
    ///@note Auxiliar function for the TSP triangular inequality algorithm
    ///@note second version of triangular inequality
    ///@note Time complexity : O(E log V), where E is the number of segments and V the number of nodes
    ///@returns the distance aproximation
    double primMST2();

    ///@brief Function to perform a pre-Order walk in the MST
    ///@note Used after prim
    ///@note Auxiliar function for the TSP triangular inequality algorithm
    ///@param nodeID the current node
    ///@param primVisit vector with all nodes and sorted by prim visit
    ///@param preOrder vector with nodes after the pre-Order
    ///@param mst graph representing the mst after prim
    ///@note Time complexity : O(n), where n is the size of primVisit vector
    ///@returns the distance aproximation
    double preOrderWalk2(string nodeID, vector<string>& primVisit, vector<string> *preOrder, Graph *mst);

    ///@note Auxiliar function for the second version of the triangular inequality
    ///@note Auxiliar function to perform the pre-Order
    ///@param node current node
    ///@param vector with nodes after the pre-Order
    ///@note Time complexity : O(E), where E is the number of segments.
    ///@param mst graph representing the mst after prim
    void preorder_helper(string node, vector<string> *preOrder, Graph *mst);

    ///@note Auxiliar function to reset node atributes
    ///@note Time complexity : O(n), where n is the number of nodes
    void resetNodes();

    ///@brief Auxiliar function for the triangular inequality algorithm
    ///@note calculates the distance between 2 nodes
    ///@param nodeA
    ///@param nodeB
    ///@note Time complexity : O(1)
    ///@returns the distance between the 2 nodes in meters
    double HaversineDist(string nodeA, string nodeB);

    ///@brief Auxiliar function for the Haversine
    ///@param degrees
    ///@note Time complexity : O(1)
    ///@returns coordinate value from degrees to radians
    double degreesToRadians(double degrees);

    ///@brief Function for the TSP nearest Neightbour algorithm
    ///@param origin the starting node
    ///@note Time complexity : O(n^2)
    ///@returns a vector with nodes representing the path
    vector<string> nearestNeightbour(string origin);

    ///@brief Auxiliar function for Neightbour algorithm
    ///@param next
    ///@param origin
    ///@note Time complexity : O(n)
    ///@returns
    pair<double, string> getNearest(string next, string origin);

    double swapNodes(int i, int j);

    ///@brief Function to compare the time complexity and distance aproximation between triangular inequality and backtrack algorithms
    ///@note Time complexity : O(1)
    void compareTriangular();

    ///@brief Function to compare the time complexity and distance aproximation between the 2 version of triangular inequality and backtrack algorithms
    ///@note Time complexity : O(1)
    void compareTriangular2();

    ///@brief Function to compare the time complexity and distance aproximation between nearest Neightbour and backtrack algorithms
    ///@note Time complexity : O(1)
    void compareNN();

    ///@brief Function to compare the time complexity and distance aproximation between christofides and backtrack algorithms
    ///@note Time complexity : O(1)
    void compareChristofides();

    struct SegmentComparator {
        bool operator()(const Segment* seg1, const Segment* seg2) const {
            if (seg1->getNodeA() != seg2->getNodeA()) {
                return seg1->getNodeA() < seg2->getNodeA();
            } else if (seg1->getNodeB() != seg2->getNodeB()) {
                return seg1->getNodeB() < seg2->getNodeB();
            } else {
                return seg1->getCost() < seg2->getCost();
            }
        }
    };

    ///@brief Function for the MST
    ///@returns A set with all MST edges
    ///@note Time complexity : O(E log V), where E is the number of segments and V the number of nodes
    set<Segment*, Graph::SegmentComparator> christofidesPrim();

    ///@brief Function to get the MST nodes with odd degrees
    ///@param oddDegree
    ///@note Time Complexity : O(n)
    void ChristophidesOdddegree(vector<pair<string, bool>>& oddDegree);

    ///@brief Function for the christofides nodes Perfect Match
    ///@param oddDegree
    ///@note Time Complexity : O(n ^2)
    ///@returns Set with the segments of the perfect matches
    set<Segment*, Graph::SegmentComparator> christofidesPerfectMatch(vector<pair<string, bool>>& oddDegree);

    ///@brief Function for the christofides eulerian Cycle
    ///@param christograph the mst graph with the perfect match segments
    ///@param eulerianpath vector to save the eulerian path
    ///@note Time Complexity: O(n)
    void EulerianCycle(set<Segment*, Graph::SegmentComparator> &christograph, vector<string>& eulerianpath);

    ///@brief Function for the christofides algorithm
    ///@note Time Complexity:  O(E log V + V^2), where E is the number of edges and v the number of nodes
    ///@returns an aproximation distance of the TSP
    double christofidesAlgo();
};


#endif
