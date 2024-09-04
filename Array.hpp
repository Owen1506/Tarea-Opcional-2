#include <iostream>
using namespace std;

template<typename T>
class ArrayGenerico {
private:
    T* arreglo;
    int capacidad;
    int cantidad;
    bool estaRestringido = true;

    void redimensionar(int nuevaCapacidad) {
        T* nuevoArreglo = new T[nuevaCapacidad];
        for (int i = 0; i < cantidad; i++) {
            nuevoArreglo[i] = arreglo[i];
        }
        delete[] arreglo;
        arreglo = nuevoArreglo;
        capacidad = nuevaCapacidad;
    }

    bool aparece(T dato) const {
        for (int i = 0; i < cantidad; i++) {
            if (arreglo[i] == dato) {
                return true;
            }
        }
        return false;
    }

public:
    ArrayGenerico(int capacidadInicial = 10000) {
        capacidad = capacidadInicial;
        cantidad = 0;
        arreglo = new T[capacidad];
    }

    ~ArrayGenerico() {
        delete[] arreglo;
    }

    int largoArray() const {
        return cantidad;
    }

    void restringir() {
        estaRestringido = !estaRestringido;
        
        if (estaRestringido) {
            T* arregloReferencia = new T[cantidad];
            int nuevaCantidad = 0;

            for (int i = 0; i < cantidad; i++) {
                bool yaExiste = false;
                for (int j = 0; j < nuevaCantidad; j++) {
                    if (arreglo[i] == arregloReferencia[j]) {
                        yaExiste = true;
                        break;
                    }
                }
                if (!yaExiste) {
                    arregloReferencia[nuevaCantidad] = arreglo[i];
                    nuevaCantidad++;
                }
            }
            
            delete[] arreglo;
            arreglo = new T[nuevaCantidad];
            for (int i = 0; i < nuevaCantidad; i++) {
                arreglo[i] = arregloReferencia[i];
            }

            cantidad = nuevaCantidad;
            capacidad = nuevaCantidad; 
            delete[] arregloReferencia;
        }
    }

//Insercion

    void insertar(T dato) {
        if (estaRestringido && aparece(dato)) {
            cout << "Elemento repetido no permitido en modo restringido." << endl;
            return;
        }
        if (cantidad == capacidad) {
            redimensionar(capacidad + 1); 
        }

        arreglo[cantidad] = dato;
        cantidad++;
    }
    
    void insertarInicio(T dato) {
        T* arregloReferencia = new T[cantidad];
        for (int i = 0; i < cantidad; i++) {
            arregloReferencia[i] = arreglo[i];
        }
        delete[] arreglo;
        arreglo = new T[cantidad + 1];
        int contador = 0;
        while (contador < cantidad) {
            if (contador == 0) {
                arreglo[contador] = dato;
            }
            arreglo[contador + 1] = arregloReferencia[contador];
            contador++;
        }

        cantidad++;
    }

    void insertarAleatorio(T dato, int indice) {
        T* arregloReferencia = new T[cantidad];
        for (int i = 0; i < cantidad; i++) {
            arregloReferencia[i] = arreglo[i];
        }
        delete[] arreglo;
        arreglo = new T[cantidad + 1];
        int contador1 = 0;
        int contador2 = 0;
        while (contador1 < cantidad) {
            if (contador1 == indice) {
                arreglo[contador1] = dato;
                contador1++;
                cantidad++;
            }
            arreglo[contador1] = arregloReferencia[contador2];
            contador1++;
            contador2++;
        }
    }

    void insertarEn(T dato, const char* modo) {
        if (modo == "aleatorio") {
            insertarAleatorio(dato, 3);
        }

        if (modo == "inicio") {
            insertarInicio(dato);
        }

        if (modo == "final") {
            insertar(dato);
        }
    }

//-------------------//////


    void eliminar(int indice) {
        if (indice < 0 || indice >= cantidad) {
            cout << "Indice fuera de rango" << endl;
            return;
        }
        for (int i = indice; i < cantidad - 1; i++) {
            arreglo[i] = arreglo[i + 1];
        }
        cantidad--;
        if (cantidad > 0 && cantidad == capacidad / 4) {
            redimensionar(capacidad / 2);
        }
    }

    void modificar(int indice, T dato) {
        if (indice < 0 || indice >= cantidad) {
            cout << "Indice fuera de rango" << endl;
            return;
        }
        arreglo[indice] = dato;
    }

    T obtener(int indice) const {
        if (indice < 0 || indice >= cantidad) {
            cout << "Indice fuera de rango" << endl;
            throw out_of_range("Indice fuera de rango");
        }
        return arreglo[indice];
    }


//Ordenamiento 
    void ordenar(const char*  Modo)
    {
        if (Modo == "heapSort"){
            heapSort();
        }

        if (Modo == "bucketSort"){
            bucketSort();
        }
    }

    void heapify(T* arr, int n, int i) {
        int mayor = i;
        int izquierda = 2 * i + 1;
        int derecha = 2 * i + 2;

        if (izquierda < n && arr[izquierda] > arr[mayor])
            mayor = izquierda;

        if (derecha < n && arr[derecha] > arr[mayor])
            mayor = derecha;

        if (mayor != i) {
            swap(arr[i], arr[mayor]);
            heapify(arr, n, mayor);
        }
    }

    void heapSort() {
        for (int i = cantidad / 2 - 1; i >= 0; i--) {
            heapify(arreglo, cantidad, i);
        }

        for (int i = cantidad - 1; i > 0; i--) {
            swap(arreglo[0], arreglo[i]);
            heapify(arreglo, i, 0);
        }
    }
   
    void bucketSort() {
        int num = cantidad;
        int i, j;
        int valorMaximo = arreglo[0];

        for (i = 1; i < num; i++) {
            if (arreglo[i] > valorMaximo) {
                valorMaximo = arreglo[i];
            }
        }

        int arreglo1[valorMaximo + 1];
        for (i = 0; i <= valorMaximo; i++) {
            arreglo1[i] = 0;
        }

        for (i = 0; i < num; i++) {
            arreglo1[arreglo[i]]++;
        }
        for (i = 0, j = 0; i <= valorMaximo; i++) {
            while (arreglo1[i] > 0) {
                arreglo[j++] = i;
                arreglo1[i]--;
            }
        }
    }

//------------------------------//

    void convertirArbolBinario() {
        T* arregloReferencia = new T[cantidad];
        for (int i = 0; i < cantidad; i++) {
            arregloReferencia[i] = arreglo[i];
        }

        delete[] arreglo;
        arreglo = new T[cantidad];
        for (int i = 0; i < cantidad; i++) {
            arreglo[i] = -1;
        }

        for (int i = 0; i < cantidad; i++) {
            if (arregloReferencia[i] != -1) {
                insertarEnArbol(arreglo, cantidad, arregloReferencia[i]);
            }
        }

        delete[] arregloReferencia;
    }

    void insertarEnArbol(T* t, int s, T dato) {
        if (t[0] == -1) {
            t[0] = dato;
        } else {
            int i = 0;
            while (i < s && t[i] != -1) {
                if (t[i] == dato) {
                    return;
                } else if (t[i] > dato) {
                    i = 2 * i + 1;
                } else {
                    i = 2 * i + 2;
                }
            }
            if (i < s) {
                t[i] = dato;
            } 
        }
    }

    void mostrarAux(int* t, int s, int p, int l) {
        if (p >= s || t[p] == -1) {
            return;
        }

        mostrarAux(t, s, 2 * p + 1, l + 1);

        for (int i = 0; i < l; i++) {
            cout << '\t';
        }
        cout << t[p] << endl;

        mostrarAux(t, s, 2 * p + 2, l + 1);
    }

    void mostrar() {
        mostrarAux(arreglo, cantidad, 0, 0);
    }

    void imprimir() const {
        for (int i = 0; i < cantidad; i++) {
            cout << arreglo[i] << " ";
        }
        cout << endl;
    }

    T** subdivision(int divisiones) {
        if (divisiones <= 0 || divisiones > cantidad) {
            cout << "Número de subdivisiones inválido." << endl;
            return nullptr;
        }

        
        T** resultado = new T*[divisiones];

        int indiceActual = 0;
        int cont = 0;
        int cont3 = 0;
        while (cont < divisiones){
            int cont2 = 0;
            resultado[cont] = new T[cantidad/divisiones];
            while(cont2<(cantidad/divisiones)){
                resultado[cont][cont2] = arreglo[cont3];
                cont2 ++;
                cont3 ++;
            }
            cont ++;
            
        }

        imprimirSubdivisiones(resultado,divisiones);
        return resultado;
    }

    void imprimirSubdivisiones(T** array, int divisiones) {
        for (int i = 0; i < divisiones; i++) {
            for (int j = 0; j<cantidad/divisiones; j++) {
                cout << array[i][j] << " ";
            }
            cout << endl;
        }
    }

};
