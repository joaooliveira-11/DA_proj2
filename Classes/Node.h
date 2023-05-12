#ifndef DA_proj2_NODE_H
#define DA_proj2_NODE_H
using namespace std;
#include <string>
#include <vector>
#include "Segment.h"

class Node {
private:
    string id;
    bool visited = false;
    vector<Segment *> outgoing;
    vector<Segment *> incoming;

public:
    Node(string _id);
    string getID() const;
    vector<Segment *> getOutgoing() const;
    vector<Segment *> getIncoming() const;
    void addIncoming(Segment *segment);
    void addOutgoing(Segment *s);
    void setSegments(vector<Segment *> newOutgoing);
    void setIncoming(vector<Segment *> newIncoming);

    bool isVisited();
    void setVisited(bool visited_);
};


#endif
