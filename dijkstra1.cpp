#include <iostream>
#include <vector>
#include <queue>
#include <limits>

//implementacion normal de dijkstra con cola de prioridad

// Algoritmo principal de Dijkstra
std::vector<int> dijkstra(const std::vector<std::vector<std::pair<int,int>>>& graph, int start) {

  int n = graph.size(); //tamaño del grafo
  
  std::vector<int> distances(n, std::numeric_limits<int>::max()); // Vector de distancias
  distances[start] = 0; // La distancia al nodo inicial es 0
  
  // Cola de prioridad para procesar los nodos (distancia, nodo)
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
  pq.emplace(0, start);
  
  while (!pq.empty()) {
    auto [current_distance, current_node] = pq.top();
    pq.pop();
    
    // Explorar los vecinos
    for (const auto& neighbor : graph[current_node]) {
      int v = neighbor.first;
      int weight = neighbor.second;
      
      // Relajación de la arista
      if (distances[current_node] + weight < distances[v]) {
	distances[v] = distances[current_node] + weight;
	pq.emplace(distances[v], v);
      }
    }
  }
  
  return distances;
}

int main() {
  // Crear un grafo dirigido con pesos
  int n, m; // n = cantidad de nodos, m = cantidad de aristas
  //cout << "Introduce el número de nodos y aristas: ";
  std::cin >> n >> m;

  //par es hacia donde - peso
  std::vector<std::vector<std::pair<int,int>>> graph(n);
  
  //cout << "Introduce las aristas (origen destino peso):\n";
  for (int i = 0; i < m; ++i) {
    int from, to, weight;
    std::cin >> from >> to >> weight;
    graph[from].push_back({to, weight});
  }

  int start;
  //cout << "Introduce el nodo de inicio: ";
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
