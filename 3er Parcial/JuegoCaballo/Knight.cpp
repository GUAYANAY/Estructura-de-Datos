#include "Knight.h"

const int Knight::moves[8][2] = {
    {2, 1}, {1, 2}, {-1, 2}, {-2, 1},
    {-2, -1}, {-1, -2}, {1, -2}, {2, -1}
};

Knight::Knight(int x, int y) : x(x), y(y) {}

void Knight::markMoves(Board& board) const {
    for (auto& move : moves) {
        int newX = x + move[0];
        int newY = y + move[1];
        if (board.isValidPosition(newX, newY)) {
            board.markPosition(newX, newY, 'O');
        }
    }
}
