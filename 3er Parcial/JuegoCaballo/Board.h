#ifndef BOARD_H
#define BOARD_H

#include <vector>

class Board {
public:
    Board(int size);
    void print() const;
    void draw() const; // Nueva función para graficar el tablero
    void setPiece(int x, int y, char piece);
    bool isValidPosition(int x, int y) const;
    void markPosition(int x, int y, char mark);

private:
    std::vector<std::vector<char>> board;
};

#endif // BOARD_H
