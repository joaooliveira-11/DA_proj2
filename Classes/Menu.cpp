#include "Menu.h"
#include <bits/stdc++.h>
#include <sys/time.h>

Reading reading = Reading();

Graph *tourismgraph;
Graph *stadiumsgraph;
Graph *shippinggraph;

Graph *RWgraph1;
Graph *RWgraph2;
Graph *RWgraph3;

Graph *FCgraph25;
Graph *FCgraph50;
Graph *FCgraph75;
Graph *FCgraph100;
Graph *FCgraph200;
Graph *FCgraph300;
Graph *FCgraph400;
Graph *FCgraph500;
Graph *FCgraph600;
Graph *FCgraph700;
Graph *FCgraph800;
Graph *FCgraph900;

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
    //graphreport.distTriangular = graph->primMST();
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

void Menu::readmenu() {

    int option;
    cout << "===============MAIN MENU===============" << endl;
    cout << "Chose a type of Graph to work with" << endl;
    cout << "1 - Toy-Graphs: tourism" << endl;
    cout << "2 - Toy-Graphs: stadiums" << endl;
    cout << "3 - Toy-Graphs: shipping" << endl;

    cout << "4 - Extra Fully connected: 25" << endl;
    cout << "5 - Extra Fully connected: 50" << endl;
    cout << "6 - Extra Fully connected: 75" << endl;
    cout << "7 - Extra Fully connected: 100" << endl;
    cout << "8 - Extra Fully connected: 200" << endl;
    cout << "9 - Extra Fully connected: 300" << endl;
    cout << "10 - Extra Fully connected: 400" << endl;
    cout << "11 - Extra Fully connected: 500" << endl;
    cout << "12 - Extra Fully connected: 600" << endl;
    cout << "13 - Extra Fully connected: 700" << endl;
    cout << "14 - Extra Fully connected: 800" << endl;
    cout << "15 - Extra Fully connected: 900" << endl;

    cout << "16 - Real-World-Graphs: 1" << endl;
    cout << "17 - Real-World-Graphs: 2" << endl;
    cout << "18 - Real-World-Graphs: 3" << endl;
    cin >> option;

    switch (option) {
        case 1: {
            if(tourismgraph == nullptr) tourismgraph = reading.read_tourism_graph();
            TSPalgorithmsSubmenu(tourismgraph);
            break;
        }
        case 2: {
            if(stadiumsgraph == nullptr) stadiumsgraph = reading.read_stadium_graph();
            TSPalgorithmsSubmenu(stadiumsgraph);
            break;

        }
        case 3: {
            if(shippinggraph == nullptr) shippinggraph = reading.read_shiping_graph();
            TSPalgorithmsSubmenu(shippinggraph);
            break;
        }
        case 4: {
            if(FCgraph25 == nullptr) FCgraph25 = reading.read_fullyconected25();
            TSPalgorithmsSubmenu(FCgraph25);
            break;
        }
        case 5: {
            if(FCgraph50 == nullptr) FCgraph50 = reading.read_fullyconected50();
            TSPalgorithmsSubmenu(FCgraph50);
            break;
        }
        case 6: {
            if(FCgraph75 == nullptr) FCgraph75 = reading.read_fullyconected75();
            TSPalgorithmsSubmenu(FCgraph75);
            break;

        }
        case 7: {
            if(FCgraph100 == nullptr) FCgraph100 = reading.read_fullyconected100();
            TSPalgorithmsSubmenu(FCgraph100);
            break;
        }
        case 8: {
            if(FCgraph200 == nullptr) FCgraph200 = reading.read_fullyconected200();
            TSPalgorithmsSubmenu(FCgraph200);
            break;

        }
        case 9: {
            if(FCgraph300 == nullptr) FCgraph300 = reading.read_fullyconected300();
            TSPalgorithmsSubmenu(FCgraph300);
            break;

        }
        case 10: {
            if(FCgraph400 == nullptr) FCgraph400 = reading.read_fullyconected400();
            TSPalgorithmsSubmenu(FCgraph400);
            break;

        }
        case 11: {
            if(FCgraph500 == nullptr) FCgraph500 = reading.read_fullyconected500();
            TSPalgorithmsSubmenu(FCgraph500);
            break;

        }
        case 12: {
            if(FCgraph600 == nullptr) FCgraph600 = reading.read_fullyconected600();
            TSPalgorithmsSubmenu(FCgraph600);
            break;

        }
        case 13: {
            if(FCgraph700 == nullptr) FCgraph700 = reading.read_fullyconected700();
            TSPalgorithmsSubmenu(FCgraph700);
            break;

        }
        case 14: {
            if(FCgraph800 == nullptr) FCgraph800 = reading.read_fullyconected800();
            TSPalgorithmsSubmenu(FCgraph800);
            break;

        }
        case 15: {
            if(FCgraph900 == nullptr) FCgraph900 = reading.read_fullyconected900();
            TSPalgorithmsSubmenu(FCgraph900);
            break;

        }
        case 16: {
            if(RWgraph1 == nullptr) RWgraph1 = reading.read_realgraph1();
            TSPalgorithmsSubmenu(RWgraph1);
            break;
        }
        case 17: {
            if(RWgraph2 == nullptr) RWgraph2 = reading.read_realgraph2();
            TSPalgorithmsSubmenu(RWgraph2);
            break;
        }
        case 18: {
            if(RWgraph3 == nullptr) RWgraph3 = reading.read_realgraph3();
            TSPalgorithmsSubmenu(RWgraph3);
            break;
        }
        default:
            break;
    }

}
