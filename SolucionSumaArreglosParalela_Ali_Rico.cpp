// --- Crear el proyecto en VS y configurarlo para utilizar OpenMP ---
#include <iostream>
#include <omp.h>    // agregar la librería esencial para OpenMP


#define N 1000      // cantidad de elementos a manejar en los arreglos
#define chunk 100   // tamaño que tendrán los pedazos de los arreglos para que cada hilo creado se encargue de esta cantidad de elementos
#define mostrar 10  // Permitirá manejar la cantidad de datos a imprimir

//La creación de las constantes y del prototipo de la función
void imprimeArreglo(float *d);

// --- Crear los arreglos y asignarles valores ---
int main() {
    std::cout << "Sumando arreglos en paralelo\n";
    
    float a[N], b[N], c[N];
    int i;

    for (i = 0; i < N; i++) 
    {
        a[i] = i*10;
        b[i] = (i+3) * 3.7;
    }
    int pedazos=chunk;

    // --- Crear un for paralelo con OpenMP ---
    
    #pragma omp parallel for \
    shared(a, b, c) private(i) \
    schedule(static, pedazos)

    for (i = 0; i < N; i++) 
        c[i] = a[i] + b[i];
    

    // --- Imprimiendo los arreglos ---
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a: " << std::endl;
    imprimeArreglo(a);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b: " << std::endl;
    imprimeArreglo(b);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c: " << std::endl;
    imprimeArreglo(c);

    std::cout << "Más ordenado " << mostrar << " valores A + B = C " << std::endl;
    std::cout << "A: "; imprimeArreglo(a);
    std::cout << "+ " << std::endl;
    std::cout << "B: "; imprimeArreglo(b);
    std::cout << "= " << std::endl;
    std::cout << "C: "; imprimeArreglo(c);
}

void imprimeArreglo(float *d) 
{
    for (int x = 0; x < mostrar; x++) 
        std::cout << d[x] << " - ";
    std::cout << std::endl;
}