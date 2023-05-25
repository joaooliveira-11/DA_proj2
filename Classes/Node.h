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

    Segment *path = nullptr;
    double dist = 0;

public:
    Node(string _id);
    Node();
    string getID() const;
    vector<Segment *> getOutgoing() const;
    vector<Segment *> getIncoming() const;
    void addIncoming(Segment *segment);
    void addOutgoing(Segment *s);
    //void setSegments(vector<Segment *> newOutgoing);
    //void setIncoming(vector<Segment *> newIncoming);

    Segment* getPath();
    double getDist();
    void setDist(double distance);
    void setPath(Segment *path);

    bool operator<(Node & node) const;


    bool isVisited();
    void setVisited(bool visited_);
    void setQueuIndex(int index);
    int queueIndex = 0;
};


#endif
