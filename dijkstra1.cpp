#include "Graph.h"
#include <sstream>
#include <vector>
#include <limits>


int main() {
  
  Graph graph;
  std::stringstream inputInfo;
  inputInfo << std::cin.rdbuf();
  
  //cargar grafo
  graph.loadGraph(inputInfo);
  
  
  int start = graph.getStartNode();
  int n = graph.getNumNodes();
  
  // Ejecutar Dijkstra, regresa el resultado de vector de distancias
  std::vector<int> distances = graph.dijkstra(start);
  
  
  // Imprimir las distancias mínimas
  std::cout << "*********NORMAL********" << std::endl;
  std::cout << "Distancias desde el nodo " << start << ":\n";
  for (int i = 1; i < distances.size(); ++i) {
    if (distances[i] == std::numeric_limits<int>::max()) {
      std::cout << "Nodo " << i << ": Inalcanzable\n";
    } else {
      std::cout << "Nodo " << i << ": " << distances[i] << "\n";
    }
  }
  
  
  // Ejecutar Dijkstra
  std::vector<int> distances2 = graph.dijkstraMinHeap(start);
  
  
  // Imprimir las distancias mínimas
  std::cout << "*********minHeap********" << std::endl;
  std::cout << "Distancias desde el nodo " << start << ":\n";
  for (int i = 1; i < distances2.size(); ++i) {
    if (distances2[i] == std::numeric_limits<int>::max()) {
      std::cout << "Nodo " << i << ": Inalcanzable\n";
    } else {
      std::cout << "Nodo " << i << ": " << distances2[i] << "\n";
    }
  }
  
  //FibonacciHeap
  std::cout << "*********FibHeap********" << std::endl;
  
  std::vector<int> distances3 = graph.dijkstraFibHeap(start);
  
  
  // Imprimir las distancias mínimas
  
  std::cout << "Distancias desde el nodo " << start << ":\n";
  
  for (int i = 1; i <= distances3.size(); ++i) {
    if (distances3[i] == std::numeric_limits<int>::max()) {
      std::cout << "Nodo " << i << ": Inalcanzable\n";
    } else {
      std::cout << "Nodo " << i << ": " << distances3[i] << "\n";
    }
  }
  
  return 0;
}
