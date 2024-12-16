#include <iostream>
#include <vector>
#include <queue>
#include <limits>

//ejemplo con min-heap

using namespace std;

// Definir una estructura para representar las aristas del grafo
struct Edge {
    int to;      // Nodo de destino
    int weight;  // Peso de la arista
};

// Definir un alias para la lista de adyacencia
using Graph = vector<vector<Edge>>;

// Algoritmo de Dijkstra usando priority_queue como min heap
vector<int> dijkstra(const Graph& graph, int start) {
    int n = graph.size();
    vector<int> distances(n, numeric_limits<int>::max()); // Vector de distancias
    distances[start] = 0; // La distancia al nodo inicial es 0

    // Priority queue configurada como min heap (distancia, nodo)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;
    min_heap.emplace(0, start);

    while (!min_heap.empty()) {
        auto [current_distance, current_node] = min_heap.top();
        min_heap.pop();

        // Si la distancia actual es mayor a la almacenada, ignorar
        if (current_distance > distances[current_node]) {
            continue;
        }

        // Explorar los vecinos
        for (const auto& edge : graph[current_node]) {
            int neighbor = edge.to;
            int weight = edge.weight;

            // Relajación de la arista
            if (distances[current_node] + weight < distances[neighbor]) {
                distances[neighbor] = distances[current_node] + weight;
                min_heap.emplace(distances[neighbor], neighbor);
            }
        }
    }

    return distances;
}

int main() {
    // Crear un grafo dirigido con pesos
    int n, m; // n = cantidad de nodos, m = cantidad de aristas
    cout << "Introduce el número de nodos y aristas: ";
    cin >> n >> m;

    Graph graph(n);

    cout << "Introduce las aristas (origen destino peso):\n";
    for (int i = 0; i < m; ++i) {
        int from, to, weight;
        cin >> from >> to >> weight;
        graph[from].push_back({to, weight});
    }

    int start;
    cout << "Introduce el nodo de inicio: ";
    cin >> start;

    // Ejecutar Dijkstra
    vector<int> distances = dijkstra(graph, start);

    // Imprimir las distancias mínimas
    cout << "Distancias desde el nodo " << start << ":\n";
    for (int i = 0; i < n; ++i) {
        if (distances[i] == numeric_limits<int>::max()) {
            cout << "Nodo " << i << ": Inalcanzable\n";
        } else {
            cout << "Nodo " << i << ": " << distances[i] << "\n";
        }
    }

    return 0;
}