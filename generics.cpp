#include <iostream>
#include <cstdlib>
#include "Array.hpp"
using namespace std;
#include <ctime>

int main() {
    std::srand(std::time(nullptr));
    
    ArrayGenerico<int> Array1;
    ArrayGenerico<int> Array2;

    Array1.restringir(); 
    for (int i=0;i<25;i++){
        int numero = std::rand ()%1000;
        Array1.insertar(numero);
    }

   
     // Imprime: 1 2 3 4 2 3 4

    Array1.imprimir(); // Deberia imprimir 1 2 3 4

    int num = Array1.largoArray();
    //miArray.bucketSort(num);

    //miArray.ordenar("bucketSort");

    Array1.ordenar("bucketSort");

    Array1.imprimir();

    cout << "\n";
    Array1.subdivision(4);

    return 0;
}

