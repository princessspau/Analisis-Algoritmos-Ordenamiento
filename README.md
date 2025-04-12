# Analisis-Algoritmos-Ordenamiento
Este proyecto evalúa el desempeño de 7 algoritmos de ordenamiento clásicos realizando pruebas con arreglos de distintos tamaños. A través de estas pruebas, se registran los tiempos de ejecución para comparar su eficiencia y entender cómo se comportan en diferentes escenarios.

Los métodos de ordenación utilizados son:

  - Inserción
  - Burbuja 
  - Selección
  - Mezcla
  - Quick Sort
  - Montículos
  - Shell


El programa realiza un análisis exhaustivo del rendimiento de siete algoritmos clásicos de ordenamiento, evaluando su comportamiento con arreglos de diferentes tamaños, que varían de 10 a 1000 elementos en incrementos de 10. Para cada tamaño, genera arreglos aleatorios y ejecuta 1000 pruebas, garantizando resultados estadísticamente confiables.

Utiliza la librería chrono de C++ para medir los tiempos de ejecución con alta precisión en nanosegundos. Los algoritmos analizados incluyen: Inserción, Burbuja, Selección, Shell, Merge Sort, Quick Sort y Heap Sort, cada uno con características únicas en términos de complejidad y comportamiento.

Para asegurar condiciones de prueba equivalentes, cada algoritmo se ejecuta sobre copias idénticas de los arreglos generados. Al finalizar, el programa genera archivos CSV con los resultados detallados, además de un archivo consolidado que presenta los promedios de los tiempos de ejecución. Esto permite un análisis claro de cómo escala el rendimiento de cada algoritmo según el tamaño del arreglo y facilita la comparación de su eficiencia relativa.

El código está implementado en C++, optimizado para obtener mediciones precisas y emplea funciones "wrapper" para adaptar los algoritmos recursivos a una interfaz uniforme. El objetivo principal es demostrar, de manera experimental, las diferencias de rendimiento entre enfoques de ordenamiento, desde métodos cuadráticos hasta los más eficientes con complejidad logarítmica. Los datos obtenidos ofrecen una visión práctica y concreta sobre el comportamiento de estos algoritmos en diferentes escenarios.


## Requisitos del Sistema
- **Sistema Operativo**: Windows 10/11, Linux (Ubuntu 20.04+), macOS (Big Sur+)
- **Compilador**: g++ o compatible con C++11
- **RAM**: 4GB mínimo (8GB recomendado para mayor comodidad)
- **Espacio en disco**: 10MB mínimo
- **CPU**: x86_64 architecture (Intel/AMD)

## Compilación y Ejecución

**Clonar el repositorio**:
```bash
git clone https://github.com/princessspau/Analisis-Algoritmos-Ordenamiento.git
```
**Cambio de directorio**:
```bash
cd Analisis-Algoritmos-Ordenamiento
```
**Compilar**:
```bash
g++ -std=c++11 ordenamientos_algoritmo_nuevo.cpp
```
**Ejecución**:
```bash
.\ordenamientos_algoritmo_nuevo.cpp
```

# Descripción de Algoritmos de Ordenamiento

## Inserción
El algoritmo de inserción recorre el arreglo y construye un subconjunto ordenado de elementos al mover cada elemento actual hacia atrás hasta encontrar su posición correcta. Es adecuado para conjuntos de datos pequeños o casi ordenados, pero su eficiencia disminuye con conjuntos de datos grandes debido a su complejidad cuadrática.


## Burbuja
El método de la burbuja compara pares de elementos adyacentes y los intercambia si están en el orden incorrecto, "burbujando" los elementos más grandes hacia el final del arreglo. Aunque es simple y fácil de entender, es uno de los algoritmos menos eficientes para grandes conjuntos de datos.


## Selección
Este algoritmo encuentra el elemento más pequeño (o más grande) en cada iteración y lo coloca en su posición correcta al principio del arreglo. Su principal ventaja es que realiza un número fijo de intercambios, pero puede ser más lento en comparación con otros métodos debido a su alta cantidad de comparaciones.



## Shell Sort
Shell Sort es una extensión del método de inserción que ordena elementos distantes entre sí en cada iteración, reduciendo progresivamente el intervalo hasta alcanzar un ordenamiento final. Su rendimiento depende de la secuencia de incrementos utilizada y suele ser más eficiente que la inserción para arreglos más grandes.



## Merge Sort
Merge Sort utiliza el enfoque divide y vencerás para dividir recursivamente el arreglo en mitades, ordenar cada mitad y luego combinarlas en un solo arreglo ordenado. Este algoritmo garantiza una complejidad O(n log n), lo que lo hace altamente eficiente para grandes volúmenes de datos.

**Funciones auxiliares:**
- División del arreglo: Una función que divide el arreglo en mitades.
- Mezcla: Una función que combina dos mitades ordenadas en un solo arreglo ordenado.

### Detalles de la función Mezcla:
La función `Mezcla` toma dos subarreglos ordenados y los fusiona en un único subarreglo ordenado. 
1. Copia los elementos de las mitades en arreglos temporales.
2. Compara los elementos de los arreglos temporales y los coloca en orden en el arreglo principal.
3. Si quedan elementos en cualquiera de los subarreglos, se copian directamente al arreglo principal.

## Quick Sort
Quick Sort selecciona un pivote y reorganiza los elementos de tal manera que los menores queden a la izquierda y los mayores a la derecha. Luego aplica este proceso recursivamente a las subparticiones. Es muy rápido en promedio, pero su eficiencia puede degradarse si no se elige el pivote adecuadamente.

**Funciones auxiliares:**
- Partición: Una función que organiza los elementos en torno al pivote.
- Selección del pivote: Una función que elige el pivote para cada iteración, lo que puede influir en la eficiencia general del algoritmo.

### Detalles de la función PARTITION:
La función `PARTITION` organiza el arreglo dividiéndolo según un pivote. 
1. Coloca todos los elementos menores que el pivote a la izquierda y los mayores a la derecha.
2. Utiliza un índice para realizar intercambios entre elementos y garantizar la correcta partición.

## Heap Sort
Heap Sort utiliza una estructura de datos de montículo para organizar los elementos. Primero construye un montículo máximo y luego extrae repetidamente el elemento máximo, colocándolo al final del arreglo. Tiene un rendimiento estable con complejidad O(n log n) y no requiere espacio adicional significativo.

**Funciones auxiliares:**
- Construcción del montículo: Una función que reorganiza el arreglo en una estructura de montículo máximo.
- Ajuste del montículo: Una función que mantiene la propiedad del montículo después de extraer el elemento máximo.

### Detalles de la función heapify:
La función `heapify` ajusta el arreglo para mantener la propiedad del montículo:
1. Determina si el nodo actual es menor que sus hijos.
2. Si es necesario, intercambia el nodo actual con el hijo más grande.
3. Llama recursivamente a `heapify` para ajustar el resto del montículo.

### Detalles de la función swap:
La función `swap` realiza el intercambio de dos elementos en el arreglo:
1. Usa una variable temporal para almacenar el valor de un elemento.
2. Asigna el valor del segundo elemento al primero.
3. Coloca el valor almacenado temporalmente en el segundo elemento.



| Algoritmo   |   Orden Promedio |  
|:------------|:--------:|
| Inserción   | O( n² )  | 
| Burbuja     | O( n² )  | 
| Selección   |  O( n² ) |
| Mezcla      |O(n log n)|
| Quick Sort  |O(n log n)|
| Montículos  |O(n log n)|
| Shell       |O(n log n)|


# Gráfica comparativa de los tiempos de ejecución (obtenidos experimentalmente)
La imagen a continuación presenta la comparación de los tiempos promedio de ejecución en relación con el tamaño de los conjuntos, correspondiente a cada uno de los algoritmos de ordenamiento evaluados.

![Grafica comparacion 7](Grafica%20comparacion%207.png)

El análisis de la gráfica revela que los algoritmos de ordenamiento por inserción, burbuja y selección presentan un incremento notablemente superior en sus tiempos promedio de ejecución con curvas ascendentes que indican una complejidad temporal cuadrática 𝑂(𝑛2), y conforme aumenta el tamaño de los conjuntos, lo cual evidencia su naturaleza algorítmica. Sin embargo cabe destacar que estos algoritmos fueron probados con un tamaño de pruebas de 1000 en 1000, sin embargo, si estos hubieran sido probados en un rango mayor podriamos ver una curva mejor, ya que estos "picos" que se observan son debidos a la cantidad que se uso en este codigo.


Al observar la grafica, se alcanza a distinguir la falta de claridad de cuatro algorimos anteriores, (merge, quick, monticulos y shell), por lo que a continuacion se presentaran en su totalidad.

![Grafica comparacion 4](Grafica%20comparacion%204.png)

En el gráfico se aprecia que los algoritmos no tienen un crecimiento lineal en su tiempo de ejecución, lo que descarta un orden de complejidad O(n). A diferencia de los métodos básicos (inserción, burbuja y selección), los otros cuatro muestran un rendimiento notablemente superior, sugiriendo que su comportamiento no es cuadrático, sino más bien logarítmico.

