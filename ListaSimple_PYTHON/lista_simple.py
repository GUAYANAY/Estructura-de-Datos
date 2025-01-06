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
from nodo import Nodo

class ListaSimple:
    def __init__(self):
        self.cabeza = None

    def __del__(self):
        while self.cabeza:
            temp = self.cabeza
            self.cabeza = self.cabeza.get_siguiente()
            del temp

    def validar_cedula_unica(self, cedula):
        try:
            temp = self.cabeza
            while temp:
                if temp.get_cedula() == cedula:
                    return False
                temp = temp.get_siguiente()
            return True
        except Exception as e:
            print(f"Error al validar cédula única: {e}")
            return False

    def insertar_a_cola(self, cedula, nombre, apellido):
        try:
            if not self.validar_cedula_unica(cedula):
                print("Error: La cedula ya existe en la lista.")
                return
            nuevo = Nodo(cedula, nombre, apellido)
            if not self.cabeza:
                self.cabeza = nuevo
            else:
                temp = self.cabeza
                while temp.get_siguiente():
                    temp = temp.get_siguiente()
                temp.set_siguiente(nuevo)
        except Exception as e:
            print(f"Error al insertar a cola: {e}")

    def buscar(self, cedula):
        try:
            with open("personas.txt", "r") as archivo:
                for linea in archivo:
                    archivo_cedula, nombre, apellido = linea.strip().split(',')
                    if archivo_cedula == cedula:
                        print(f"\n--Persona encontrada--\nCedula: {archivo_cedula}\nNombre: {nombre}\nApellido: {apellido}")
                        return Nodo(archivo_cedula, nombre, apellido)
        except FileNotFoundError:
            print("Error al abrir el archivo personas.txt.")
        except Exception as e:
            print(f"Error al buscar persona: {e}")
        print(f"La cedula {cedula} no existe en el archivo personas.txt.")
        return None

    def eliminar(self, cedula):
        try:
            temp = self.cabeza
            anterior = None
            while temp:
                if temp.get_cedula() == cedula:
                    if not anterior:
                        self.cabeza = temp.get_siguiente()
                    else:
                        anterior.set_siguiente(temp.get_siguiente())
                    del temp
                    self.actualizar_archivo(cedula)
                    return True
                anterior = temp
                temp = temp.get_siguiente()
            return False
        except Exception as e:
            print(f"Error al eliminar persona: {e}")
            return False

    def mostrar(self):
        try:
            temp = self.cabeza
            if not temp:
                print("\nNULL\n")
                return
            while temp:
                print(f"\nCedula: {temp.get_cedula()}\nNombre: {temp.get_nombre()}\nApellido: {temp.get_apellido()} -> ", end="")
                temp = temp.get_siguiente()
            print("\nNULL\n")
        except Exception as e:
            print(f"Error al mostrar lista: {e}")

    def eliminar_caracter(self, cedula, caracter, lista_auxiliar):
        try:
            temp = self.buscar(cedula)
            if not temp:
                return False
            if caracter.lower() not in temp.get_nombre().lower() and caracter.lower() not in temp.get_apellido().lower():
                print("Caracter no encontrado en el nombre o apellido.")
                return False
            nuevo_nombre = ''.join('' if c.lower() == caracter.lower() else c for c in temp.get_nombre())
            nuevo_apellido = ''.join('' if c.lower() == caracter.lower() else c for c in temp.get_apellido())
            temp.set_nombre(nuevo_nombre)
            temp.set_apellido(nuevo_apellido)
            lista_auxiliar.insertar_a_cola(temp.get_cedula(), nuevo_nombre, nuevo_apellido)
            self.actualizar_archivo(temp.get_cedula(), nuevo_nombre, nuevo_apellido)
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
            lista_auxiliar.insertar_a_cola(temp.get_cedula(), nuevo_nombre, nuevo_apellido)
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
        except Exception as e:
            print(f"Error al actualizar archivo: {e}")

    def guardar_en_archivo(self, cedula, nombre, apellido, nombre_archivo):
        try:
            with open(nombre_archivo, 'a') as archivo:
                archivo.write(f"{cedula},{nombre},{apellido}\n")
        except FileNotFoundError:
            print("Error al abrir el archivo para escritura.")
        except Exception as e:
            print(f"Error al guardar en archivo: {e}")

    def cargar_desde_archivo(self, nombre_archivo):
        try:
            with open(nombre_archivo, 'r') as archivo:
                for linea in archivo:
                    cedula, nombre, apellido = linea.strip().split(',')
                    self.insertar_a_cola(cedula, nombre, apellido)
        except FileNotFoundError:
            print("No se pudo abrir el archivo.")
        except Exception as e:
            print(f"Error al cargar desde archivo: {e}")
