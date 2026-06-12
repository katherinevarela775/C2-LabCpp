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

// --- LÓGICA DE GENERACIÓN ---

void generar(int x, int y, vector<vector<char>>& mapa, int filas, int cols) { // Esta funcion es la que utiliza el DFS
// Crea el laberinto mediante un algoritmo de excavación aleatoria. 
// Utiliza recursividad para avanzar por el mapa saltando de dos en dos casillas, rompiendo los muros intermedios para garantizar que siempre exista un camino conectado y sin ciclos entre cualquier punto del tablero.
    mapa[x][y] = CAMINO; 
    int dx[] = {0, 0, 2, -2}; 
    int dy[] = {2, -2, 0, 0};
    vector<int> dir = {0, 1, 2, 3}; 
    static mt19937 rng(time(NULL)); 
    shuffle(dir.begin(), dir.end(), rng);

    for (int i = 0; i < 4; i++) { // Este for intenta ir en las 4 direcciones que mezclamos antes.
        int nx = x + dx[dir[i]];  
        int ny = y + dy[dir[i]];
        if (esValido(nx, ny, filas, cols) && mapa[nx][ny] == MURO) { 
            mapa[x + dx[dir[i]] / 2][y + dy[dir[i]] / 2] = CAMINO; 
            generar(nx, ny, mapa, filas, cols); // Aquí ocurre la recursividad. La función se detiene y abre una "sub-función" para seguir excavando desde la nueva casilla. Cuando ese camino se bloquea, la función original retoma donde se quedó y prueba la siguiente dirección del for.
        }
    } 
}
