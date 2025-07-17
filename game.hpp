#ifndef GAME_HEADER_HPP
#define GAME_HEADER_HPP

#include <vector>

class Move
{
public:
    int macro_square;
    int micro_square;

    Move(int mac, int mic);
    Move(const Move &other);
    bool operator==(const Move &other);
};

class State
{
public:
    int turn;
    int board[9][9];
    int macro_claims[9];
    bool game_over;
    int winner;
    Move *p_last_move;

    void createLegalMoves(std::vector<Move *> &moves);
    void executeMove(Move *m);
    void reverseMove(Move *m);
    int getNextTurn();
    State();
    State(const State &other);
};

const int win_rows[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};

#endif