🌀 El Laberinto Maestro:
Este es el resultado de unas cuantas horas de código, café y lógica. 
No es solo un generador de mapas; es un reto donde puedes intentar ganarle a la máquina o sentarte a ver cómo ella resuelve el caos en milisegundos.

¿Qué hay bajo el capó?

La Generación (El caos controlado): Para crear el laberinto usé un algoritmo de DFS (Búsqueda en Profundidad). Básicamente, el programa actúa como un topo que va excavando túneles al azar. Lo genial es que, al saltar de dos en dos, me aseguro de que siempre haya paredes entre los caminos y que nunca te quedes atrapado en un laberinto sin salida.
La IA (El cerebro): Para la resolución automática me fui por un BFS (Búsqueda en Anchura). ¿Por qué? Porque no quería que la máquina solo encontrara "una" salida, quería que encontrara la mejor. El BFS explora como una mancha de aceite que se expande: lo primero que toca la salida es, sí o sí, el camino más corto.

Cosas que aprendí (y que me sorprendieron): 

Al medir los tiempos de ejecución, me di cuenta de algo gracioso: la computadora es ridículamente rápida calculando la ruta (le toma como $0.001$ segundos), pero lo que realmente la "frena" es mostrarnos los dibujitos en la consola. Es un buen recordatorio de que, a veces, la interfaz es el verdadero cuello de botella, no la lógica.

Los "Extras" que le puse

Modo Jugador: No quería que fuera solo ver texto. Puedes moverte con W, A, S, D y dejar tu propio rastro de puntos.  
Animación en vivo: Ver la solución aparecer de golpe es aburrido. Le puse un pequeño retraso para que puedas ver cómo la IA va "marcando" su camino con asteriscos, casi como si estuviera pensando en tiempo real.
Antifallos: Si intentas crear un laberinto muy chiquito o con números pares que romperían la lógica, el código lo corrige solito para que nada explote
