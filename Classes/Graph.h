#ifndef DA_PROJ2_GRAPH_H
#define DA_PROJ2_GRAPH_H

#include <string>
#include <unordered_map>
#include "Node.h"

using namespace std;
class Graph {
private:

public:
    ~Graph();
    Graph();
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

    std::unordered_map<string, Node, StringHash, StringEqual> nodesMAP;
    double **dists = new double*[10000];

    void savepath(int n, int current_path[], int path[]);
    double TSPRec(double currDist, double *minDist, int currentIndx, int n, int currentPath[], int path[]);
    double primMST();
    double preOrderWalk(string nodeID,vector<string>primVisit, vector<string>* preOrder);
    void resetNodes();
    double HaversineDist(string nodeA, string nodeB);
    double degreesToRadians(double degrees);


    //void preOrderWalk(string nodeID, double &cost, string *current_node);
};


#endif
