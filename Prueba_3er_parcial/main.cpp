/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 *                                                                                          *
 * Autor:                          Erika Guayanay, Maycol Celi, Jerson Llumiquinga          *
 * Fecha de creacion:              28/02/2025                                               *
 * Fecha de modificacion:          25/02/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/
#include <iostream>
#include "DemostracionComplejidad.h"

int main()
{
    try
    {
        DemostracionComplejidad demo;
        demo.demostrar();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
