import random

def generar_grafo():
    print("--- Generador de Grafos ---")
    # Solicitar al usuario el número de nodos y aristas
    num_nodos = int(input("Ingrese el número de nodos: "))
    num_aristas = int(input("Ingrese el número de aristas: "))
    name = input("Nombre archivo")
    
    # Validar que el número de aristas no exceda las combinaciones posibles de nodos
    if num_aristas > (num_nodos * (num_nodos - 1)) // 2:
        print("Error: Demasiadas aristas para el número de nodos.")
        return

    # Abrir un archivo para escribir el resultado
    with open(name, "w") as file:
        file.write(f"{num_nodos} {num_aristas}\n")
        print("\nEstructura del Grafo:")
        print(f"{num_nodos} {num_aristas}")
        file.write(f"{num_nodos} {num_aristas}\n")

        aristas = set()

        # Generar las aristas de manera aleatoria
        while len(aristas) < num_aristas:
            nodo1 = random.randint(1, num_nodos)
            nodo2 = random.randint(1, num_nodos)
            peso = random.randint(1, 100)  # Peso aleatorio entre 1 y 100

            # Evitar lazos y duplicados (nodo1, nodo2) == (nodo2, nodo1)
            if nodo1 != nodo2:
                arista = tuple(sorted([nodo1, nodo2]))  # Ordena los nodos para evitar duplicados
                if arista not in aristas:
                    aristas.add(arista)
                    linea = f"{arista[0]} {arista[1]} {peso}\n"
                    print(linea.strip())
                    file.write(linea)

if __name__ == "__main__":
    generar_grafo()
