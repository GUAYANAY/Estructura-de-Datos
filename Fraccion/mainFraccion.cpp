/*
Programa: Operaciones con Fracciones
Autor: Erika Vannesa Guayanay Lema
Fecha: 11 de Noviembre del 2024
**************UNIVERSIDAD DE LAS FUERZAS ARMADAS "ESPE"***************************
*/

#include "Fraccion.cpp"
#include <iostream>
#include <limits>
#include <string>
#include <cctype>

bool validarEntrada(int& valor) {
    std::string entrada;
    std::cin >> entrada;

    // Validar que la entrada contenga solo dígitos (y opcionalmente un signo)
    for (char c : entrada){
        if (!isdigit(c) && c != '-') {
            // Si contiene un punto o coma, o cualquier otro carácter no numérico
            if (c == '.' || c == ',') {
                return false; // No permitir decimales
            }
            return false; // No permitir caracteres no numéricos
        }
    }

    // Convertir la entrada válida en un número entero
    try {
        valor = std::stoi(entrada);  // Si la conversión es exitosa, es un número entero válido
    } catch (const std::invalid_argument& e) {
        return false;  // Si no se puede convertir, es una entrada no válida
    } catch (const std::out_of_range& e) {
        return false;  // Si el número es demasiado grande
    }

    return true;  // La entrada es un número entero válido
}

int main() {
    try {
        int numerador1, denominador1, numerador2, denominador2;

        // Solicitar y validar la primera fracción
        std::cout << "Ingrese Los datos de la primera Fraccion: " << std::endl;
        std::cout << "Numerador: ";
        while (!validarEntrada(numerador1)) {
            std::cout << "Entrada no valida. Ingrese un numero entero: ";
        }

        std::cout << "Denominador diferente de cero: ";
        while (!validarEntrada(denominador1) || denominador1 == 0) {
            std::cout << "El denominador no puede ser cero o una entrada no valida. Intente de nuevo: ";
        }

        // Solicitar y validar la segunda fracción
        std::cout << "Ingrese Los datos de la segunda Fraccion: " << std::endl;
        std::cout << "Numerador: ";
        while (!validarEntrada(numerador2)) {
            std::cout << "Entrada no valida. Ingrese un numero entero: ";
        }

        std::cout << "Denominador diferente de cero: ";
        while (!validarEntrada(denominador2) || denominador2 == 0) {
            std::cout << "El denominador no puede ser cero o una entrada no valida. Intente de nuevo: ";
        }

        // Crear objetos Fraccion y sumar
        Fraccion<int> fraccion1(numerador1, denominador1);
        Fraccion<int> fraccion2(numerador2, denominador2);

        Fraccion<int> resultado = fraccion1.procesar(fraccion1, fraccion2);
        Fraccion<int> resultadoResta=fraccion1.procesarResta(fraccion1,fraccion2);

       // Imprimir la suma de las fracciones en formato a/b + c/d = (ad + bc)/bd
        std::cout << "La suma de las fracciones "
          << fraccion1.getNumerador() << "/" << fraccion1.getDenominador() 
          << " + " 
          << fraccion2.getNumerador() << "/" << fraccion2.getDenominador() 
          << " es: "
          << resultado.getNumerador() << "/" << resultado.getDenominador() 
          << std::endl;

        double resultadoDecimal = static_cast<double>(resultado.getNumerador()) / resultado.getDenominador();
        std::cout << "El resultado en decimal es: " << resultadoDecimal << std::endl;

        // Imprimir la resta de las fracciones en formato a/b + c/d = (ad + bc)/bd
        std::cout << "La resta de las fracciones "
          << fraccion1.getNumerador() << "/" << fraccion1.getDenominador() 
          << " + " 
          << fraccion2.getNumerador() << "/" << fraccion2.getDenominador() 
          << " es: "
          << resultadoResta.getNumerador() << "/" << resultadoResta.getDenominador() 
          << std::endl;

        double resultadoDecimal2 = static_cast<double>(resultadoResta.getNumerador()) / resultadoResta.getDenominador();
        std::cout << "El resultado en decimal es: " << resultadoDecimal2 << std::endl;


    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
