#ifndef DA_PROJ2_SEGMENT_H
#define DA_PROJ2_SEGMENT_H

using namespace std;
#include <string>

class Segment {
private:
    string nodeA, nodeB;
    double cost;
public:

    ///@brief Constructor of new Segment given it's departure node id, arrival node id and segment cost
    ///@param _nodeA
    ///@param _nodeB
    ///@param _cost
    Segment(string _nodeA, string _nodeB, double _cost);

    ///@brief Getter for the Segment´s departure node id.
    ///@returns Segment´s departure node id.
    string getNodeA() const;

    ///@brief Getter for the Segment´s arrival node id.
    ///@returns Segment´s arrival node id.
    string getNodeB() const;

    ///@brief Getter for the Segment´s cost
    ///@returns the Segment´s cost
    double getCost() const;
};

#endif
