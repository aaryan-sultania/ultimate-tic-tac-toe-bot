#include "game.hpp"
#include <vector>

bool checkBoardForWinner(int mmboard[9], int turn) {
    for (int i = 0; i < 8; i++) {
        if (mmboard[win_rows[i][0]] == turn && mmboard[win_rows[i][1]] == turn && mmboard[win_rows[i][2]] == turn) {
            return true;
        }
    }
    return false;
}

bool checkBoardForDraw(int mmboard[9]) {
    if (checkBoardForWinner(mmboard, 1)) return false;
    if (checkBoardForWinner(mmboard, -1)) return false;
    for (int i = 0; i < 9; i++) {
        if (mmboard[i] == 0) {
            return false;
        }
    }
    return true;
}

Move::Move(int mac, int mic) : macro_square(mac), micro_square(mic) {};
Move::Move(const Move& other) : macro_square(other.macro_square), micro_square(other.micro_square) {};


bool Move::operator==(const Move& other) {
    if(macro_square == other.macro_square & micro_square == other.micro_square) return true;
    return false;
}

State::State() : p_last_move(nullptr), turn(1), winner(0) {
    for(int i = 0; i<9; i++) {
        for(int j = 0; j<9; j++) {
           board[i][j] = 0; 
        }
        macro_claims[i] = 0;
    }
    p_last_move = new Move(4, 4);
};
State::State(const State& other) : turn(other.turn), game_over(other.game_over), winner(other.winner), p_last_move(other.p_last_move) {
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 9; j++) {
                board[i][j] = other.board[i][j];
            }
        }
        for(int i = 0; i < 9; i++) {
            macro_claims[i] = other.macro_claims[i];
        }
    };

void State::createLegalMoves(std::vector<Move*>& moves) {
    if (game_over) return;
    int new_move_macro_square = p_last_move->micro_square;
    if (macro_claims[new_move_macro_square] == 0) {
        for (int i = 0; i < 9; i++) {
            if (board[new_move_macro_square][i] == 0) {
                moves.push_back(new Move(new_move_macro_square, i));
            }
        }
    }
    else {
        for (int j = 0; j < 9; j++) {
            if (macro_claims[j] == 0) {
                for (int i = 0; i < 9; i++) {
                    if (board[j][i] == 0) {
                        moves.push_back(new Move(j, i));
                    }
                }
            }
        }
    }
};

void State::executeMove(Move* move){
    board[move->macro_square][move->micro_square] = turn;
    if (checkBoardForWinner(board[move->macro_square], turn)) {
        macro_claims[move->macro_square] = turn;
    }
    if (checkBoardForDraw(board[move->macro_square])) {
        macro_claims[move->macro_square] = 2;
    }
    if (checkBoardForWinner(macro_claims, turn)) {
        game_over = true;
        winner = turn;
    }
    if (checkBoardForDraw(macro_claims)) {
        game_over = true;
    }
    turn = getNextTurn();
    p_last_move = move;

};

int State::getNextTurn() {
    return (turn == 1) ? -1 : 1;
}