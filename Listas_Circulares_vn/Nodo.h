/***********************************************************************
 * Module:  Nodo.h
 * Author:  Erika Guayanay
 * Date: 25/11/2024
 * Purpose: Lista de Personas con Listas Circulares
 * University: Universidad de las Fuerzas Armadas - ESPE
 ***********************************************************************/
#pragma once
#include <iostream>
#include <string>

using namespace std;

class Nodo {
private:
    string cedula;
    string nombre;
    string apellido;
    Nodo* siguiente;
public:
    Nodo(string, string, string);
    string getCedula();
    string getNombre();
    string getApellido();
    void setNombre(string);
    void setApellido(string);
    Nodo* getSiguiente();
    void setSiguiente(Nodo*);
};
