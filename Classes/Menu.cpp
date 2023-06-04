#include "Menu.h"
#include <bits/stdc++.h>
#include <sys/time.h>

Reading reading = Reading();
Graph* graphsArray[18];

double Menu::TSPbacktrack(Graph *graph) {
    int n = graph->nodesMAP.size();
    double minDist = 100000000.0;
    int currentPath[n];
    int path[n];
    currentPath[0] = 0;
    graph->nodesMAP.find(to_string(0))->second.setVisited(true);
    graph->TSPRec(0, &minDist, 1, n, currentPath, path);
    for (int i = 0; i < n; i++) {
        cout << path[i] << "-> ";
    }
    cout << "0" << endl;
    cout << "TSP Backtrack Cost: " << minDist << endl;
    graph->resetNodes();
    return minDist;
}

void Menu::TSPtriangularInequality(Graph *graph) {
    int option;
    cout << "===============TSP Triangular Submenu===============" << endl;
    cout << "Chose a version for this algorithm" << endl;
    cout << "1 - Triangular Inequality (better aproximation / slower)" << endl;
    cout << "2 - Triangular Inequality (worse aproximation / faster for larger graphs)" << endl;
    cin >> option;

    struct timeval start, end;
    ios_base::sync_with_stdio(false);
    gettimeofday(&start, NULL);
    switch (option) {
        case 1:
            graph->graphreport.distTriangular = graph->primMST();
            gettimeofday(&end, NULL);
            graph->graphreport.elapsedTriangular = printElapsedTime(start, end);
            break;
        case 2:
            graph->graphreport.distTriangular2 = graph->primMST2();
            gettimeofday(&end, NULL);
            graph->graphreport.elapsedTriangular2 = printElapsedTime(start, end);
            break;
    }
    graph->graphreport.distTriangular = graph->christofidesAlgo();
    graph->resetNodes();
}

void Menu::do2Opt(vector<string> &tour, int i, int j) {
    reverse(begin(tour) + i + 1, begin(tour) + j + 1);
}

void Menu::TSPnearestNeighbor(Graph *graph){
    vector<string> tour = graph->nearestNeightbour("0");

    double res = 0.0;
    for(int i = 0; i < tour.size() - 1; i++){
        res += graph->dists[stoi(tour[i])][stoi(tour[i + 1])];
    }

    cout <<"performed 2-opt local optimization of the tour: " <<endl;
    int n = tour.size();
    bool foundImprovement = true;
    while (foundImprovement) {
        foundImprovement = false;
        for (int i = 0; i <= n - 2; i++) {
            for (int j = i + 1; j <= n - 1; j++) {
                int diff =  - graph->dists[stoi(tour[i])][stoi(tour[(i + 1) % n])] - graph->dists[stoi(tour[j])][stoi(tour[(j + 1) % n])]
                        + graph->dists[stoi(tour[i])][stoi(tour[j])] + graph->dists[stoi(tour[(i + 1) % n])][stoi(tour[(j + 1) % n])];

                // If the length of the path is reduced, do a 2-opt swap
                if (diff < 0) {
                    cout << "swapped nodes " <<tour[i] << " and " <<tour[j] <<endl;
                    do2Opt(tour, i, j);
                    res += diff;
                    foundImprovement = true;
                }
            }
        }
    }

    cout <<endl << "New tour:" <<endl;
    for(int i = 1; i < tour.size(); i++){
        cout << tour[i - 1] << " -> " << tour[i] << " || distance: " << graph->dists[stoi(tour[i - 1])][stoi(tour[i])] << " || type: "
             << "direct connection" << endl;
    }



    cout <<endl <<"2-opt improvement:" << res <<endl <<endl;

    graph->resetNodes();
}

double Menu::printElapsedTime(timeval start, timeval end){
    double elapsed =  (end.tv_sec - start.tv_sec) * 1e6;
    elapsed = (elapsed + (end.tv_usec -
                   start.tv_usec)) * 1e-6;
    cout << "The elapsed time was: " << fixed <<elapsed <<setprecision(6) <<"seconds. "<< endl;
    return elapsed;
}

void Menu::graphReport(Graph* graph){
    cout << "Heuristics time and cost approximation: comparisons between them and backtracking" << std::endl;
    cout << "---------------------------------------------------------------------------------" << endl;
    graph->compareTriangular();
    graph->compareTriangular2();
    graph->compareNN();
}
void Menu::TSPalgorithmsSubmenu(Graph *graph) {

    int option;
    cout << "===============TSP Algorithms===============" << endl;
    cout << "Chose an aproach for the TSP" << endl;
    cout << "1 - TSP Backtrack Aproach (only for toy graphs)" << endl;
    cout << "2 - TSP Triangular Inequality Aproach" << endl;
    cout << "3 - TSP Nearest Neighbor" << endl;
    cout << "4 - Report (only for toy graphs)" << endl;
    cin >> option;

    switch (option) {
        case 1: {
            struct timeval start, end;
            gettimeofday(&start, NULL);
            ios_base::sync_with_stdio(false);
            graph->graphreport.distBacktrack = TSPbacktrack(graph);

            gettimeofday(&end, NULL);
            graph->graphreport.elapsedBacktrack = printElapsedTime(start, end);

            string decision;
            cout << "Do you want to do another action?. (ex.: yes or no) \n";
            cin >> decision;
            while (decision != "yes" && decision != "no") {
                cout << "Do you want to do another action?. (ex.: yes or no) \n";
                cin >> decision;
            }
            if (decision == "yes"){
                TSPalgorithmsSubmenu(graph);
                break;
            }
            else {
                readmenu();
                break;
            }
        }
        case 2: {
            TSPtriangularInequality(graph);
            string decision;
            cout << "Do you want to do another action?. (ex.: yes or no) \n";
            cin >> decision;
            while (decision != "yes" && decision != "no") {
                cout << "Do you want to do another action?. (ex.: yes or no) \n";
                cin >> decision;
            }
            if (decision == "yes") {
                TSPalgorithmsSubmenu(graph);
                break;
            }
            else {
                readmenu();
                break;
            }
        }

        case 3:{
            struct timeval start, end;
            gettimeofday(&start, NULL);
            ios_base::sync_with_stdio(false);

            TSPnearestNeighbor(graph);

            gettimeofday(&end, NULL);
            graph->graphreport.elapsedNN = printElapsedTime(start, end);

            graph->resetNodes();

            string decision;
            cout << "Do you want to do another action?. (ex.: yes or no) \n";
            cin >> decision;
            while (decision != "yes" && decision != "no") {
                cout << "Do you want to do another action?. (ex.: yes or no) \n";
                cin >> decision;
            }
            if (decision == "yes") {
                TSPalgorithmsSubmenu(graph);
                break;
            }
            else {
                readmenu();
                break;
            }
        }
        case 4:{
            graphReport(graph);
            string decision;
            cout << "Do you want to do another action?. (ex.: yes or no) \n";
            cin >> decision;
            while (decision != "yes" && decision != "no") {
                cout << "Do you want to do another action?. (ex.: yes or no) \n";
                cin >> decision;
            }
            if (decision == "yes") {
                TSPalgorithmsSubmenu(graph);
                break;
            }
            else {
                readmenu();
                break;
            }
        }
        default:
            break;
    }
}

void Menu::toyGraphs() {
    int option;
    cout << "===============Toy Graphs Submenu===============" << endl;
    cout << "Chose a Toy Graph to work with" << endl;
    cout << "1 - tourism" << endl;
    cout << "2 - stadiums" << endl;
    cout << "3 - shipping" << endl;
    cin >> option;

    switch (option) {
        case 1: {
            if (graphsArray[tourism] == nullptr) graphsArray[tourism] = reading.read_tourism_graph();
            TSPalgorithmsSubmenu(graphsArray[tourism]);
            break;
        }
        case 2: {
            if (graphsArray[stadiums] == nullptr) graphsArray[stadiums] = reading.read_toygraphs(2);
            TSPalgorithmsSubmenu(graphsArray[stadiums]);
            break;
        }
        case 3: {
            if (graphsArray[shipping] == nullptr) graphsArray[shipping] = reading.read_toygraphs(1);
            TSPalgorithmsSubmenu(graphsArray[shipping]);
            break;
        }
        default:
            break;
    }
}

void Menu::realWorldGraphs(){
    int option;
    cout << "===============Real World Graphs Submenu===============" << endl;
    cout << "Chose a Toy Graph to work with" << endl;
    cout << "1 - Real-World-Graphs: 1" << endl;
    cout << "2 - Real-World-Graphs: 2" << endl;
    cout << "3 - Real-World-Graphs: 3" << endl;
    cin >> option;

    switch (option) {
        case 1: {
            if(graphsArray[RW1]  == nullptr) graphsArray[RW1] = reading.read_realgraphs(1);
            TSPalgorithmsSubmenu(graphsArray[RW1]);
            break;
        }
        case 2: {
            if(graphsArray[RW2] == nullptr) graphsArray[RW2] = reading.read_realgraphs(2);
            TSPalgorithmsSubmenu(graphsArray[RW2]);
            break;
        }
        case 3: {
            if(graphsArray[RW3] == nullptr) graphsArray[RW3] = reading.read_realgraphs(3);
            TSPalgorithmsSubmenu(graphsArray[RW3]);
            break;
        }
        default:
            break;
    }
}

void Menu::fullyConnectedGraphs(){
    int option;
    cout << "===============Fully Connected Graphs Submenu===============" << endl;
    cout << "1 - Extra Fully connected: 25" << endl;
    cout << "2 - Extra Fully connected: 50" << endl;
    cout << "3 - Extra Fully connected: 75" << endl;
    cout << "4 - Extra Fully connected: 100" << endl;
    cout << "5 - Extra Fully connected: 200" << endl;
    cout << "6 - Extra Fully connected: 300" << endl;
    cout << "7 - Extra Fully connected: 400" << endl;
    cout << "8 - Extra Fully connected: 500" << endl;
    cout << "9 - Extra Fully connected: 600" << endl;
    cout << "10 - Extra Fully connected: 700" << endl;
    cout << "11 - Extra Fully connected: 800" << endl;
    cout << "12 - Extra Fully connected: 900" << endl;
    cin >> option;

    switch (option) {
        case 1: {
            if(graphsArray[FC25] == nullptr) graphsArray[FC25] = reading.read_fullyconectedGraphs(25);
            TSPalgorithmsSubmenu(graphsArray[FC25]);
            break;
        }
        case 2: {
            if(graphsArray[FC50] == nullptr) graphsArray[FC50] = reading.read_fullyconectedGraphs(50);
            TSPalgorithmsSubmenu(graphsArray[FC50]);
            break;
        }
        case 3: {
            if(graphsArray[FC75] == nullptr) graphsArray[FC75] = reading.read_fullyconectedGraphs(75);
            TSPalgorithmsSubmenu(graphsArray[FC75]);
            break;
        }
        case 4: {
            if(graphsArray[FC100] == nullptr) graphsArray[FC100] = reading.read_fullyconectedGraphs(100);
            TSPalgorithmsSubmenu(graphsArray[FC100]);
            break;
        }
        case 5: {
            if(graphsArray[FC200] == nullptr) graphsArray[FC200] = reading.read_fullyconectedGraphs(200);
            TSPalgorithmsSubmenu(graphsArray[FC200]);
            break;
        }
        case 6: {
            if(graphsArray[FC300] == nullptr) graphsArray[FC300] = reading.read_fullyconectedGraphs(300);
            TSPalgorithmsSubmenu(graphsArray[FC300]);
            break;
        }
        case 7: {
            if(graphsArray[FC400]== nullptr) graphsArray[FC400] = reading.read_fullyconectedGraphs(400);
            TSPalgorithmsSubmenu(graphsArray[FC400]);
            break;
        }
        case 8: {
            if(graphsArray[FC500] == nullptr) graphsArray[FC500] = reading.read_fullyconectedGraphs(500);
            TSPalgorithmsSubmenu(graphsArray[FC500]);
            break;
        }
        case 9: {
            if(graphsArray[FC600] == nullptr) graphsArray[FC600] = reading.read_fullyconectedGraphs(600);
            TSPalgorithmsSubmenu(graphsArray[FC600]);
            break;
        }
        case 10: {
            if(graphsArray[FC700] == nullptr) graphsArray[FC700] = reading.read_fullyconectedGraphs(700);
            TSPalgorithmsSubmenu(graphsArray[FC700]);
            break;
        }
        case 11: {
            if(graphsArray[FC800] == nullptr) graphsArray[FC800]  = reading.read_fullyconectedGraphs(800);
            TSPalgorithmsSubmenu(graphsArray[FC800] );
            break;
        }
        case 12: {
            if(graphsArray[FC900]  == nullptr) graphsArray[FC900]  = reading.read_fullyconectedGraphs(900);
            TSPalgorithmsSubmenu(graphsArray[FC900]);
            break;
        }
        default:
            break;
    }
}

void Menu::readmenu() {

    int option;
    cout << "===============MAIN MENU===============" << endl;
    cout << "Chose a type of Graph to work with" << endl;
    cout << "1 - Toy Graphs" << endl;
    cout << "2 - Real-World Graphs" << endl;
    cout << "3 - Fully-Connected Graphs" << endl;
    cin >> option;

    switch (option) {
        case 1: {
            toyGraphs();
            break;
        }
        case 2: {
            realWorldGraphs();
            break;
        }
        case 3: {
            fullyConnectedGraphs();
            break;
        }
        default:
            break;
    }
}
