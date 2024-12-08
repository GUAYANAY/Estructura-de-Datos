#ifndef VENTANA_AYUDA_H
#define VENTANA_AYUDA_H

#include <windows.h>

class VentanaAyuda {
public:
    // Método público para mostrar la ventana de ayuda
    void mostrar();

private:
    // Método estático para manejar eventos de la ventana
    static LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    // Variable estática para rastrear si la clase de ventana ya fue registrada
    static bool claseRegistrada;
};

#endif
