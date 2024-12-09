#ifndef CURSOR_H
#define CURSOR_H
#include <windows.h>
#include <string>

class Cursor {
private:
    int posicion;          // Posición actual del cursor
    int totalOpciones;     // Total de opciones del menú

public:
    // Constructor que recibe el total de opciones del menú
    Cursor(int totalOpciones);

    // Método para mover el cursor hacia arriba
    void moverArriba();

    // Método para mover el cursor hacia abajo
    void moverAbajo();

    // Método para obtener la posición actual del cursor
    int getPosicion();

    // Método para mostrar el menú con el cursor en la opción seleccionada
    void actualizarMenu(const std::string opciones[], int totalOpciones);

    // Método que verifica si se presionó la tecla Enter
    bool aceptarSeleccion();

    // Método que verifica si alguna tecla ha sido presionada
    bool teclaPresionada();
    void cambiarColorTexto(int color);
};

#endif // CURSOR_H
