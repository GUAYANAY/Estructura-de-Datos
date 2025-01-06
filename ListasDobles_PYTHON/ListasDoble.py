"""
***********************************************************************
* UNIVERSIDAD DE LAS FUERZAS ARMADAS "ESPE"
* ALUMNOS:  Erika Guayanay
* FECHA ENTREGA: 06 de enero de 2025
* PROGRAMA: Listas Circulares en python.
* NRC: 1992
***********************************************************************
"""

import os
from Nodo import Nodo

class ListaDoble:
    def __init__(self):
        self.primero = None
        self.ultimo = None

    def __del__(self):
        while self.primero:
            temp = self.primero
            self.primero = self.primero.get_siguiente()
            del temp

    def validar_cedula_unica(self, cedula):
        temp = self.primero
        while temp:
            if temp.get_cedula() == cedula:
                return False
            temp = temp.get_siguiente()
        return True

    def insertar(self, cedula, nombre, apellido):
        if not self.validar_cedula_unica(cedula):
            print("Error: La cedula ya existe en la lista.")
            return

        nuevo = Nodo(cedula, nombre, apellido)
        if not self.primero:
            self.primero = nuevo
            self.ultimo = nuevo
        else:
            self.ultimo.set_siguiente(nuevo)
            nuevo.set_anterior(self.ultimo)
            self.ultimo = nuevo

    def buscar(self, cedula):
        try:
            with open("personas.txt", "r") as archivo:
                for linea in archivo:
                    archivo_cedula, nombre, apellido = linea.strip().split(',')
                    if archivo_cedula == cedula:
                        print("Persona encontrada")
                        print(f"Cedula: {archivo_cedula}")
                        print(f"Nombre: {nombre}")
                        print(f"Apellido: {apellido}")
                        return Nodo(archivo_cedula, nombre, apellido)
        except FileNotFoundError:
            print("Error al abrir el archivo personas.txt.")
        print(f"La cedula {cedula} no existe en el archivo personas.txt.")
        return None

    def eliminar(self, cedula):
        temp = self.primero
        while temp and temp.get_cedula() != cedula:
            temp = temp.get_siguiente()

        if not temp:
            print(f"Persona con cedula {cedula} no encontrada.")
            return False

        if temp == self.primero:
            self.primero = temp.get_siguiente()
            if self.primero:
                self.primero.set_anterior(None)
            else:
                self.ultimo = None
        elif temp == self.ultimo:
            self.ultimo = temp.get_anterior()
            if self.ultimo:
                self.ultimo.set_siguiente(None)
            else:
                self.primero = None
        else:
            temp.get_anterior().set_siguiente(temp.get_siguiente())
            temp.get_siguiente().set_anterior(temp.get_anterior())

        del temp

        try:
            with open("personas.txt", "r") as archivo_entrada, open("personas_temp.txt", "w") as archivo_temporal:
                for linea in archivo_entrada:
                    archivo_cedula, nombre, apellido = linea.strip().split(',')
                    if archivo_cedula != cedula:
                        archivo_temporal.write(f"{archivo_cedula},{nombre},{apellido}\n")
        except FileNotFoundError:
            print("Error al abrir los archivos.")
            return False

        os.remove("personas.txt")
        os.rename("personas_temp.txt", "personas.txt")
        return True

    def eliminar_caracter(self, cedula, caracter, lista_auxiliar):
        try:
            temp = self.buscar(cedula)
            if not temp:
                return False

            nombre = temp.get_nombre()
            apellido = temp.get_apellido()

            if caracter not in nombre and caracter not in apellido:
                print("Caracter no encontrado en el nombre o apellido.")
                return False

            nuevo_nombre = nombre.replace(caracter, '')
            nuevo_apellido = apellido.replace(caracter, '')
            temp.set_nombre(nuevo_nombre)
            temp.set_apellido(nuevo_apellido)
            lista_auxiliar.insertar(temp.get_cedula(), nuevo_nombre, nuevo_apellido)
            self.actualizar_archivo(cedula, nuevo_nombre, nuevo_apellido)
            print("Caracter eliminado correctamente del archivo y lista auxiliar actualizada.")
            return True
        except Exception as e:
            print(f"Error al eliminar caracter: {e}")
            return False

    def cifrar_caracter(self, cedula, caracter, desplazamiento, lista_auxiliar):
        try:
            temp = self.buscar(cedula)
            if not temp:
                return

            nombre = temp.get_nombre()
            apellido = temp.get_apellido()

            if caracter.lower() not in nombre.lower() and caracter.lower() not in apellido.lower():
                print("Caracter no encontrado en el nombre o apellido.")
                return

            def cifrar(c, desplazamiento):
                if c.isalpha():
                    base = ord('A') if c.isupper() else ord('a')
                    return chr((ord(c) - base + desplazamiento) % 26 + base)
                return c

            nuevo_nombre = ''.join(cifrar(c, desplazamiento) if c.lower() == caracter.lower() else c for c in nombre)
            nuevo_apellido = ''.join(cifrar(c, desplazamiento) if c.lower() == caracter.lower() else c for c in apellido)
            temp.set_nombre(nuevo_nombre)
            temp.set_apellido(nuevo_apellido)
            lista_auxiliar.insertar(temp.get_cedula(), nuevo_nombre, nuevo_apellido)
            self.actualizar_archivo(cedula, nuevo_nombre, nuevo_apellido)
            print(f"Caracter cifrado correctamente con desplazamiento {desplazamiento}. Archivo actualizado y lista auxiliar actualizada.")
        except Exception as e:
            print(f"Error al cifrar caracter: {e}")

    def actualizar_archivo(self, cedula, nuevo_nombre=None, nuevo_apellido=None):
        try:
            with open("personas.txt", "r") as archivo_entrada, open("personas_temp.txt", "w") as archivo_temporal:
                for linea in archivo_entrada:
                    archivo_cedula, nombre, apellido = linea.strip().split(',')
                    if archivo_cedula == cedula:
                        if nuevo_nombre and nuevo_apellido:
                            archivo_temporal.write(f"{archivo_cedula},{nuevo_nombre},{nuevo_apellido}\n")
                    else:
                        archivo_temporal.write(linea)
            os.remove("personas.txt")
            os.rename("personas_temp.txt", "personas.txt")
        except FileNotFoundError:
            print("Error al abrir los archivos.")

    def guardar_en_archivo(self, cedula, nombre, apellido, nombre_archivo):
        try:
            with open(nombre_archivo, "a") as archivo:
                archivo.write(f"{cedula},{nombre},{apellido}\n")
        except Exception as e:
            print(f"Error al guardar en archivo: {e}")

    def mostrar(self):
        try:
            temp = self.primero
            if not temp:
                print("NULL")
                return
            while temp:
                print(f"\nCedula: {temp.get_cedula()}\nNombre: {temp.get_nombre()}\nApellido: {temp.get_apellido()} ->\n")
                temp = temp.get_siguiente()
        except Exception as e:
            print(f"Error al mostrar la lista: {e}")

    def cargar_desde_archivo(self, nombre_archivo):
        try:
            with open(nombre_archivo, "r") as archivo:
                for linea in archivo:
                    cedula, nombre, apellido = linea.strip().split(',')
                    self.insertar(cedula, nombre, apellido)
        except FileNotFoundError:
            print("No se pudo abrir el archivo.")
        except Exception as e:
            print(f"Error al cargar desde archivo: {e}")