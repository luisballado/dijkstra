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

//#include "EdgeInfo.h"

// VALOR MUY GRANDE ¿?
#define INF 0x3f3f3f3f 

class Graph {

  
private:
  int numNodes;
  int numEdges;

  std::vector<std::vector<int>> adjList; //por que es un no dirigido
  void split(std::string line, std::vector<int> &res);

public:
  Graph();
  ~Graph();
  void loadGraph(std::istream &input);
  void printGraph();
  void dijkstra();
  void dijkstraMinHeap();
  void dijkstraFibHeap();
};

#endif // _GRAPH_H
