"""
***********************************************************************
* UNIVERSIDAD DE LAS FUERZAS ARMADAS "ESPE"
* ALUMNOS:  Erika Guayanay
* FECHA ENTREGA: 06 de enero de 2025
* PROGRAMA: Listas Circulares en python.
* NRC: 1992
***********************************************************************
"""

import re
import msvcrt

cedulas_registradas = set()

def validar_cedula_real(cedula):
    if len(cedula) != 10 or not cedula.isdigit():
        print("Error: La cedula debe contener exactamente 10 digitos y solo numeros.")
        return False

    provincia = int(cedula[:2])
    if provincia < 1 or provincia > 24:
        print("Error: La cedula tiene un codigo de provincia invalido.")
        return False

    digito_verificador = int(cedula[9])
    suma = 0

    for i in range(9):
        digito = int(cedula[i])
        if i % 2 == 0:
            digito *= 2
            if digito > 9:
                digito -= 9
        suma += digito

    decena_superior = (suma + 9) // 10 * 10
    calculado = decena_superior - suma

    if calculado != digito_verificador:
        print("Error: La cedula no es valida.")
        return False

    return True

def validar_cedula_unica(cedula):
    try:
        with open("personas.txt", "r") as archivo:
            for linea in archivo:
                cedula_existente = linea.split(',')[0]
                if cedula_existente == cedula:
                    return False
    except FileNotFoundError:
        return True  # Si el archivo no existe, la cédula es única
    return True

def registrar_cedula(cedula):
    cedulas_registradas.add(cedula)

def eliminar_cedula(cedula):
    cedulas_registradas.discard(cedula)

def validar_solo_letras(texto):
    return all(c.isalpha() or c.isspace() for c in texto)

def existe_cedula(cedula):
    return cedula in cedulas_registradas

def capturar_solo_numeros():
    while True:
        entrada = input("Seleccione una opcion: ")
        if entrada.isdigit():
            return int(entrada)
        print("Error: Debe ingresar solo numeros.")

def capturar_solo_letras(mensaje=""):
    while True:
        entrada = input(mensaje)
        if validar_solo_letras(entrada):
            return entrada
        print("Error: Debe ingresar solo letras.")

def normalizar_nombre(nombre):
    return nombre.capitalize()

def capturar_cedula():
    while True:
        entrada = input("Ingrese cedula: ")
        if entrada.isdigit():
            return entrada
        print("Error: Debe ingresar solo numeros.")

def capturar_una_letra():
    while True:
        entrada = input("Ingrese una letra: ")
        if len(entrada) == 1 and entrada.isalpha():
            return entrada
        print("Error: Debe ingresar una sola letra.")

def validar_numero_1a25():
    while True:
        entrada = input("Ingrese un numero entre 1 y 25: ")
        if entrada.isdigit():
            numero = int(entrada)
            if 1 <= numero <= 25:
                return numero
        print("Error: Debe ingresar un numero entre 1 y 25.")

def capturar_solo_numeros_bloqueado():
    entrada = ""
    while True:
        tecla = msvcrt.getch()
        if tecla.isdigit():
            entrada += tecla.decode()
            print(tecla.decode(), end="", flush=True)
        elif tecla == b'\r':  # Enter key
            if entrada == "":
                continue
            print()
            return entrada
        elif tecla == b'\x08':  # Backspace key
            if len(entrada) > 0:
                entrada = entrada[:-1]
                print("\b \b", end="", flush=True)

def capturar_solo_letras_bloqueado():
    entrada = ""
    while True:
        tecla = msvcrt.getch()
        if tecla.isalpha() or tecla == b' ':
            entrada += tecla.decode()
            print(tecla.decode(), end="", flush=True)
        elif tecla == b'\r':  # Enter key
            if entrada == "":
                continue  # Do not allow to proceed if input is empty
            print()
            return entrada
        elif tecla == b'\x08':  # Backspace key
            if len(entrada) > 0:
                entrada = entrada[:-1]
                print("\b \b", end="", flush=True)

def capturar_una_letra_bloqueado():
    while True:
        entrada = ""
        while True:
            tecla = msvcrt.getch()
            if tecla.isalpha() and len(entrada) == 0:
                entrada += tecla.decode()
                print(tecla.decode(), end="", flush=True)
            elif tecla == b'\r':  # Enter key
                if entrada == "":
                    continue
                print()
                return entrada
            elif tecla == b'\x08':  # Backspace key
                if len(entrada) > 0:
                    entrada = entrada[:-1]
                    print("\b \b", end="", flush=True)

def capturar_numero_1_a_25_bloqueado():
    while True:
        entrada = ""
        while True:
            tecla = msvcrt.getch()
            if tecla.isdigit() and len(entrada) < 2 and tecla != b'0':  # Allow only up to 2 digits and block 0
                entrada += tecla.decode()
                print(tecla.decode(), end="", flush=True)
            elif tecla == b'\r':
                if entrada == "":
                    continue
                if not (1 <= int(entrada) <= 25):
                    print("\nError: El número debe estar entre 1 y 25.")
                    entrada = ""
                    break  # Break to allow re-entry
                print()
                return int(entrada)
            elif tecla == b'\x08':
                if len(entrada) > 0:
                    entrada = entrada[:-1]
                    print("\b \b", end="", flush=True)