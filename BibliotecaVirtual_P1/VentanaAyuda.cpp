#include "VentanaAyuda.h"
#include <sstream>
#include <iostream>
#include <windows.h>
#include <cstring>
#include <vector>
#include <sstream>


bool VentanaAyuda::claseRegistrada = false;
int offsetY = 0; // Controlar la posici�n de desplazamiento

LRESULT CALLBACK VentanaAyuda::WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_SIZE: {
            // Forzar el redibujado
            RECT rect;
            GetClientRect(hwnd, &rect);
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // Limpiar la pantalla para evitar que se repitan las palabras
            RECT rect;
            GetClientRect(hwnd, &rect);  // Obtener las dimensiones del �rea cliente de la ventana
            FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1)); // Limpiar con el color de fondo

            // Contenido de las instrucciones
           const char* instrucciones =
    "Bienvenido al sistema de gesti�n de libros y autores.\n\n"
    "El programa permite gestionar una lista de autores y libros mediante un men� interactivo.\n"
    "A continuaci�n, se describen las opciones de los men�s:\n\n"
    "1. Manejar Autores\n"
    "   - Insertar Autor: Agregar un nuevo autor al sistema.\n"
    "     Para insertar un autor, debe ingresar los siguientes datos:\n"
    "     - Ingrese Nombre: El nombre completo del autor. Solo debe contener letras\n"
    "       (sin n�meros ni caracteres especiales).\n"
    "     - Ingrese Apellido: El apellido completo del autor. Solo debe contener letras\n"
    "       (sin n�meros ni caracteres especiales).\n"
    "     - C�dula: La c�dula de identidad del autor. Debe ser un n�mero v�lido y �nico\n"
    "       (sin letras ni caracteres especiales). El sistema validar� que la c�dula no\n"
    "       est� registrada previamente.\n"
    "       Nota: Si la c�dula ya est� registrada, el autor no ser� agregado.\n"
    "     - Fecha de Publicaci�n: La fecha de publicaci�n del autor (si aplica).\n"
    "       Ingrese una fecha en formato MM/DD/AAAA.\n"
    "   - Buscar Autor: Buscar un autor por su c�dula.\n"
    "     Ingrese la c�dula del autor que desea buscar. El sistema le mostrar� los\n"
    "     datos del autor si este se encuentra registrado.\n"
    "   - Eliminar Autor: Eliminar un autor por su c�dula.\n"
    "     Ingrese la c�dula del autor que desea eliminar. Si el autor existe, ser�\n"
    "     eliminado del sistema.\n"
    "     Nota: Esta acci�n es irreversible y eliminar� todos los libros asociados\n"
    "     al autor.\n"
    "   - Mostrar Autores: Ver la lista de todos los autores registrados.\n"
    "     Esta opci�n le mostrar� una lista completa de todos los autores registrados\n"
    "     en el sistema.\n"
    "   - Generar PDF de Autores: Crear un archivo PDF con la lista completa de\n"
    "     autores registrados. Este archivo incluir� los datos de cada autor\n"
    "     (nombre, apellido, c�dula y fecha de publicaci�n).\n"
    "   - Crear Backup de Autores: Guardar un respaldo de todos los autores\n"
    "     registrados en el sistema.\n"
    "   - Restaurar Backup de Autores: Restaurar los datos de autores a partir de\n"
    "     un archivo de respaldo.\n"
    "\n"
    "2. Manejar Libros\n"
    "   - Insertar Libro: Agregar un nuevo libro al sistema.\n"
    "     Cedula del Autor: Deber� ingresar la c�dula del autor que va a utilizar\n"
    "     para el registro del libro.\n"
    "     Para insertar un libro, debe ingresar los siguientes datos:\n"
    "     - Ingrese el T�tulo: El t�tulo del libro. Solo debe contener letras y\n"
    "       espacios (sin n�meros ni caracteres especiales).\n"
    "     - ISBN: El ISBN del libro. Debe ser un n�mero �nico (sin letras ni\n"
    "       caracteres especiales). El sistema validar� que el ISBN no est�\n"
    "       registrado previamente.\n"
    "       Nota: Si el ISBN ya est� registrado, el libro no ser� agregado.\n"
    "   - Buscar Libro: Buscar un libro por su ISBN.\n"
    "     Ingrese el ISBN del libro que desea buscar. El sistema le mostrar� los\n"
    "     datos del libro si este se encuentra registrado.\n"
    "   - Eliminar Libro: Eliminar un libro por su ISBN.\n"
    "     Ingrese el ISBN del libro que desea eliminar. Si el libro existe, ser�\n"
    "     eliminado del sistema.\n"
    "   - Mostrar Libros: Ver la lista de todos los libros registrados.\n"
    "     Esta opci�n le mostrar� una lista completa de todos los libros registrados\n"
    "     en el sistema.\n"
    "   - Generar PDF de Libros: Crear un archivo PDF con la lista completa de\n"
    "     libros registrados. Este archivo incluir� los datos de cada libro\n"
    "     (t�tulo, ISBN y c�dula del autor asociado).\n"
    "   - Crear Backup de Libros: Guardar un respaldo de todos los libros\n"
    "     registrados en el sistema.\n"
    "   - Restaurar Backup de Libros: Restaurar los datos de libros a partir de\n"
    "     un archivo de respaldo.\n"
    "\n"
    "3. Salir: Termina la ejecuci�n del programa.\n"
    "   - Esta opci�n cerrar� el programa y saldr� del sistema.\n\n"
    "Recuerde que solo puede agregar autores y libros si estos no est�n\n"
    "previamente registrados en el sistema. Las c�dulas de los autores y los ISBN\n"
    "de los libros deben ser �nicos para cada registro. El sistema no permitir�\n"
    "duplicados.\n\n"
    "Validaciones importantes:\n"
    "1. En el campo de c�dula de los autores, se debe ingresar solo n�meros y esta\n"
    "   debe ser �nica. El sistema validar� que no haya letras ni caracteres\n"
    "   especiales en la c�dula.\n"
    "2. En los campos de nombre y apellido del autor, solo se deben ingresar letras\n"
    "   (sin n�meros ni caracteres especiales).\n"
    "3. En el campo del t�tulo del libro, solo se deben ingresar letras y espacios.\n"
    "   No se deben ingresar n�meros ni caracteres especiales.\n"
    "4. El ISBN debe ser un n�mero �nico y debe ingresarse correctamente sin letras\n"
    "   ni caracteres especiales.\n";




            // Convertir el texto en l�neas
            std::vector<std::string> lineas;
            std::istringstream stream(instrucciones);
            std::string linea;
            while (std::getline(stream, linea)) {
                lineas.push_back(linea);
            }

            // Pintar el texto dentro del �rea visible
            int yPos = 10 - offsetY; // Modificar la posici�n en Y seg�n el desplazamiento

            for (const std::string& linea : lineas) {
                // Si el texto llega al borde inferior, detener la pintura
                if (yPos > rect.bottom) {
                    break;
                }

                TextOut(hdc, 10, yPos, linea.c_str(), linea.length());
                yPos += 20; // Espaciado entre l�neas
            }

            EndPaint(hwnd, &ps);
            break;
        }
        case WM_VSCROLL: {
            SCROLLINFO si;
            si.cbSize = sizeof(SCROLLINFO);
            si.fMask = SIF_ALL;
            GetScrollInfo(hwnd, SB_VERT, &si);

            int nPos = si.nPos;

            // Desplazamiento en funci�n de la acci�n del usuario
            switch (LOWORD(wParam)) {
                case SB_LINEUP: // Desplazar hacia arriba una l�nea
                    if (nPos > 0) {
                        nPos--;
                    }
                    break;
                case SB_LINEDOWN: // Desplazar hacia abajo una l�nea
                    if (nPos < si.nMax) {
                        nPos++;
                    }
                    break;
                case SB_PAGEUP: // Desplazar hacia arriba una p�gina
                    if (nPos > 0) {
                        nPos -= 10;  // Ajustar el tama�o del desplazamiento
                    }
                    break;
                case SB_PAGEDOWN: // Desplazar hacia abajo una p�gina
                    if (nPos < si.nMax) {
                        nPos += 10;  // Ajustar el tama�o del desplazamiento
                    }
                    break;
                case SB_THUMBTRACK: // Desplazamiento manual del thumb
                    nPos = si.nTrackPos;
                    break;
            }

            // Actualizar la posici�n de la barra de desplazamiento
            SetScrollPos(hwnd, SB_VERT, nPos, TRUE);

            // Calcular el desplazamiento en el texto
            offsetY = nPos * 20;  // Multiplicar por el tama�o de la l�nea (20 px por l�nea)

            InvalidateRect(hwnd, NULL, TRUE);  // Forzar redibujado
            break;
        }
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

void VentanaAyuda::mostrar() {
    const char* className = "Ayuda";

    if (!claseRegistrada) {
        WNDCLASS wc = {0};
        wc.lpfnWndProc = WindowProcedure; // Funci�n de manejo de eventos
        wc.hInstance = GetModuleHandle(NULL);
        wc.lpszClassName = className;

        if (!RegisterClass(&wc)) {
            MessageBox(NULL, "Error al registrar la clase de ventana", "Error", MB_OK | MB_ICONERROR);
            return;
        }
        claseRegistrada = true;
    }

    // Crear la ventana con barra de desplazamiento
    HWND hwnd = CreateWindowEx(
        0,                          // Estilo extendido
        className,                  // Nombre de la clase
        "Ayuda - Instrucciones",    // T�tulo de la ventana
        WS_OVERLAPPEDWINDOW | WS_VSCROLL,  // Barra de desplazamiento habilitada
        CW_USEDEFAULT, CW_USEDEFAULT, 600, 400, // Posici�n y tama�o inicial
        NULL, NULL, GetModuleHandle(NULL), NULL);

    if (hwnd == NULL) {
        MessageBox(NULL, "Error al crear la ventana", "Error", MB_OK | MB_ICONERROR);
        return;
    }

    // Agregar la barra de desplazamiento
    SCROLLINFO si = {0};
    si.cbSize = sizeof(SCROLLINFO);
    si.fMask = SIF_PAGE | SIF_RANGE;
    si.nMin = 0;
    si.nMax = 100;  // Ajustar el rango seg�n el tama�o del contenido
    si.nPage = 10;  // Ajustar la p�gina (cantidad de texto visible)
    SetScrollInfo(hwnd, SB_VERT, &si, TRUE);

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}
