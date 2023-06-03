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

    bool operator<(const Segment& other) const {
        if (nodeA != other.nodeA) {
            return nodeA < other.nodeA;
        }
        if (nodeB != other.nodeB) {
            return nodeB < other.nodeB;
        }
        return cost < other.cost;
    }
};

#endif
