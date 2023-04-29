#include <iostream>
#include "Classes/Reading.h"
int main() {
    map<string, Graph> graphs_map;
    //std::cout << "Hello, World!" << std::endl;

    Reading reading = Reading();
    graphs_map = reading.readAllFiles();
    /*
    cout << graphs_map["Stadium"].nodesMAP.size();

    for(auto i : graphs_map["Stadium"].nodesMAP){
        cout << i.first << " " << i.second.getOutgoing().size() << endl;
    }
     */
    //cout << graphs_map.size();
    for(auto i : graphs_map["Shipping"].nodesMAP){
        cout << i.first << " " << i.second.getOutgoing().size() << endl;
    }
    return 0;
}
