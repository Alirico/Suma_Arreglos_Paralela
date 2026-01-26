#include <iostream>
#include <vector>
#include <omp.h>    // Librería esencial para OpenMP
#include <ctime>    // Para generar números aleatorios
#include <iomanip>  // Para que la impresión se vea ordenada

#define N 1000      // Cantidad de elementos
#define chunk 100   // Tamaño de los pedazos de datos para los hilos
#define mostrar 10  // Cuántos elementos mostrar para verificar

void imprimirArreglo(float *d, int n);

int main() {
    std::cout << "Verificando ejecucion en paralelo con OpenMP...\n";
    
    float a[N], b[N], c[N];
    int i;

    // Inicializamos la semilla para números aleatorios
    srand(time(0));

    // Llenamos los arreglos con valores aleatorios
    for (i = 0; i < N; i++) {
        a[i] = static_cast<float>(rand() % 100);
        b[i] = static_cast<float>(rand() % 100);
    }

    // --- PASO CLAVE: Bucle for paralelo ---
    // Usamos la directiva parallel for para repartir el trabajo
    #pragma omp parallel for \
        shared(a, b, c) private(i) \
        schedule(static, chunk)

    for (i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
    }

    // --- Comprobación de resultados ---
    std::cout << "Imprimiendo los primeros " << mostrar << " elementos de los arreglos:\n";
    std::cout << "Arreglo A: "; imprimirArreglo(a, mostrar);
    std::cout << "Arreglo B: "; imprimirArreglo(b, mostrar);
    std::cout << "Arreglo C (Suma): "; imprimirArreglo(c, mostrar);

    return 0;
}

void imprimirArreglo(float *d, int n) {
    for (int x = 0; x < n; x++) {
        std::cout << d[x] << " - ";
    }
    std::cout << std::endl;
}