#ifndef KNIGHT_H
#define KNIGHT_H

#include "Board.h"

class Knight {
public:
    Knight(int x, int y);
    void markMoves(Board& board) const;

private:
    int x, y;
    static const int moves[8][2];
};

#endif // KNIGHT_H
