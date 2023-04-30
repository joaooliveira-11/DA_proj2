#include <iostream>
#include "Classes/Reading.h"
int main() {
    map<string, Graph*> graphs_map;
    //std::cout << "Hello, World!" << std::endl;

    Reading reading = Reading();
    graphs_map = reading.readAllFiles();

    for(auto name : graphs_map){
        cout << name.first << " " << name.second->nodesMAP.size() << endl;
    }
    return 0;
}
