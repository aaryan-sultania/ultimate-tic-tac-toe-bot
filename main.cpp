#include <iostream>
#include "game.hpp"
#include "mcts.hpp"
#include <vector>
#include <chrono>


int main () {
    std::srand(std::time(nullptr)); // Seed random number generator

    MCTS mcts;
    while (mcts.root_state->game_over == false) {
        for (int i = 0; i < 1500000; i++) {
            mcts.runTree();
        }
        Move best_move = Move(mcts.bestMove());
        mcts.makeMove(&best_move);
        std::cout << "Move: " << best_move.macro_square << " " << best_move.micro_square << std::endl;
    }
    std::cout << "Game Over! Winner: " << mcts.root_state->winner << std::endl;
    return 0;

    while (mcts.root_state->game_over == false) {
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 5; i++) {
            mcts.runTree();
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Computation time: " << duration.count() << " microseconds" << std::endl;
        Move best_move = Move(mcts.bestMove());

        std::cout << "My move: " << best_move.macro_square << " " << best_move.micro_square << std::endl;
        mcts.makeMove(&best_move);
        std::cout << "My chance of winning: " << (float) mcts.root_node->num_wins / (float) mcts.root_node->num_visted<< std::endl;
        int mac, mic;
        std::cout << "Your move: ";
        std::cin >> mac >> mic;
        Move* playerMove = new Move(mac, mic);
        mcts.makeMove(playerMove);
        delete playerMove;
    }
    for (int i = 0; i < 50000; i++) {
        mcts.runTree();
    }
    Move best_opener = Move(mcts.bestMove());
    std::cout << best_opener.macro_square << best_opener.micro_square << std::endl;
    mcts.makeMove(&best_opener);
};
