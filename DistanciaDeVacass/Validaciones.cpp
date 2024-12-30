#include "Validaciones.h"
#include <iostream>
#include <sstream>
#include <conio.h> // for getch()

using namespace std;

bool Validaciones::esNumero(const string& str) {
    for (char const &c : str) {
        if (isdigit(c) == 0) return false;
    }
    return true;
}

string Validaciones::capturarEntrada() {
    string input;
    char ch;
    while ((ch = getch()) != '\r') { // '\r' is the Enter key
        if (isdigit(ch) || ch == '-' || ch == ' ') {
            cout << ch;
            input += ch;
        } else if (ch == '\b' && !input.empty()) { // '\b' is the Backspace key
            cout << "\b \b";
            input.pop_back();
        }
    }
    cout << endl;
    // Remove leading and trailing spaces
    input.erase(0, input.find_first_not_of(' '));
    input.erase(input.find_last_not_of(' ') + 1);
    return input;
}

bool Validaciones::validarFormatoIntervalo(const string& str) {
    stringstream ss(str);
    string a_str, b_str;
    ss >> a_str >> b_str;
    if (ss.rdbuf()->in_avail() != 0 || a_str.empty() || b_str.empty()) { // Check if there are more than two numbers or if any number is missing
        return false;
    }
    if (!esNumero(a_str) || !esNumero(b_str)) {
        return false;
    }
    long long a = stoll(a_str);
    long long b = stoll(b_str);
    if (a < 0 || a > 100 || b < 0 || b > 100) {
        return false;
    }
    return true;
}

void Validaciones::leerDatos(int& N, int& M, vector<pair<long long, long long>>& intervalos) {
    string input;
    while (true) {
        cout << "Ingrese el numero de vacas y el numero de intervalos: ";
        input = capturarEntrada();
        if (input.empty()) {
            cout << "Entrada vacia. Por favor, ingrese los datos." << endl;
            continue;
        }
        stringstream ss(input);
        string n_str, m_str;
        ss >> n_str >> m_str;
        if (ss.rdbuf()->in_avail() != 0 || n_str.empty() || m_str.empty()) { // Check if there are more than two numbers or if any number is missing
            cout << "Entrada invalida. Por favor, ingrese solo dos numeros." << endl;
            continue;
        }
        if (esNumero(n_str) && esNumero(m_str)) {
            try {
                N = stoi(n_str);
                M = stoi(m_str);
                break;
            } catch (const invalid_argument& e) {
                cout << "Entrada invalida. Por favor, ingrese solo numeros." << endl;
            } catch (const out_of_range& e) {
                cout << "Numero fuera de rango. Por favor, ingrese un numero valido." << endl;
            }
        } else {
            cout << "Entrada invalida. Por favor, ingrese solo numeros." << endl;
        }
    }

    intervalos.clear(); // Clear any previous data
    for (int i = 0; i < M; ++i) {
        while (true) {
            cout << "Ingrese el intervalo " << i + 1 << " en el formato [a b]: ";
            input = capturarEntrada();
            if (input.empty()) {
                cout << "Entrada vacia. Por favor, ingrese los datos." << endl;
                continue;
            }
            if (validarFormatoIntervalo(input)) {
                stringstream ss(input);
                string a_str, b_str;
                ss >> a_str >> b_str;
                try {
                    long long a = stoll(a_str);
                    long long b = stoll(b_str);
                    intervalos.push_back(make_pair(a, b));
                    break;
                } catch (const invalid_argument& e) {
                    cout << "Entrada invalida. Por favor, ingrese solo numeros." << endl;
                } catch (const out_of_range& e) {
                    cout << "Numero fuera de rango. Por favor, ingrese un numero valido." << endl;
                }
            } else {
                cout << "Entrada invalida. Por favor, ingrese solo dos numeros en el formato [a b] entre 0 y 100." << endl;
            }
        }
    }
}
