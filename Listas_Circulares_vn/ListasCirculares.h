/***********************************************************************
 * Module:  ListasCirculares.h
 * Author:  Erika Guayanay
 * Date: 25/11/2024
 * Purpose: Lista de Personas con Listas Circulares
 * University: Universidad de las Fuerzas Armadas - ESPE
 ***********************************************************************/
#pragma once
#include "Nodo.h"

using namespace std;

class ListaCircular {
private:
    Nodo* primero;
    Nodo* ultimo;
public:
    ListaCircular();
    void insertar(string, string, string);
    Nodo* buscar(string);
    bool eliminar(string);
    void mostrar();
    void eliminarCaracter(string, char);
    bool validarCedulaUnica(string);
};
