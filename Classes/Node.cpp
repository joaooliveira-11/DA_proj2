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

void Node::setQueuIndex(int index){this->queueIndex = 0;}

void Node::setLONG(double longitude_){
    this->longitude = longitude_;
    this->longitudeSET = true;
}

void Node::setLAT(double latitude_){
    this->latitude = latitude_;
    this->latitudeSET = true;
}

double Node::getLONG(){ return longitude;}
double Node::getLAT(){ return latitude;}

bool Node::isLongSET() {return longitudeSET;}
bool Node::isLatSET() {return latitudeSET;}