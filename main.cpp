#include <iostream>
#include "Classes/Reading.h"

int main() {
    Reading reading = Reading();
    Graph *tourismgraph;
    Graph *stadiumsgraph;
    Graph *shippinggraph;

    Graph *RWgraph1;
    Graph *RWgraph2;
    Graph *RWgraph3;

    int option;
    cout << "===============MAIN MENU===============" << endl;
    cout << "Chose a type of Graph to work with" << endl;
    cout << "1 - Toy-Graphs: tourism" << endl;
    cout << "2 - Toy-Graphs: stadiums" << endl;
    cout << "3 - Toy-Graphs: shipping" << endl;
    cout << "4 - Real-World-Graphs: 1" << endl;
    cout << "5 - Real-World-Graphs: 2" << endl;
    cout << "6 - Real-World-Graphs: 3" << endl;
    cin >> option;

    switch (option) {
        case 1: {
            tourismgraph = reading.read_tourism_graph();
            int n = tourismgraph->nodesMAP.size();
            double minDist = 100000000.0;
            int currentPath[n];
            int path[n];
            currentPath[0] = 0;
            tourismgraph->nodesMAP.find(to_string(0))->second.setVisited(true);
            tourismgraph->TSPRec(0, &minDist, 1, n, currentPath, path);
            cout << minDist << endl;
            for(int i = 0; i < n;i++){
                cout << path[i] << endl;
            }
            break;
        }
        case 2:
            stadiumsgraph = reading.read_stadium_graph();
            cout << stadiumsgraph->nodesMAP.size() << endl;
            break;
        case 3: {
            shippinggraph = reading.read_shiping_graph();
            int n = shippinggraph->nodesMAP.size();
            double minDist = 100000000.0;
            int currentPath[n];
            int path[n];
            currentPath[0] = 9;
            shippinggraph->TSPRec(0, &minDist, 1, n, currentPath, path);
            cout << minDist;
            break;
        }
        case 4:
            RWgraph1 = reading.read_realgraph1();
            cout << RWgraph1->nodesMAP.size() << endl;
            break;
        case 5:
            RWgraph2 = reading.read_realgraph2();
            cout << RWgraph2->nodesMAP.size() << endl;
            break;
        case 6:
            RWgraph3 = reading.read_realgraph3();
            cout << RWgraph3->nodesMAP.size() << endl;
            break;
        default:
            break;
    }
    return 0;
}
