#ifndef DA_PROJ2_SEGMENT_H
#define DA_PROJ2_SEGMENT_H

using namespace std;
#include <string>

class Segment {
private:
    string nodeA, nodeB;
    double cost;
public:
    Segment(string _nodeA, string _nodeB, double _cost);
    string getNodeA() const;
    string getNodeB() const;
    double getCost() const;

    bool operator<(Segment b){if(this->getCost() > b.getCost()) return true; else return false;}
};

#endif
