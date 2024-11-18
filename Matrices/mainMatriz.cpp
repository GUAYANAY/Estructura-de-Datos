#include "Matriz.cpp"

int main() {
    // Crear dos matrices de tipo int
    Matriz<int> mat1;
    Matriz<int> mat2;

    // Inicializar matrices con valores aleatorios
    mat1.inicializarAleatorio();
    mat2.inicializarAleatorio();

    // Imprimir matrices
    cout << "Matriz 1:" << endl;
    mat1.imprimir();
    cout << endl;

    cout << "Matriz 2:" << endl;
    mat2.imprimir();
    cout << endl;

    // Calcular y mostrar la suma total usando suma recursiva
    cout << "Suma total de matrices: " 
         << Matriz<int>::sumarRecursivo(mat1.datos, mat2.datos, MAX - 1, MAX - 1) 
         << endl;

    return 0;
}
