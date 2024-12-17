#include "Graph.h"
#include <iostream>
#include <sstream>

//compilar 
// g++ main.cpp Graph.cpp -o programa

int main() {

  Graph g;
  
  std::stringstream inputInfo;
  inputInfo << std::cin.rdbuf();

  g.loadGraph(inputInfo); // cargar grafo
  g.printGraph();         //imprimir grafo

    
  //TODO: contar tiempo1 aqui
  //g.dijkstraMinHeap();

  //TODO: contar tiempo2 aqui
  //g.dijkstraFibHeap();
  
  return 0;
}
