#include "ListaAutores.h"
#include "ListaLibros.h"
#include "VentanaAyuda.h"
#include "Validaciones.h"
#include <iostream>
#include <cstdlib> // Para system()
#include <limits>
//#include "hpdf.h"

// Men� para manejar las opciones de "Autores"
void menuAutores(ListaAutores& listaAutores) {
    int opcion;
    do {
        system("pause");
        system("cls");
        cout << "*****************************************************************************";
        cout << "\n\t\t\t\t MENU AUTORES \t\t\t\t\n";
         cout << "*****************************************************************************\n";
        cout << "\t1. Insertar Autor\n";
        cout << "\t2. Buscar Autor\n";
        cout << "\t3. Eliminar Autor\n";
        cout << "\t4. Mostrar Autores\n";
        cout << "\t5. Volver al menu principal\n";
        cout << "\tIngrese una opcion: ";
        ingresarOpcionMenu(opcion);

        if (!validarOpcionMenu(opcion, 1, 5)) {
            cout << "Opcion no valida. Intente de nuevo.\n";
            continue;
        }

        switch (opcion) {

       case 1: {
           string cedula, nombre, apellido, fechaPublicacion;
           while (true) {
                cout << "Ingrese la cedula: ";
                cin >> cedula;
                if (validarCedula(cedula)) break;
                cout << "Error: La cedula ingresada no es valida\n";
                }
          while (true) {
        cout << "Ingrese nombre: ";
        cin >> nombre;
        if (validarTexto(nombre)) break;
        cout << "Error: El nombre debe contener solo letras y espacios.\n";
        }
        while (true) {
        cout << "Ingrese apellido: ";
        cin >> apellido;
        if (validarTexto(apellido)) break;
        cout << "Error: El apellido debe contener solo letras y espacios.\n";
        }

        while (true) {
        cout << "Ingrese fecha de publicación (MM/dd/yyyy): ";
        cin >> fechaPublicacion;
        if (validarFecha(fechaPublicacion)) break;
        cout << "Error: La fecha debe tener el formato MM/dd/yyyy.\n";
        }

    listaAutores.insertar(cedula, nombre, apellido, fechaPublicacion);

    break;
}

       case 2: {
    string cedula;

    while (true) {
        cout << "Ingrese cedula del autor: ";
        cin >> cedula;
        if (validarCedula(cedula)) break;
        cout << "Error: La cedula ingresada no es válida\n";}

    NodoAutores* autor = listaAutores.buscar(cedula);
    if (autor) {

        cout << "Autor encontrado:\n";
        cout << "Nombre: " << autor->getNombre() << "\n";
        cout << "Apellido: " << autor->getApellido() << "\n";
    } else {

        cout << "Autor no encontrado con la cedula proporcionada.\n";
    }
    break;
}

        case 3: {
            string cedula;
    while (true) {
        cout << "Ingrese cedula del autor a eliminar: ";
        cin >> cedula;
        if (validarCedula(cedula)) break;
        cout << "Error: La cedula ingresada no es valida.\n";
    }

    bool eliminado = listaAutores.eliminar(cedula);
    if (eliminado) {
        cout << "Autor con cédula " << cedula << " eliminado exitosamente.\n";
    } else {
        cout << "Error: No se encontró un autor con la cédula proporcionada.\n";
    }
    break;
        }


        case 4:
            listaAutores.mostrar();
            break;
        case 5:
            cout << "Volviendo al menu principal...\n";
            system("pause");
            break;
        }

    } while (opcion != 5);
}

// MenU para manejar las opciones de "Libros"
void menuLibros(ListaLibros& listaLibros, ListaAutores& listaAutores) {
    int opcion;
    do {
        system("pause");
        system("cls");
       cout << "*****************************************************************************";
        cout << "\n\t\t\t\t MENU LIBROS \t\t\t\t\n";
         cout << "*****************************************************************************\n";
        cout << "1. Insertar Libro\n";
        cout << "2. Buscar Libro\n";
        cout << "3. Eliminar Libro\n";
        cout << "4. Mostrar Libros\n";
        cout << "5. Volver al menu principal\n";
        cout << "Ingrese una opcion: ";
        ingresarOpcionMenu(opcion);

        if (!validarOpcionMenu(opcion, 1, 5)) {
            cout << "Opcion no valida. Intente de nuevo.\n";
            continue;
        }

        switch (opcion) {

        case 1: {

    string titulo, isbn, genero, anioLanzamiento;
    double precio, calificacion;
    string autor = listaLibros.seleccionarAutor(listaAutores);
    if (autor.empty()) break;

    do {
        cout << "Ingrese titulo: ";
        cin.ignore();
        getline(cin, titulo);
        if (!validarTexto(titulo)) {
            cout << "Error: El titulo solo puede contener letras y espacios.\n";
        }
    } while (!validarTexto(titulo));

    do {
        cout << "Ingrese ISBN: ";
        getline(cin, isbn);
        if (!validarISBN(isbn)) {
            cout << "Error: El ISBN solo puede contener digitos y guiones.\n";
        }
    } while (!validarISBN(isbn));

    do {
        cout << "Ingrese genero: ";
        getline(cin, genero);
        if (!validarTexto(genero)) {
            cout << "Error: El genero solo puede contener letras y espacios.\n";
        }
    } while (!validarTexto(genero));

    do {
        cout << "Ingrese fecha de lanzamiento (MM/DD/AAAA): ";
        getline(cin, anioLanzamiento);
        if (!validarFecha(anioLanzamiento)) {
            cout << "Error: Fecha invalida. Usa el formato MM/DD/AAAA.\n";
        }
    } while (!validarFecha(anioLanzamiento));

    do {
        cout << "Ingrese precio: ";
        if (!ingresarNumero(precio) || !validarPrecio(precio)) {
            cout << "Error: El precio debe ser un numero positivo.\n";
        }
    } while (!validarPrecio(precio));

    do {
        cout << "Ingrese calificación (0-10): ";
        if (!ingresarNumero(calificacion) || !validarCalificacion(calificacion)) {
            cout << "Error: La calificación debe ser entre 0 y 10.\n";
        }
    } while (!validarCalificacion(calificacion));

    listaLibros.insertar(titulo, autor, isbn, anioLanzamiento, genero, precio, calificacion);
    cout << "Libro ingresado exitosamente.\n";
    break;

        }
        case 2: {
            string isbn;
            do {
        cout << "Ingrese ISBN del libro: ";
        cin >> isbn;
        if (!validarISBN(isbn)) {
            cout << "Error: El ISBN debe contener solo digitos y guiones.\n";
        }
    } while (!validarISBN(isbn));

            NodoLibros* libro = listaLibros.buscar(isbn);
            if (libro) {
                cout << "Libro encontrado: " << libro->getTitulo() << " por " << libro->getAutor() << "\n";
            } else {
                cout << "Libro no encontrado.\n";
            }
            break;
        }
        case 3: {
            string isbn;
            do {
                    cout << "Ingrese ISBN del libro: ";
                    cin >> isbn;
                    if (!validarISBN(isbn)) {
                            cout << "Error: El ISBN debe contener solo digitos y guiones.\n";}
              } while (!validarISBN(isbn));

           if (listaLibros.eliminar(isbn)) {
             cout << "El libro con ISBN " << isbn << " ha sido eliminado exitosamente.\n";
             } else {
             cout << "El libro con ISBN " << isbn << " no se encontró en la lista.\n";
            }
            break;
        }
        case 4:
            listaLibros.mostrar();
            break;
        case 5:
            cout << "Volviendo al menu principal...\n";
            system("pause");
            break;
        }
    } while (opcion != 5);
}

int main() {
    ListaLibros listaLibros;
    ListaAutores listaAutores;
    VentanaAyuda ventanaAyuda;

    listaAutores.cargarDesdeArchivoJSON();
    listaLibros.cargarDesdeArchivoJSON();

    int opcionMenu;

    do {
        system("cls");
        cout << "*****************************************************************************";
        cout << "\n\t\t\t\t MENU PRINCIPAL \t\t\t\t\n";
         cout << "*****************************************************************************\n";
        cout << "1. Manejar Autores\n";
        cout << "2. Manejar Libros\n";
        cout << "3. Ayuda\n";
        cout << "4. Salir\n";
        cout << "\n";
        cout << "Ingrese una opcion: ";
        ingresarOpcionMenu(opcionMenu);

        if (!validarOpcionMenu(opcionMenu, 1, 3)) {
            cout << "Opcion no valida. Intente de nuevo.\n";
            continue;
        }

        switch (opcionMenu) {
        case 1:
            menuAutores(listaAutores);
            break;
        case 2:
            menuLibros(listaLibros, listaAutores);
            break;
        case 3:
            ventanaAyuda.mostrar();
            break;
        case 4:
            cout << "Saliendo...\n";
            break;
        }

    } while (opcionMenu != 4);

    return 0;
}
