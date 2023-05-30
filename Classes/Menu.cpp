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
        if (i != n - 1) cout << path[i] << "-> ";
        else cout << path[i] << endl;
    }
    cout << "TSP Backtrack Cost: " << minDist << endl;
    graph->resetNodes();
    return minDist;
}

void Menu::TSPtriangularInequality(Graph *graph) {
    graph->graphreport.distTriangular = graph->primMST();
    graph->resetNodes();
}

void Menu::TSPnearestNeighbor(Graph *graph){
    double minimum = numeric_limits<double>::infinity();
    double res;
    for(int i = 0; i < graph->nodesMAP.size(); i++){
        res = graph->nearestNeightbour(to_string(i));
        //cout << "subtotal: " <<res <<endl <<endl;
        minimum = min(res, minimum);
    }
    cout << "the minimum of all the neighbors is: " << minimum <<endl <<endl;

    graph->resetNodes();
}

double Menu::printElapsedTime(timeval start, timeval end){
    double elapsed =  (end.tv_sec - start.tv_sec) * 1e6;
    elapsed = (elapsed + (end.tv_usec -
                   start.tv_usec)) * 1e-6;
    cout << "The elapsed time was: " << fixed <<elapsed <<setprecision(6) <<"seconds. "<< endl;
    return elapsed;
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
            //graphreport.distBacktrack= TSPbacktrack(graph);
            graph->graphreport.distBacktrack = TSPbacktrack(graph);

            gettimeofday(&end, NULL);
            //graphreport.elapsedBacktrack = printElapsedTime(start, end);
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
            struct timeval start, end;
            gettimeofday(&start, NULL);
            ios_base::sync_with_stdio(false);
            TSPtriangularInequality(graph);

            gettimeofday(&end, NULL);
            //graphreport.elapsedTriangular = printElapsedTime(start, end);
            graph->graphreport.elapsedTriangular = printElapsedTime(start, end);

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
            printElapsedTime(start, end);

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
            /*
            if(graphreport.elapsedTriangular == 0 || graphreport.elapsedBacktrack == 0 || graphreport.distTriangular == 0 || graphreport.distBacktrack == 0){
                cout << "You don't have the data yet, remember that you need to run both algorithms to get the full data. \n";
                TSPalgorithmsSubmenu(graph);
            }
             */
            if(graph->graphreport.elapsedTriangular == 0 || graph->graphreport.elapsedBacktrack == 0 || graph->graphreport.distTriangular == 0 || graph->graphreport.distBacktrack == 0){
                cout << "You don't have the data yet, remember that you need to run both algorithms to get the full data. \n";
                TSPalgorithmsSubmenu(graph);
            }

            double ratioTime, ratioDist;
            ratioTime =  (graph->graphreport.elapsedTriangular / graph->graphreport.elapsedBacktrack) * 100 ;
            ratioDist = ((graph->graphreport.distTriangular / graph->graphreport.distBacktrack) * 100) - 100 ;
            cout << "the triangular aproximation takes "<< ratioTime <<"% of the time it takes the backtracking algorithm  \n" ;
            cout << "the triangular aproximation distance is "<< ratioDist <<"% longer than the backtracking algorithm distance\n \n" ;

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
            if (graphsArray[stadiums] == nullptr) graphsArray[stadiums] = reading.read_stadium_graph();
            TSPalgorithmsSubmenu(graphsArray[stadiums]);
            break;
        }
        case 3: {
            if (graphsArray[shipping] == nullptr) graphsArray[shipping] = reading.read_shiping_graph();
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
            if(graphsArray[RW1]  == nullptr) graphsArray[RW1] = reading.read_realgraph1();
            TSPalgorithmsSubmenu(graphsArray[RW1]);
            break;
        }
        case 2: {
            if(graphsArray[RW2] == nullptr) graphsArray[RW2] = reading.read_realgraph2();
            TSPalgorithmsSubmenu(graphsArray[RW2]);
            break;
        }
        case 3: {
            if(graphsArray[RW3] == nullptr) graphsArray[RW3] = reading.read_realgraph3();
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
            if(graphsArray[FC25] == nullptr) graphsArray[FC25] = reading.read_fullyconected25();
            TSPalgorithmsSubmenu(graphsArray[FC25]);
            break;
        }
        case 2: {
            if(graphsArray[FC50] == nullptr) graphsArray[FC50] = reading.read_fullyconected50();
            TSPalgorithmsSubmenu(graphsArray[FC50]);
            break;
        }
        case 3: {
            if(graphsArray[FC75] == nullptr) graphsArray[FC75] = reading.read_fullyconected75();
            TSPalgorithmsSubmenu(graphsArray[FC75]);
            break;
        }
        case 4: {
            if(graphsArray[FC100] == nullptr) graphsArray[FC100] = reading.read_fullyconected100();
            TSPalgorithmsSubmenu(graphsArray[FC100]);
            break;
        }
        case 5: {
            if(graphsArray[FC200] == nullptr) graphsArray[FC200] = reading.read_fullyconected200();
            TSPalgorithmsSubmenu(graphsArray[FC200]);
            break;
        }
        case 6: {
            if(graphsArray[FC300] == nullptr) graphsArray[FC300] = reading.read_fullyconected300();
            TSPalgorithmsSubmenu(graphsArray[FC300]);
            break;
        }
        case 7: {
            if(graphsArray[FC400]== nullptr) graphsArray[FC400] = reading.read_fullyconected400();
            TSPalgorithmsSubmenu(graphsArray[FC400]);
            break;
        }
        case 8: {
            if(graphsArray[FC500] == nullptr) graphsArray[FC500] = reading.read_fullyconected500();
            TSPalgorithmsSubmenu(graphsArray[FC500]);
            break;
        }
        case 9: {
            if(graphsArray[FC600] == nullptr) graphsArray[FC600] = reading.read_fullyconected600();
            TSPalgorithmsSubmenu(graphsArray[FC600]);
            break;
        }
        case 10: {
            if(graphsArray[FC700] == nullptr) graphsArray[FC700] = reading.read_fullyconected700();
            TSPalgorithmsSubmenu(graphsArray[FC700]);
            break;
        }
        case 11: {
            if(graphsArray[FC800] == nullptr) graphsArray[FC800]  = reading.read_fullyconected800();
            TSPalgorithmsSubmenu(graphsArray[FC800] );
            break;
        }
        case 12: {
            if(graphsArray[FC900]  == nullptr) graphsArray[FC900]  = reading.read_fullyconected900();
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
