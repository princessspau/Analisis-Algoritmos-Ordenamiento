#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;
using namespace chrono;

// Constantes globales
const int NUM_PRUEBAS = 1000; // Numero de pruebas a realizar por cada tama�o de arreglo
const int MIN_TAMANO = 10;   // Tamano minimo de los arreglos
const int MAX_TAMANO = 1000; // Tamano maximo de los arreglos
const int INCREMENTO = 10;   // Incremento entre tama�os consecutivos de los arreglos
const int NUM_ALGORITMOS = 7; // N�mero de algoritmos de ordenamiento a evaluar

// Prototipos de funciones
void generarArreglo(int arr[], int n); // Genera un arreglo aleatorio de tama�o n
void copiarArreglo(int origen[], int destino[], int n); // Copia un arreglo en otro
long long medirTiempo(int arr[], int n, void (*algoritmo)(int[], int)); // Mide el tiempo de ejecuci�n de un algoritmo
void ejecutarPruebas(const string& nombreAlgoritmo, void (*algoritmo)(int[], int), const string& filename, double promedios[]); // Ejecuta pruebas para un algoritmo
void exportarResultados(const string& filename, long long tiempos[][(MAX_TAMANO-MIN_TAMANO)/INCREMENTO + 1], int num_tamanos); // Exporta los resultados a un archivo CSV
void exportarPromediosTotales(const string& filename, const string nombresAlgoritmos[], double promediosTotales[][(MAX_TAMANO-MIN_TAMANO)/INCREMENTO + 1], int num_tamanos); // Exporta los promedios totales

// Algoritmos de ordenamiento
void insercion(int arr[], int n); // Ordenamiento por inserci�n
void burbuja(int arr[], int n);  // Ordenamiento burbuja
void seleccion(int arr[], int n); // Ordenamiento por selecci�n
void shell(int arr[], int n);     // Ordenamiento Shell
void mezclaSortWrapper(int arr[], int n);
void quickSortWrapper(int arr[], int n);
void heapSort(int arr[], int n); // Ordenamiento por mont�culos

// Funciones auxiliares
void Mezcla(int arr[], int inicio, int medio, int fin); // Mezcla dos subarreglos (para MergeSort)
void mezclaSort(int arr[], int inicio, int fin); // Implementaci�n de MergeSort
int PARTITION(int arr[], int inicio, int fin);  // Partici�n para QuickSort
void quickSort(int arr[], int inicio, int fin); // Implementaci�n de QuickSort
void heapify(int arr[], int n, int i);          // Reorganiza el �rbol para mantener la propiedad de heap
void swap(int *a, int *b);                      // Intercambia dos elementos

int main() {
    srand(time(nullptr)); // Inicializa la semilla para la generaci�n de n�meros aleatorios

    const int num_tamanos = (MAX_TAMANO - MIN_TAMANO) / INCREMENTO + 1; // Calcula la cantidad de tama�os a probar
    string nombresAlgoritmos[NUM_ALGORITMOS] = { // Nombres de los algoritmos para exportaci�n
        "Insercion", "Burbuja", "Seleccion", "Merge", "Quick", "Monticulos", "Shell"
    };
    double promediosTotales[NUM_ALGORITMOS][num_tamanos]; // Matriz para almacenar promedios totales

    cout << "=== COMPARACION DE ALGORITMOS DE ORDENAMIENTO ===" << endl;
    cout << "Pruebas por tam: " << NUM_PRUEBAS << endl;
    cout << "Tam desde " << MIN_TAMANO << " hasta " << MAX_TAMANO << " en incrementos de " << INCREMENTO << endl << endl;

    // Ejecutar pruebas para cada algoritmo
    double promedios[num_tamanos];

    ejecutarPruebas("Inserci�n", insercion, "1_Insercion_Ordenamiento.csv", promedios);
    for (int t = 0; t < num_tamanos; ++t) promediosTotales[0][t] = promedios[t];

    ejecutarPruebas("Burbuja", burbuja, "2_Burbuja_Ordenamiento.csv", promedios);
    for (int t = 0; t < num_tamanos; ++t) promediosTotales[1][t] = promedios[t];

    ejecutarPruebas("Selecci�n", seleccion, "3_Seleccion_Ordenamiento.csv", promedios);
    for (int t = 0; t < num_tamanos; ++t) promediosTotales[2][t] = promedios[t];

    ejecutarPruebas("Mezcla", mezclaSortWrapper, "4_Merge_Ordenamiento.csv", promedios);
    for (int t = 0; t < num_tamanos; ++t) promediosTotales[3][t] = promedios[t];

    ejecutarPruebas("QuickSort", quickSortWrapper, "5_Quick_Ordenamiento.csv", promedios);
    for (int t = 0; t < num_tamanos; ++t) promediosTotales[4][t] = promedios[t];

    ejecutarPruebas("HeapSort", heapSort, "6_Monticulos_Ordenamiento.csv", promedios);
    for (int t = 0; t < num_tamanos; ++t) promediosTotales[5][t] = promedios[t];

    ejecutarPruebas("Shell", shell, "7_Shell_Ordenamiento.csv", promedios);
    for (int t = 0; t < num_tamanos; ++t) promediosTotales[6][t] = promedios[t];

    // Exportar promedios totales
    exportarPromediosTotales("Promedios_Totales.csv", nombresAlgoritmos, promediosTotales, num_tamanos);

    cout << "\n=== TODAS LAS PRUEBAS COMPLETADAS ===" << endl;
    cout << "Se han generado los archivos:\n";
    for (int i = 1; i <= 7; ++i) {
        cout << "- " << i << "_";
        switch(i) {
            case 1: cout << "Insercion"; break;
            case 2: cout << "Burbuja"; break;
            case 3: cout << "Seleccion"; break;
            case 4: cout << "Merge"; break;
            case 5: cout << "Quick"; break;
            case 6: cout << "Monticulos"; break;
            case 7: cout << "Shell"; break;
        }
        cout << "_Ordenamiento.csv\n";
    }
    cout << "- Promedios_Totales.csv\n";

    return 0;
}

// IMPLEMENTACION PARA CAMBIO DE VARIABLE
void mezclaSortWrapper(int arr[], int n) {
    mezclaSort(arr, 0, n - 1); // Llama a MergeSort con los �ndices inicial y final
}

//*****************************************************************************************

void quickSortWrapper(int arr[], int n) {
    quickSort(arr, 0, n - 1); // Llama a QuickSort con los �ndices inicial y final
}



// Implementaci�n de algoritmos


//****************************************************************************
void insercion(int arr[], int n) {
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) { // Recorre los elementos mayores que la clave hacia la derecha
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key; // Inserta la clave en su posici�n correcta
    }
}


//***************************************************************************
void burbuja(int arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) { // Intercambia elementos desordenados
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}


//**************************************************************************
void seleccion(int arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_idx]) { // Encuentra el elemento m�s peque�o
                min_idx = j;
            }
        }
        if (min_idx != i) {
            swap(&arr[i], &arr[min_idx]); // Intercambia el elemento m�s peque�o con el actual
        }
    }
}


//**************************************************************************
void shell(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) { // Reduce el tama�o del intervalo
        for (int i = gap; i < n; ++i) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) { // Ordena los elementos a intervalos gap
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}


//*******************************************************************************
void mezclaSort(int arr[], int inicio, int fin) {
    if (inicio >= fin) return;

    int medio = inicio + (fin - inicio) / 2; // Divide el arreglo en dos mitades
    mezclaSort(arr, inicio, medio);         // Ordena la mitad izquierda
    mezclaSort(arr, medio + 1, fin);       // Ordena la mitad derecha
    Mezcla(arr, inicio, medio, fin);       // Combina las dos mitades
}


//****************************************************************************
void quickSort(int arr[], int inicio, int fin) {
    if (inicio >= fin) return;

    int pi = PARTITION(arr, inicio, fin); // Encuentra la posici�n del pivote
    quickSort(arr, inicio, pi - 1);       // Ordena la parte izquierda
    quickSort(arr, pi + 1, fin);          // Ordena la parte derecha
}

//****************************************************************************

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; --i) // Construye el heap inicial
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; --i) {
        swap(&arr[0], &arr[i]); // Mueve el mayor elemento al final
        heapify(arr, i, 0);     // Restaura la propiedad del heap
    }
}

//**************************************************************************

// Funciones auxiliares


void Mezcla(int arr[], int inicio, int medio, int fin) {
    int n1 = medio - inicio + 1;
    int n2 = fin - medio;

    int L[n1], R[n2]; // Arreglos temporales para almacenar las mitades

    for (int i = 0; i < n1; ++i) L[i] = arr[inicio + i];
    for (int j = 0; j < n2; ++j) R[j] = arr[medio + 1 + j];

    int i = 0, j = 0, k = inicio;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++]; // Copia los elementos restantes de L
    while (j < n2) arr[k++] = R[j++]; // Copia los elementos restantes de R
}

//********************************************************************************

int PARTITION(int arr[], int inicio, int fin) {
    int pivote = arr[fin]; // Selecciona el �ltimo elemento como pivote
    int i = inicio - 1; // Inicializa el �ndice del menor elemento

    for (int j = inicio; j <= fin - 1; ++j) {
        if (arr[j] < pivote) { // Si el elemento actual es menor que el pivote
            i++;
            swap(&arr[i], &arr[j]); // Intercambia elementos
        }
    }
    swap(&arr[i + 1], &arr[fin]);
    return i + 1;
}

//******************************************************************************

void heapify(int arr[], int n, int i) {
    int largest = i; // Inicializa el nodo m�s grande como ra�z
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) { // Si el m�s grande no es la ra�z
        swap(&arr[i], &arr[largest]); // Intercambia y reestructura el sub�rbol afectado
        heapify(arr, n, largest); // Llama recursivamente para asegurar la propiedad del heap
    }
}

//********************************************************************************

void swap(int *a, int *b) {
    int temp = *a; // Intercambia los valores de dos variables
    *a = *b;
    *b = temp;
}

//***********************************************************************

void generarArreglo(int arr[], int n) {
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % 10000; // Llena el arreglo con valores aleatorios entre 0 y 9999
    }
}

//************************************************************************

void copiarArreglo(int origen[], int destino[], int n) {
    for (int i = 0; i < n; ++i) {
        destino[i] = origen[i]; // Copia cada elemento del arreglo origen al destino
    }
}

//*************************************************************************

long long medirTiempo(int arr[], int n, void (*algoritmo)(int[], int)) {
    int copia[MAX_TAMANO];
    copiarArreglo(arr, copia, n); // Crea una copia del arreglo original

    auto inicio = high_resolution_clock::now(); // Registra el tiempo de inicio
    algoritmo(copia, n); // Ejecuta el algoritmo en la copia del arreglo
    auto fin = high_resolution_clock::now(); // Registra el tiempo de finalizaci�n

    return duration_cast<nanoseconds>(fin - inicio).count(); // Calcula y retorna el tiempo en nanosegundos
}

//***********************************************************************************

void ejecutarPruebas(const string& nombreAlgoritmo, void (*algoritmo)(int[], int), const string& filename, double promedios[]) {
    const int num_tamanos = (MAX_TAMANO - MIN_TAMANO) / INCREMENTO + 1; // Calcula el n�mero de tama�os de prueba
    long long tiempos[NUM_PRUEBAS][num_tamanos] = {0}; // Matriz para almacenar los tiempos de cada prueba

    cout << "Procesando " << nombreAlgoritmo << "..." << endl;

    for (int t = 0; t < num_tamanos; ++t) {
        int n = MIN_TAMANO + t * INCREMENTO; // Calcula el tama�o actual de la prueba
        long long suma_tiempos = 0;

        for (int prueba = 0; prueba < NUM_PRUEBAS; ++prueba) {
            int arr[MAX_TAMANO];
            generarArreglo(arr, n); // Genera un arreglo aleatorio de tama�o n
            tiempos[prueba][t] = medirTiempo(arr, n, algoritmo); // Mide el tiempo del algoritmo
            suma_tiempos += tiempos[prueba][t]; // Acumula los tiempos
        }

        promedios[t] = static_cast<double>(suma_tiempos) / NUM_PRUEBAS; // Calcula el promedio de tiempos para el tama�o actual
        cout << "  Tama�o " << n << ": " << fixed << setprecision(2) << promedios[t] << " ns\n";
    }

    exportarResultados(filename, tiempos, num_tamanos); // Exporta los resultados individuales de cada prueba
}

//**********************************************************************************************************************


void exportarResultados(const string& filename, long long tiempos[][(MAX_TAMANO-MIN_TAMANO)/INCREMENTO + 1], int num_tamanos) {
    ofstream archivo(filename);

    if (!archivo.is_open()) {
        cerr << "error al abrir el archivo " << filename << endl; // Maneja errores al abrir el archivo
        return;
    }

    archivo << "Prueba";
    for (int t = 0; t < num_tamanos; ++t) {
        archivo << ",Tama�o_" << MIN_TAMANO + t * INCREMENTO; // Escribe los encabezados de los tama�os
    }
    archivo << "\n";

    for (int p = 0; p < NUM_PRUEBAS; ++p) {
        archivo << p + 1; // Escribe el n�mero de la prueba
        for (int t = 0; t < num_tamanos; ++t) {
            archivo << "," << tiempos[p][t]; // Escribe los tiempos de cada prueba
        }
        archivo << "\n";
    }

    archivo.close(); // Cierra el archivo
}

//***************************************************************************************************

void exportarPromediosTotales(const string& filename, const string nombresAlgoritmos[], double promediosTotales[][(MAX_TAMANO-MIN_TAMANO)/INCREMENTO + 1], int num_tamanos) {
    ofstream archivo(filename);

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo " << filename << endl; // Maneja errores al abrir el archivo
        return;
    }

    archivo << "Algoritmo";
    for (int t = 0; t < num_tamanos; ++t) {
        archivo << ",Tama�o_" << MIN_TAMANO + t * INCREMENTO; // Escribe los encabezados de los tama�os
    }
    archivo << "\n";

    for (int a = 0; a < NUM_ALGORITMOS; ++a) {
        archivo << nombresAlgoritmos[a]; // Escribe el nombre del algoritmo
        for (int t = 0; t < num_tamanos; ++t) {
            archivo << "," << fixed << setprecision(2) << promediosTotales[a][t]; // Escribe los promedios de tiempos
        }
        archivo << "\n";
    }

    archivo.close(); // Cierra el archivo
}
