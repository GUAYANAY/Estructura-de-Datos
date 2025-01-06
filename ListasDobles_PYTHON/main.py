"""
***********************************************************************
* UNIVERSIDAD DE LAS FUERZAS ARMADAS "ESPE"
* ALUMNOS:  Erika Guayanay
* FECHA ENTREGA: 06 de enero de 2025
* PROGRAMA: Listas Circulares en python.
* NRC: 1992
***********************************************************************
"""

from ListasDoble import ListaDoble
from Validaciones import *
from MetodoOrdenamientoExterno import MetodoOrdenamientoExterno
import os

def main():
    lista_principal = ListaDoble()
    lista_auxiliar = ListaDoble()
    metodo_ordenamiento = MetodoOrdenamientoExterno()
    cedula, nombre, apellido = "", "", ""
    desplazamiento = 0
    caracter = ''
    opcion = 0

    lista_principal.cargar_desde_archivo("personas.txt")

    while opcion != 10:
        os.system("cls" if os.name == "nt" else "clear")
        print("\n----------------------------------------------------")
        print("\t\t MENU DE OPCIONES\t\t")
        print("----------------------------------------------------")
        print("1. Insertar persona")
        print("2. Buscar persona")
        print("3. Eliminar persona")
        print("4. Mostrar lista")
        print("5. Eliminar caracter de nombre")
        print("6. Cifrar un caracter")
        print("7. Mostrar lista auxiliar")
        print("8. Ordenar lista por nombre (Distribution Sort)")
        print("9. Mostrar archivo de distribucion ordenado")
        print("10. Salir")
        opcion = capturar_solo_numeros()

        if opcion == 1:
            while True:
                print("Ingrese cedula: ")
                cedula = capturar_solo_numeros_bloqueado()
                if not validar_cedula_real(cedula):
                    print("Cedula invalida. Intente de nuevo.")
                    continue
                if not validar_cedula_unica(cedula):
                    print("La cedula ya esta registrada. Intente de nuevo.")
                    continue
                break

            while True:
                print("Ingrese nombre: ")
                nombre = capturar_solo_letras_bloqueado()
                nombre = normalizar_nombre(nombre)
                if not validar_solo_letras(nombre):
                    print("Error: El nombre debe contener solo letras. Intente nuevamente.")
                else:
                    break

            while True:
                print("Ingrese apellido: ")
                apellido = capturar_solo_letras_bloqueado()
                apellido = normalizar_nombre(apellido)
                if not validar_solo_letras(apellido):
                    print("Error: El apellido debe contener solo letras. Intente nuevamente.")
                else:
                    break

            lista_principal.insertar(cedula, nombre, apellido)
            lista_principal.guardar_en_archivo(cedula, nombre, apellido, "personas.txt")
            print("Persona registrada exitosamente.")

        elif opcion == 2:
            while True:
                print("Ingrese cedula para buscar: ")
                cedula = capturar_solo_numeros_bloqueado()
                if not validar_cedula_real(cedula):
                    print("Cedula invalida. Intente de nuevo.")
                else:
                    break

            persona = lista_principal.buscar(cedula)
            if persona is None:
                print("Persona no encontrada.")

        elif opcion == 3:
            while True:
                print("Ingrese cedula a eliminar: ")
                cedula = capturar_solo_numeros_bloqueado()
                if not validar_cedula_real(cedula):
                    print("Cedula invalida. Intente de nuevo.")
                else:
                    break

            if lista_principal.eliminar(cedula):
                print("Persona eliminada exitosamente.")
            else:
                print("Error: Persona no encontrada o no pudo ser eliminada.")

        elif opcion == 4:
            lista_principal.mostrar()

        elif opcion == 5:
            print("Ingrese cedula: ")
            cedula = capturar_solo_numeros_bloqueado()
            if not validar_cedula_real(cedula):
                print("Cedula invalida. Intente de nuevo.")
                input("Presione Enter para continuar...")
                continue
            if not lista_principal.buscar(cedula):
                print("Error: Persona no encontrada.")
                input("Presione Enter para continuar...")
                continue

            print("Ingrese caracter a eliminar: ")
            caracter = capturar_una_letra_bloqueado()
            lista_principal.eliminar_caracter(cedula, caracter, lista_auxiliar)
            input("Presione Enter para continuar...")
            continue

        elif opcion == 6:
            print("Ingrese cedula: ")
            cedula = capturar_solo_numeros_bloqueado()
            if not validar_cedula_real(cedula):
                print("Cedula invalida. Intente de nuevo.")
                input("Presione Enter para continuar...")
                continue
            if not lista_principal.buscar(cedula):
                print("Error: Persona no encontrada.")
                input("Presione Enter para continuar...")
                continue

            print("Ingrese caracter a cifrar: ")
            caracter = capturar_una_letra_bloqueado()
            print("\nIngrese desplazamiento: ")
            desplazamiento = capturar_numero_1_a_25_bloqueado()
            lista_principal.cifrar_caracter(cedula, caracter, desplazamiento, lista_auxiliar)
            input("Presione Enter para continuar...")
            continue

        elif opcion == 7:
            lista_auxiliar.mostrar()

        elif opcion == 8:
            if not os.path.exists("personas.txt") or os.path.getsize("personas.txt") == 0:
                print("El archivo 'personas.txt' no existe o esta vacio. No hay datos para procesar.")
                input("Presione Enter para continuar...")
                continue

            archivos_cubetas = []
            metodo_ordenamiento.distribuir_datos("personas.txt", archivos_cubetas)
            for archivo in archivos_cubetas:
                metodo_ordenamiento.ordenar_archivo(archivo)
            metodo_ordenamiento.fusionar_archivos(archivos_cubetas, "personas_ordenadas.txt")
            print("La lista ha sido ordenada y guardada en 'personas_ordenadas.txt'.")

        elif opcion == 9:
            if not os.path.exists("personas_ordenadas.txt") or os.path.getsize("personas_ordenadas.txt") == 0:
                print("El archivo 'personas_ordenadas.txt' no existe o esta vacio. No hay datos para mostrar.")
                input("Presione Enter para continuar...")
                continue

            metodo_ordenamiento.mostrar_archivo("personas_ordenadas.txt")

        elif opcion == 10:
            print("Saliendo...")

        else:
            print("Opcion invalida. Intente de nuevo.")

        input("Presione Enter para continuar...")

if __name__ == "__main__":
    main()