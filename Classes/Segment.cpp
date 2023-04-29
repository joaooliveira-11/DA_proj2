#include "Segment.h"

Segment::Segment(string _nodeA, string _nodeB, double _cost) : nodeA(_nodeA), nodeB(_nodeB), cost(_cost) {}

string Segment::getNodeA() const{
    return nodeA;
}
string Segment::getNodeB() const{
    return nodeB;
}
double Segment::getCost() const{
    return cost;
}