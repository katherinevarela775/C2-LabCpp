#include <iostream> 
#include <vector> 
#include <ctime> 
#include <algorithm> //Manejo de datos y logica (vectores), azar (random), tiempo (ctime), y control de la consola (conio.h y windows.h).
#include <random> 
#include <conio.h> 
#include <windows.h> 
#include <queue> 
#include <map> 

using namespace std;

const char MURO = '#'; 
const char CAMINO = ' ';
const char RUTA_COMPU = '*';
const char RUTA_USUARIO = '.'; 
const char ENTRADA = 'E';
const char SALIDA = 'S';
const char JUGADOR = 'O';

struct Punto { // Agrupa coordenadas cartesianas y establece una regla de ordenamiento personalizada para que el diccionario pueda organizar y buscar las posiciones del mapa de forma eficiente.
    int x, y; 
    bool operator<(const Punto& p) const { 
        return x < p.x || (x == p.x && y < p.y); 
    } 
}; 

// --- FUNCIONES DE APOYO ---

void limpiarPantalla(int saltos) {  // Desplaza el texto anterior hacia arriba mediante saltos de línea para simular una pantalla limpia.
    for(int i = 0; i < saltos; i++) cout << "\n"; 
}


bool esValido(int x, int y, int filas, int cols) { // Actúa como un "sensor de límites" que impide que cualquier algoritmo acceda a coordenadas inexistentes.
    return (x >= 0 && x < filas && y >= 0 && y < cols); 
}

void imprimirMapa(const vector<vector<char>>& mapa, int filas, int cols, int jug_x = -1, int jug_y = -1) {
    //Esta función es la encargada de transformar la matriz de datos que está en la memoria en algo que nosotros podamos ver en la terminal.
    for (int i = 0; i < filas; i++) { 
        for (int j = 0; j < cols; j++) { 
            if (i == jug_x && j == jug_y) cout << JUGADOR << " "; 
            else cout << mapa[i][j] << " "; // Si no es la posición del jugador, imprime lo que haya en el mapa seguido de un espacio.
        }
        cout << "\n"; 
    }
}