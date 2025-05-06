#include <iostream>
#include "Board.h"
#include "Knight.h"

using namespace std;

int main() {
    int n;
    cout << "Ingrese la cantidad de la tabla: ";
    cin >> n;

    Board board(n);

    int knightX, knightY;
    cout << "Ingrese la posición del caballo (x y): ";
    cin >> knightX >> knightY;

    Knight knight(knightX, knightY);
    board.setPiece(knightX, knightY, 'C');
    knight.markMoves(board);

    board.print();
    board.draw(); // Llamar a la función para graficar el tablero

    return 0;
}
