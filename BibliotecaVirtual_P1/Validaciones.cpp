#include "Validaciones.h"
#include <regex>
#include <iostream>
#include <limits>

// Validaciones existentes
bool validarCedula(const string& cedula) {
    if (cedula.length() != 10) return false;
    if (!regex_match(cedula, regex("\\d{10}"))) return false;

    int suma = 0;
    for (int i = 0; i < 9; i++) {
        int digito = cedula[i] - '0';
        if (i % 2 == 0) {
            digito *= 2;
            if (digito > 9) digito -= 9;
        }
        suma += digito;
    }

    int ultimoDigito = cedula[9] - '0';
    int decenaSuperior = (suma + 9) / 10 * 10;
    return ultimoDigito == (decenaSuperior - suma);
}

bool validarTexto(const string& texto) {
    return regex_match(texto, regex("^[a-zA-ZáéíóúÁÉÍÓÚñÑ ]+$"));
}

bool validarFecha(const string& fecha) {
    return regex_match(fecha, regex("^(0[1-9]|1[0-2])/(0[1-9]|[12][0-9]|3[01])/[0-9]{4}$"));
}

bool validarEntero(const string& numero) {
    return regex_match(numero, regex("^-?\\d+$"));
}

bool validarFlotante(const string& numero) {
    return regex_match(numero, regex("^-?\\d*\\.?\\d+$"));
}

bool validarOpcionMenu(int opcion, int min, int max) {
    return opcion >= min && opcion <= max;
}

bool validarPrecio(double precio) {
    return precio >= 0.0;
}

bool validarCalificacion(double calificacion) {
    return calificacion >= 0.0 && calificacion <= 10.0;
}

bool validarISBN(const std::string& isbn) {
    return std::regex_match(isbn, std::regex("[0-9-]+"));
}

// Función para ingresar números enteros (por ejemplo, año)
bool ingresarNumero(int& numero) {
    while (true) {
        cin >> numero;
        if (cin.fail()) { // Si la entrada no es un número
            cin.clear(); // Limpiar el error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorar caracteres no válidos
            cout << "Error: Ingresa un numero valido.\n";
        } else {
            return true; // Entrada válida
        }
    }
}

// Función para ingresar números decimales (por ejemplo, precio o calificación)
bool ingresarNumero(double& numero) {
    while (true) {
        cin >> numero;
        if (cin.fail()) { // Si la entrada no es un número
            cin.clear(); // Limpiar el error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorar caracteres no válidos
            cout << "Error: Ingresa un numero valido.\n";
        } else {
            return true; // Entrada válida
        }
    }
}

// Función para ingresar y validar la opción seleccionada en el menú
bool ingresarOpcionMenu(int& opcion) {
    while (true) {
        cin >> opcion;
        if (cin.fail()) { // Si la entrada no es un número
            cin.clear(); // Limpiar el error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorar caracteres no válidos
            cout << "Error: Ingresa una opcion valida.\n";
             cout << "Vuelve a intentarlo por favor:";
        } else {
            return true; // Entrada válida
        }
    }
}
