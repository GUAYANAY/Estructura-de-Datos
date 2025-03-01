/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 *                                                                                          *
 * Autor:                          Erika Guayanay, Maycol Celi, Jerson Llumiquinga          *
 * Fecha de creacion:              28/02/2025                                               *
 * Fecha de modificacion:          28/02/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/
#include <iostream>
#include "Calculo.h"

int main()
{
    try
    {
        Calculo demo;
        demo.demostrar();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}