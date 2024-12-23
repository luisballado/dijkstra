// SI _GRAPH_H no esta definido, se define
#ifndef _GRAPH_H
#define _GRAPH_H

#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include "FibonacciHeap.h"

//#include "EdgeInfo.h"

// VALOR MUY GRANDE ¿?
#define INF 0x3f3f3f3f 

class Graph {

  
private:
  int numNodes;
  int numEdges;
  int nodeExpl;
  std::vector<std::vector<std::pair<int,int>>> adjList;
  void split(std::string line, std::vector<int> &res);

public:
  Graph();
  ~Graph();
  void loadGraph(std::istream &input);
  int getStartNode();
  int getNumNodes();
  void printGraph();
  std::vector<int> dijkstra(int start);
  std::vector<int> dijkstraMinHeap(int start); 
  std::vector<int> dijkstraFibHeap(int start);
};

#endif // _GRAPH_H
