#include <iostream>
#include <vector>
#include <queue>
#include <limits>

//ejemplo con min-heap

// Algoritmo de Dijkstra usando priority_queue como min heap
/*
std::vector<int> dijkstra(std::vector<std::vector<std::pair<int,int>>>& graph, int start) {
  int n = graph.size();
  std::vector<int> distances(n, std::numeric_limits<int>::max()); // Vector de distancias
  distances[start] = 0; // La distancia al nodo inicial es 0
  
  // Priority queue configurada como min heap (distancia, nodo)
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> min_heap;
  min_heap.emplace(0, start);
  
  while (!min_heap.empty()) {
    auto [current_distance, current_node] = min_heap.top();
    min_heap.pop();
    
    // Si la distancia actual es mayor a la almacenada, ignorar
    if (current_distance > distances[current_node]) {
      continue;
    }
    
    // Explorar los vecinos
    for (const auto& neighbor : graph[current_node]) {
      int v = neighbor.first;
      int weight = neighbor.second;
      
      // Relajación de la arista
      if (distances[current_node] + weight < distances[v]) {
	distances[v] = distances[current_node] + weight;
	min_heap.emplace(distances[v], v);
      }
    }
  }
  
  return distances;
}
*/

int main() {
  // Crear un grafo dirigido con pesos
  int n, m; // n = cantidad de nodos, m = cantidad de aristas
  std::cout << "Introduce el número de nodos y aristas: ";
  std::cin >> n >> m;
  
  std::vector<std::vector<std::pair<int,int>>> graph(n);
  
  std::cout << "Introduce las aristas (origen destino peso):\n";
  for (int i = 0; i < m; ++i) {
    int from, to, weight;
    std::cin >> from >> to >> weight;
    graph[from].push_back({to, weight});
  }
  
  int start;
  std::cout << "Introduce el nodo de inicio: ";
  std::cin >> start;
  
  // Ejecutar Dijkstra
  std::vector<int> distances = dijkstra(graph, start);
  
  // Imprimir las distancias mínimas
  std::cout << "Distancias desde el nodo " << start << ":\n";
  for (int i = 0; i < n; ++i) {
    if (distances[i] == std::numeric_limits<int>::max()) {
      std::cout << "Nodo " << i << ": Inalcanzable\n";
    } else {
      std::cout << "Nodo " << i << ": " << distances[i] << "\n";
    }
  }
  
  return 0;
}
