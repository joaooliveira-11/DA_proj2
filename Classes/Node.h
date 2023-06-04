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

    double longitude,latitude;
    bool longitudeSET = false;
    bool latitudeSET = false;

public:
    ///@brief Constructor of new Node given its id
    ///@param _id the node id
    Node(string _id);

    ///@brief Default constructor of new Node
    Node();

    ///@brief Getter for the Node's id
    ///@returns the Node´s id
    string getID() const;

    ///@brief Getter for the Node's outgoing edges
    ///@returns a vector with the Node's outgoing segments
    vector<Segment *> getOutgoing() const;

    ///@brief Getter for the Node's outgoing edges
    ///@returns a vector with the Node's incoming segments
    vector<Segment *> getIncoming() const;

    ///@brief adds a new incoming segment
    ///@param segment
    void addIncoming(Segment *segment);

    ///@brief adds a new outgoing segment
    ///@param s
    void addOutgoing(Segment *s);

    ///@brief Getter for the Node´s path
    ///@returns the Node´s path
    Segment* getPath();

    ///@brief Getter for the Node´s distance
    ///@note helper function for the prim algorithm
    ///@returns the Node´s distance
    double getDist();

    ///@brief Setter for the Node´s distance
    ///@param distance
    ///@note helper function for the prim algorithm
    void setDist(double distance);

    ///@brief Setter for the Node´s path
    ///@param path
    ///@note helper function for the prim algorithm
    void setPath(Segment *path);

    ///@brief Operator< overload.
    ///@param node
    ///@returns True if our Node´s distance is smaller than node's distance received as parameter.
    bool operator<(Node & node) const;

    ///@brief Function to know if a node is visited
    ///@returns true if visited, false otherwise
    bool isVisited();

    ///@brief Setter for the node´s visited atribute
    ///@param visited_
    void setVisited(bool visited_);

    ///@brief Setter for the node's queue Index
    ///@param index
    ///@note helper function for the prim algorithm
    void setQueuIndex(int index);

    ///@brief Setter for the node's longitude
    ///@param longitude_
    void setLONG(double longitude_);

    ///@brief Setter for the node's latitude
    ///@param longitude_
    void setLAT(double latitude_);

    ///@brief Getter for the node's longitude
    ///@returns the node's longitude
    double getLONG();

    ///@brief Getter for the node's latitude
    ///@returns the node's latitude
    double getLAT();

    ///@brief Function to know if the node's longitude is set
    ///@returns true if is set, false otherwise
    bool isLongSET();

    ///@brief Function to know if the node's latitude is set
    ///@returns true if is set, false otherwise
    bool isLatSET();

    int queueIndex = 0;
};


#endif
