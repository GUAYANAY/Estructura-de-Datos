#include "Cursor.h"
#include <iostream>
#include <conio.h> // Para _kbhit() y _getch() en Windows
#include <cstdlib> // Para system("cls")
#include <windows.h>

using namespace std;

// Constructor que inicializa la posición del cursor y el total de opciones
Cursor::Cursor(int totalOpciones) : posicion(0), totalOpciones(totalOpciones) {}

// Método para mover el cursor hacia arriba
void Cursor::moverArriba() {
    if (posicion > 0) {
        posicion--;
    }else {
        // Si está en la primera opción, saltar al final
        posicion = totalOpciones - 1;
    }
}

// Método para mover el cursor hacia abajo
void Cursor::moverAbajo() {
    if (posicion < totalOpciones - 1) {
        posicion++;
    }else {
        // Si está en la última opción, saltar al principio
        posicion = 0;
    }
}

// Método para obtener la posición actual del cursor
int Cursor::getPosicion() {
    return posicion;
}

// Método para actualizar y mostrar el menú con el cursor en la opción seleccionada

void Cursor::actualizarMenu(const string opciones[], int totalOpciones) {
    system("cls");  // Limpiar la consola

    for (int i = 0; i < totalOpciones; i++) {
        if (i == posicion) {
            cambiarColorTexto(3); // Color amarillo para la opción seleccionada
            cout << "* " << opciones[i] << " *\n";
            cambiarColorTexto(7); // Restaurar color blanco
        } else {
            cout << "  " << opciones[i] << "\n";
        }
    }
}


// Método para verificar si se presionó la tecla Enter (código 13)
bool Cursor::aceptarSeleccion() {
    return (_kbhit() && _getch() == 13); // Enter
}

// Método para verificar si se presionó cualquier tecla
bool Cursor::teclaPresionada() {
    return _kbhit();
}

void Cursor::cambiarColorTexto(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
