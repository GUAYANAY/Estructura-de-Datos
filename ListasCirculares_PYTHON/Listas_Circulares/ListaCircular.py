"""
***********************************************************************
* UNIVERSIDAD DE LAS FUERZAS ARMADAS "ESPE"
* ALUMNOS:  Erika Guayanay
* FECHA ENTREGA: 06 de enero de 2025
* PROGRAMA: Listas Circulares en python.
* NRC: 1992
***********************************************************************
"""

from NodoCircular import NodoCircular
import os

class ListaCircular:
    def __init__(self):
        self.primero = None
        self.ultimo = None

    def insertar(self, cedula, nombre, apellido):
        nuevo = NodoCircular(cedula, nombre, apellido)
        if self.primero is None:
            self.primero = nuevo
            self.ultimo = nuevo
            self.ultimo.set_siguiente(self.primero)
        else:
            self.ultimo.set_siguiente(nuevo)
            self.ultimo = nuevo
            self.ultimo.set_siguiente(self.primero)

    def buscar(self, cedula):
        if self.primero is None:
            return None
        temp = self.primero
        while True:
            if temp.get_cedula() == cedula:
                return temp
            temp = temp.get_siguiente()
            if temp == self.primero:
                break
        return None

    def eliminar(self, cedula):
        if self.primero is None:
            return False
        temp = self.primero
        anterior = self.ultimo
        while True:
            if temp.get_cedula() == cedula:
                if temp == self.primero:
                    if self.primero == self.ultimo:
                        self.primero = None
                        self.ultimo = None
                    else:
                        self.primero = self.primero.get_siguiente()
                        self.ultimo.set_siguiente(self.primero)
                elif temp == self.ultimo:
                    self.ultimo = anterior
                    self.ultimo.set_siguiente(self.primero)
                else:
                    anterior.set_siguiente(temp.get_siguiente())
                return True
            anterior = temp
            temp = temp.get_siguiente()
            if temp == self.primero:
                break
        return False

    def eliminar_de_archivo(self, cedula, nombre_archivo):
        with open(nombre_archivo, "r") as archivo_entrada, open("personas_temp.txt", "w") as archivo_temporal:
            for linea in archivo_entrada:
                if not linea.startswith(cedula + ","):
                    archivo_temporal.write(linea)
        os.remove(nombre_archivo)
        os.rename("personas_temp.txt", nombre_archivo)
        self.eliminar(cedula)  # Remove the node from the list

    def eliminar_de_cubetas(self, cedula):
        for i in range(26):
            cubeta_nombre = f"cubeta_{i}.txt"
            if os.path.isfile(cubeta_nombre):
                with open(cubeta_nombre, "r") as archivo_entrada, open(f"temp_{cubeta_nombre}", "w") as archivo_temp:
                    for linea in archivo_entrada:
                        if not linea.startswith(cedula + ","):
                            archivo_temp.write(linea)
                os.remove(cubeta_nombre)
                os.rename(f"temp_{cubeta_nombre}", cubeta_nombre)

    def mostrar(self):
        if self.primero is None:
            print("NULL")
            return
        temp = self.primero
        while True:
            print(f"\nCedula: {temp.get_cedula()}, \nNombre: {temp.get_nombre()}, \nApellido: {temp.get_apellido()} ->", end=" ")
            temp = temp.get_siguiente()
            if temp == self.primero:
                break
        print()

    def eliminar_caracter(self, cedula, caracter, lista_auxiliar):
        temp = self.buscar(cedula)
        if temp is None:
            print("Cedula no encontrada.")
            return

        # Convert both the character and the name to lowercase for case-insensitive replacement
        nuevo_nombre = temp.get_nombre().replace(caracter.lower(), '').replace(caracter.upper(), '')
        nuevo_apellido = temp.get_apellido().replace(caracter.lower(), '').replace(caracter.upper(), '')

        temp.set_nombre(nuevo_nombre)
        temp.set_apellido(nuevo_apellido)
        lista_auxiliar.insertar(temp.get_cedula(), nuevo_nombre, nuevo_apellido)

        with open("personas.txt", "r") as archivo_entrada, open("personas_temp.txt", "w") as archivo_temporal:
            for linea in archivo_entrada:
                datos = linea.strip().split(',')
                if datos[0] == cedula:
                    archivo_temporal.write(f"{datos[0]},{nuevo_nombre},{nuevo_apellido}\n")
                else:
                    archivo_temporal.write(linea)

        os.remove("personas.txt")
        os.rename("personas_temp.txt", "personas.txt")

        print("Caracter eliminado correctamente del archivo y lista auxiliar actualizada.")

    def cifrar_caracter(self, cedula, caracter, desplazamiento, lista_auxiliar):
        temp = self.buscar(cedula)
        if temp is None:
            print("Cedula no encontrada.")
            return

        def cifrar(c):
            if c.lower() == caracter.lower() and c.isalpha():
                base = 'a' if c.islower() else 'A'
                return chr((ord(c) - ord(base) + desplazamiento) % 26 + ord(base))
            return c

        nuevo_nombre = ''.join(cifrar(c) for c in temp.get_nombre())
        nuevo_apellido = ''.join(cifrar(c) for c in temp.get_apellido())

        temp.set_nombre(nuevo_nombre)
        temp.set_apellido(nuevo_apellido)

        lista_auxiliar.insertar(temp.get_cedula(), nuevo_nombre, nuevo_apellido)

        with open("personas.txt", "r") as archivo_entrada, open("personas_temp.txt", "w") as archivo_temporal:
            for linea in archivo_entrada:
                datos = linea.strip().split(',')
                if datos[0] == cedula:
                    archivo_temporal.write(f"{datos[0]},{nuevo_nombre},{nuevo_apellido}\n")
                else:
                    archivo_temporal.write(linea)

        os.remove("personas.txt")
        os.rename("personas_temp.txt", "personas.txt")

        print(f"Caracter cifrado correctamente con desplazamiento {desplazamiento}. Archivo actualizado y lista auxiliar actualizada.")

    def guardar_en_archivo(self, cedula, nombre, apellido, nombre_archivo):
        with open(nombre_archivo, "a") as archivo:
            archivo.write(f"{cedula},{nombre},{apellido}\n")

    def cargar_desde_archivo(self, nombre_archivo):
        if not os.path.isfile(nombre_archivo):
            print("No se pudo abrir el archivo.")
            return

        with open(nombre_archivo, "r") as archivo:
            for linea in archivo:
                datos = linea.strip().split(',')
                if len(datos) == 3:
                    self.insertar(datos[0], datos[1], datos[2])
