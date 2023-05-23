#include "Node.h"

Node::Node(string _id) : id(_id) {}

Node::Node() = default;

string Node::getID() const{
    return id;
}

void Node::addOutgoing(Segment *s) {
    outgoing.push_back(s);
}

void Node::addIncoming(Segment *segment) {
    incoming.push_back(segment);
}

vector<Segment *> Node::getOutgoing() const{
    return outgoing;
}

vector<Segment *> Node::getIncoming() const{
    return incoming;
}

bool Node::operator<(Node & node) const {
    return this->dist < node.dist;
}

bool Node::isVisited() {return visited;}

void Node::setVisited(bool visited_) {this->visited = visited_;}

Segment* Node::getPath() {return path;}

double Node::getDist(){ return dist;}

void Node::setDist(double distance){ dist = distance;}

void Node::setPath(Segment *path) {this->path = path;}