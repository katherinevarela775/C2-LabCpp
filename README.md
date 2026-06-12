# 🌀 El Laberinto Maestro: Generador & Solucionador IA (C++)

Este proyecto es el resultado de unas cuantas horas de código, café y lógica. No es simplemente un generador de mapas procedimentales; es un simulador interactivo de bajo nivel donde puedes intentar ganarle a la máquina o sentarte a ver cómo la Inteligencia Artificial resuelve el caos en milisegundos.

---

## 🛠️ ¿Qué hay bajo el capó? (Arquitectura Algorítmica)

El core del sistema se apoya en dos de los algoritmos de grafos y matrices más importantes de las ciencias de la computación, aplicados con enfoques completamente opuestos:

### 1. La Generación (El caos controlado con DFS)
Para esculpir el laberinto desde una matriz sólida de muros utilizo un algoritmo de **Búsqueda en Profundidad (DFS)** modificado para excavación aleatoria:
* **El mecanismo:** El programa actúa como un "topo" que va abriendo túneles al azar.
* **La matemática:** Al saltar de dos en dos casillas y demoler el muro intermedio, se asegura matemáticamente que siempre existan paredes divisorias y que **nunca se generen ciclos (bucles infinitos)** ni habitaciones aisladas. El mapa siempre tiene solución única.

### 2. La IA Solucionadora (El camino óptimo con BFS)
Para la resolución automática implementé una **Búsqueda en Anchura (BFS)**:
* **El motivo:** A diferencia de DFS, el BFS no busca "una" salida cualquiera; garantiza hallar **el camino más corto posible**.
* **La analogía:** El BFS explora de forma radial, expandiéndose como una mancha de aceite por los pasadizos libres. Lo primero que toca la coordenada de salida es, obligatoriamente, la ruta más eficiente. La reconstrucción del camino se logra mediante un diccionario inverso de coordenadas `std::map<Punto, Punto>`.

---

## 🕹️ Características Principales & Extras

* **🎮 Modo Jugador Interactivo:** Conviértete en el explorador. El motor captura las pulsaciones instantáneas del teclado (`W`, `A`, `S`, `D`) a través de `conio.h` sin requerir que presiones Enter, permitiéndote trazar y dejar tu propio rastro de puntos (`.`) en tiempo real. Puedes usar `Q` para rendirte si te quedas atascado.
* **🎬 Animación Fluidas en Consola:** Ver la solución aparecer de golpe es aburrido. El sistema utiliza retrasos de hardware (`Sleep`) y refrescos de pantalla estratégicos para pintar la ruta con asteriscos (`*`), emulando visualmente el proceso de pensamiento de la IA en tiempo real.
* **🛡️ Sistema Anti-Fallos (Robustez de Entrada):** Si intentas inicializar un tablero demasiado pequeño (menor a 5x5) o con dimensiones pares que quebrarían la lógica de saltos del excavador, el código aplica operadores ternarios de corrección automática para normalizar las proporciones y evitar desbordamientos de memoria.

---

## 🧠 Bitácora de Aprendizaje (El verdadero cuello de botella)

Al integrar métricas de rendimiento algorítmico con la biblioteca `<ctime>`, descubrí un detalle técnico fascinante:
La computadora es ridículamente rápida calculando la ruta óptima en la memoria RAM (generalmente le toma alrededor de **0.001 segundos**). Sin embargo, lo que realmente "frena" al programa es el renderizado visual; es decir, tener que imprimir los caracteres emoji y limpiar la consola. 

Este proyecto fue un recordatorio práctico excelente de que, en el software real, **la interfaz gráfica (I/O) suele ser el verdadero cuello de botella**, y no la lógica matemática del backend.

---

## ⚙️ Requisitos y Ejecución

El código está escrito en C++ estándar y utiliza librerías nativas de Windows para el control de la consola (`windows.h` y `conio.h`).

1. Compila el archivo principal con cualquier compilador de C++ (por ejemplo, GCC):
   ```bash
   g++ laberinto.cpp -o laberinto.exe
   ```
2. Ejecuta el archivo binario generado:
   ```bash
   ./laberinto.exe
   ```
