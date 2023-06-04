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
        double elapsedBacktrack, elapsedTriangular, elapsedTriangular2, elapsedNN, distBacktrack, distTriangular, distTriangular2, distNN;
    };

    std::unordered_map<string, Node, StringHash, StringEqual> nodesMAP;
    double **dists = new double*[10000];
    report graphreport{0, 0, 0, 0,0,0,0,0};

    ///@brief Helper function to save a new optimal path
    ///@param n path size
    ///@param current_path array with the current path
    ///@param path final optimal path
    ///@note Helper function for the backtrack algorithm
    void savepath(int n, int current_path[], int path[]);

    ///@brief Function for the TSP backtrack algorithm
    ///@param currDist current path distance
    ///@param minDist current min distance
    ///@param currentIndx current path array index
    ///@param currentPath array with the current path
    ///@param path array with the optimal path
    ///@returns the TSP backtrack distance
    double TSPRec(double currDist, double *minDist, int currentIndx, int n, int currentPath[], int path[]);

    ///@brief Function to calculate the MST
    ///@note Auxiliar function for the TSP triangular inequality algorithm
    ///@returns the distance aproximation
    double primMST();

    ///@brief Function to perform a pre-Order walk in the MST
    ///@note Used after prim
    ///@note Auxiliar function for the TSP triangular inequality algorithm
    ///@param nodeID the current node
    ///@param primVisit vector with all nodes and sorted by prim visit
    ///@param preOrder vector with nodes after the pre-Order
    ///@returns the distance aproximation
    double preOrderWalk(string nodeID,vector<string>&primVisit, vector<string>* preOrder);

    ///@brief Function to calculate the MST
    ///@note Auxiliar function for the TSP triangular inequality algorithm
    ///@note second version of triangular inequality
    ///@returns the distance aproximation
    double primMST2();

    ///@brief Function to perform a pre-Order walk in the MST
    ///@note Used after prim
    ///@note Auxiliar function for the TSP triangular inequality algorithm
    ///@param nodeID the current node
    ///@param primVisit vector with all nodes and sorted by prim visit
    ///@param preOrder vector with nodes after the pre-Order
    ///@param mst graph representing the mst after prim
    ///@returns the distance aproximation
    double preOrderWalk2(string nodeID, vector<string>& primVisit, vector<string> *preOrder, Graph *mst);

    ///@note Auxiliar function for the second version of the triangular inequality
    ///@note Auxiliar function to perform the pre-Order
    ///@param node current node
    ///@param vector with nodes after the pre-Order
    ///@param mst graph representing the mst after prim
    void preorder_helper(string node, vector<string> *preOrder, Graph *mst);

    ///@note Auxiliar function to reset node atributes
    void resetNodes();

    ///@brief Auxiliar function for the triangular inequality algorithm
    ///@note calculates the distance between 2 nodes
    ///@param nodeA
    ///@param nodeB
    ///@returns the distance between the 2 nodes in meters
    double HaversineDist(string nodeA, string nodeB);

    ///@brief Auxiliar function for the Haversine
    ///@param degrees
    ///@returns coordinate value from degrees to radians
    double degreesToRadians(double degrees);

    ///@brief Function for the TSP nearest Neightbour algorithm
    ///@param origin the starting node
    ///@returns a vector with nodes representing the path
    vector<string> nearestNeightbour(string origin);

    ///@brief Auxiliar function for Neightbour algorithm
    ///@param next
    ///@param origin
    ///@returns
    pair<double, string> getNearest(string next, string origin);

    ///não sei o que é isto
    double swapNodes(int i, int j);

    ///@brief Function to compare the time complexity and distance aproximation between triangular inequality and backtrack algorithms
    void compareTriangular();

    ///@brief Function to compare the time complexity and distance aproximation between the 2 version of triangular inequality and backtrack algorithms
    void compareTriangular2();

    ///@brief Function to compare the time complexity and distance aproximation between nearest Neightbour and backtrack algorithms
    void compareNN();

    void ChristophidesOdddegree(vector<pair<string, bool>>& oddDegree);
    double christofidesAlgo();
    vector<struct Segment *> christofidesPrim();
    vector<struct Segment *> christofidesPerfectMatch(vector<pair<string, bool>>& oddDegree);

    void EulerianCycle(vector<Segment *> &christograph, vector<string> &eulerianpath);
};


#endif
