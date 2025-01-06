"""
***********************************************************************
* UNIVERSIDAD DE LAS FUERZAS ARMADAS "ESPE"
* ALUMNOS:  Erika Guayanay
* FECHA ENTREGA: 06 de enero de 2025
* PROGRAMA: Listas Circulares en python.
* NRC: 1992
***********************************************************************
"""

class Nodo:
    def __init__(self, cedula, nombre, apellido):
        self.cedula = cedula
        self.nombre = nombre
        self.apellido = apellido
        self.siguiente = None

    def get_cedula(self):
        return self.cedula

    def get_nombre(self):
        return self.nombre

    def get_apellido(self):
        return self.apellido

    def set_nombre(self, nuevo_nombre):
        self.nombre = nuevo_nombre

    def set_apellido(self, nuevo_apellido):
        self.apellido = nuevo_apellido

    def get_siguiente(self):
        return self.siguiente

    def set_siguiente(self, nuevo_siguiente):
        self.siguiente = nuevo_siguiente
