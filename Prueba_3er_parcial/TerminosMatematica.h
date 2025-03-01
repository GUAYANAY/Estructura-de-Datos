/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 *                                                                                          *
 * Autor:                          Erika Guayanay, Maycol Celi, Jerson Llumiquinga          *
 * Fecha de creacion:              28/02/2025                                               *
 * Fecha de modificacion:          28/02/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/
#pragma once
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <cmath> // Para usar log (logaritmo natural)

class TerminosMatematica
{
private:
    static const double E; // e ≈ 2.71828...

public:
    static double obtenerE()
    {
        return E;
    }

    // Función para calcular e * log(n)
    static double calcularELogN(double n)
{
    if (n <= 0)
        throw std::invalid_argument("n debe ser mayor que 0.");
    return E * log(n); // e * log(n)
}
};

// Definición de la constante E
const double TerminosMatematica::E = 2.71828182845904523536;