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
        self.anterior = None

    def get_cedula(self):
        return self.cedula

    def get_nombre(self):
        return self.nombre

    def get_apellido(self):
        return self.apellido

    def set_nombre(self, nombre):
        self.nombre = nombre

    def set_apellido(self, apellido):
        self.apellido = apellido

    def get_siguiente(self):
        return self.siguiente

    def get_anterior(self):
        return self.anterior

    def set_siguiente(self, siguiente):
        self.siguiente = siguiente

    def set_anterior(self, anterior):
        self.anterior = anterior
