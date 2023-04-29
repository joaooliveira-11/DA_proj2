#include "Graph.h"

Graph::~Graph() {
}

bool Graph::addSegment(string _nodeA, string _nodeB, double _cost){
    auto v1 = nodesMAP.find(_nodeA);
    auto v2 = nodesMAP.find(_nodeB);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    Segment *s = new Segment(_nodeA, _nodeB, _cost);
    v1->second.addOutgoing(s);
    v2->second.addIncoming(s);
    return true;
}