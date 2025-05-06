#include "Board.h"
#include <iostream>
#include <graphics.h> // Incluir la librería graphics.h

Board::Board(int size) : board(size, std::vector<char>(size, '.')) {}

void Board::print() const {
    for (const auto& row : board) {
        for (const auto& cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
}

void Board::draw() const {
    int gd = DETECT, gm;
    char driver[] = ""; // Corregir la advertencia de conversión
    initgraph(&gd, &gm, driver);

    int cellSize = 50;
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board.size(); ++j) {
            int left = j * cellSize;
            int top = i * cellSize;
            int right = left + cellSize;
            int bottom = top + cellSize;
            rectangle(left, top, right, bottom);
            if (board[i][j] == 'C') {
                setfillstyle(SOLID_FILL, BLUE);
                floodfill((left + right) / 2, (top + bottom) / 2, WHITE);
            } else if (board[i][j] == 'O') {
                setfillstyle(SOLID_FILL, GREEN);
                floodfill((left + right) / 2, (top + bottom) / 2, WHITE);
            }
        }
    }

    getch();
    closegraph();
}

void Board::setPiece(int x, int y, char piece) {
    if (isValidPosition(x, y)) {
        board[x][y] = piece;
    }
}

bool Board::isValidPosition(int x, int y) const {
    return x >= 0 && x < board.size() && y >= 0 && y < board.size();
}

void Board::markPosition(int x, int y, char mark) {
    if (isValidPosition(x, y)) {
        board[x][y] = mark;
    }
}
