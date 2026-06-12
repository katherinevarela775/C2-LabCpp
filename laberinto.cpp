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

// --- NUEVA BÚSQUEDA BFS ---


vector<Punto> encontrarRutaBFS(int filas, int cols, const vector<vector<char>>& mapa) { 
// Utiliza el algoritmo BFS para explorar el mapa de forma radial, garantizando el hallazgo del camino más corto desde el inicio hasta la salida mediante una cola de exploración y un registro de movimientos previos.
    queue<Punto> queue; 
    queue.push({0, 0}); 
    
    map<Punto, Punto> padres; // Este diccionario guarda pares de coord. {Hijo, Padre}
    vector<vector<bool>> visitado(filas, vector<bool>(cols, false)); // Una matriz llena de interrup. para evitar bucles
    visitado[0][0] = true; 

    int dx[] = {1, -1, 0, 0}; 
    int dy[] = {0, 0, 1, -1}; 
    bool encontrado = false; 
    while (!queue.empty()) { 
        Punto punt_actual = queue.front();
        queue.pop(); 

        if (punt_actual.x == filas - 1 && punt_actual.y == cols - 1) { 
            encontrado = true; 
            break; 
        }

        for (int i = 0; i < 4; i++) { 
            int nx = punt_actual.x + dx[i]; 
            int ny = punt_actual.y + dy[i]; 

            if (esValido(nx, ny, filas, cols) && mapa[nx][ny] != MURO && !visitado[nx][ny]) {
                visitado[nx][ny] = true;  
                padres[{nx, ny}] = punt_actual; 
                queue.push({nx, ny}); 
            }
        }
    }

    vector<Punto> ruta; // Esta sección reconstruye el camino óptimo rastreando hacia atrás las coordenadas desde la salida hasta el inicio mediante el diccionario de "padres", invirtiendo finalmente la lista para entregar la ruta en el orden correcto de avance.
    if (encontrado) { 
        Punto coord_expl = {filas - 1, cols - 1}; 
        while (!(coord_expl.x == 0 && coord_expl.y == 0)) { 
            ruta.push_back(coord_expl); 
            coord_expl = padres[coord_expl]; 
        }
        ruta.push_back({0, 0}); 
        reverse(ruta.begin(), ruta.end()); 
    }
    return ruta; 
}

void animarCaminoCorrecto(vector<vector<char>>& mapa, const vector<Punto>& ruta, int filas, int cols) { //se encarga de la salida visual de la solución.
    for (int i = 0; i < ruta.size(); i++) { 
        int rx = ruta[i].x; //Extrae la fila y columna del punto actual en la ruta.
        int ry = ruta[i].y;

        if (mapa[rx][ry] != ENTRADA && mapa[rx][ry] != SALIDA) { 
            mapa[rx][ry] = RUTA_COMPU;
        }

        limpiarPantalla(25); //Empuja el laberinto anterior hacia arriba para que el nuevo aparezca en el mismo lugar.
        cout << "--- MOSTRANDO CAMINO CORRECTO ---" << endl;
        imprimirMapa(mapa, filas, cols); //Dibuja el laberinto actualizado (ahora con un nuevo asterisco pintado).
        Sleep(300); //Detiene el programa por 300 milisegundos
    }
}

// --- MODO MANUAL ---

void modoManual(vector<vector<char>>& mapa, int filas, int cols) { //"Es la parte del código que convierte tus teclas (W, A, S, D) en movimientos del personaje dentro del laberinto, cuidando que no atravieses paredes y dibujando el camino que vas dejando atrás."
    int jug_x = 0, jug_y = 0; 
    while (true) { 
        limpiarPantalla(30); 
        cout << "--- MODO MANUAL --- (W,A,S,D | Q para Rendirse)" << endl;
        imprimirMapa(mapa, filas, cols, jug_x, jug_y); 

        if (jug_x == filas - 1 && jug_y == cols - 1) { 
            cout << "\n¡Llegaste a la salida! Victoria." << endl;
            break; 
        }

        char tecla = _getch();
        if (tecla == 'q' || tecla == 'Q') { 
            cout << "\nTe has rendido. Calculando ruta optima...\n";
            break; 
        }

        int nx = jug_x, ny = jug_y; // Creamos coordenadas "proyectadas"
        if (tecla == 'w' || tecla == 'W') nx--; // Arriba
        else if (tecla == 's' || tecla == 'S') nx++; // Abajo
        else if (tecla == 'a' || tecla == 'A') ny--; // Izquierda
        else if (tecla == 'd' || tecla == 'D') ny++; // Derecha

        if (esValido(nx, ny, filas, cols) && mapa[nx][ny] != MURO) {  
            if (mapa[jug_x][jug_y] != ENTRADA) mapa[jug_x][jug_y] = RUTA_USUARIO; 
            jug_x = nx; jug_y = ny; 
        }
    }
}

// --- MAIN ---

int main() { // Esta es la función principal del programa, se encarga de pedirte el tamaño del laberinto, generarlo automáticamente, dejarte jugar y finalmente mostrarte cómo la computadora lo resuelve en tiempo récord.
    int fila, columna; 
    cout << "========================================" << endl;
    cout << "    GENERADOR DE LABERINTOS MAESTRO      " << endl;
    cout << "========================================" << endl;
    cout << "Ingrese el num. de filas: "; cin >> fila;
    cout << "Ingrese el num. de columnas: "; cin >> columna; // Detiene el programa para que escribas un número. Es la contraparte de cout.

    int filasT = (fila < 5) ? 5 : (fila % 2 == 0 ? fila + 1 : fila); 
    int colsT = (columna < 5) ? 5 : (columna % 2 == 0 ? columna + 1 : columna); //Si el tablero tuviera dimensiones pares, el explorador se "estrellaría" contra el borde exterior al intentar hacer su último salto de 2 casillas, dejando el laberinto sin una pared de cierre en uno de los lados.

    vector<vector<char>> mapa(filasT, vector<char>(colsT, MURO));
    
    generar(0, 0, mapa, filasT, colsT); 
    mapa[0][0] = ENTRADA;
    mapa[filasT-1][colsT-1] = SALIDA; 

    cout << "\nPresiona una tecla para jugar..."; _getch();
    modoManual(mapa, filasT, colsT); 
    
    cout << "\nPresiona una tecla para ver la solucion directa..."; _getch(); 

    for(int i=0; i<filasT; i++) 
        for(int j=0; j<colsT; j++)
            if(mapa[i][j] == RUTA_USUARIO) mapa[i][j] = CAMINO;

    clock_t inicio = clock(); 
    vector<Punto> ruta = encontrarRutaBFS(filasT, colsT, mapa); 
    animarCaminoCorrecto(mapa, ruta, filasT, colsT); 
    clock_t fin = clock(); 

    cout << "\n--- PROCESO TERMINADO ---" << endl;
    cout << "Tiempo de calculo: " << (double)(fin - inicio) / CLOCKS_PER_SEC << " segundos." << endl; 
    cout << "\nPresiona cualquier tecla para cerrar el juego..." << endl; 
    _getch();

    return 0;} 