#include <iostream>
#include "game.hpp"
#include "mcts.hpp"
#include <vector>
#include <chrono>
#include <cstring>

const char* self_play_flag = "-S";
const char* versusAsX_flag = "-vsX";
const char* versusAsO_flag = "-vsO";

int main (int argc, char* argv[]) {
    std::srand(std::time(nullptr)); // Seed random number generator

    bool selfPlay = false;
    bool versusX = false;
    bool versusO = false;

    if (!(argc == 3)) {
        std::cout << "Usage: [number of sumulations per move] [-S | -vsX |  -vsO]" << std::endl;
        return 1;
    }
    int simulations_per_move = std::stoi(argv[1]);
    if (simulations_per_move <= 0) {
        std::cout << "Number of simulations per move must be a positive integer." << std::endl;
        return 1;
    }

    if (strcmp(argv[2], self_play_flag) == 0) selfPlay = true;
    else if (strcmp(argv[2], versusAsX_flag) == 0) versusX = true;
    else if (strcmp(argv[2], versusAsO_flag) == 0) versusO = true;
    else {
        std::cout << "Invalid flag. Use -S for self play, -vsX to play as X, or -vsO to play as O." << std::endl;
        return 1;
    }

    MCTS mcts;

    if (versusO == true) {
        mcts.runTree();
        int initmac, initmic;
        std::cout << "Your move: ";
        std::cin >> initmac >> initmic;
        Move* initplayerMove = new Move(initmac, initmic);
        mcts.makeMove(initplayerMove);
        delete initplayerMove;
    }
    while (mcts.root_state->game_over == false) {
        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < simulations_per_move; i++) {
            mcts.runTree();
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Computation time: " << duration.count() << " microseconds" << std::endl;

        Move best_move = Move(mcts.bestMove());

        std::cout << "My move: " << best_move.macro_square << " " << best_move.micro_square << std::endl;
        mcts.makeMove(&best_move);
        std::cout << "My chance of winning: " << (float) mcts.root_node->num_wins / (float) mcts.root_node->num_visted<< std::endl;

        if (!selfPlay && !mcts.root_state->game_over) {
            int mac, mic;
            std::cout << "Your move: ";
            std::cin >> mac >> mic;
            Move* playerMove = new Move(mac, mic);
            mcts.makeMove(playerMove);
            delete playerMove;
        }
    }
    std::cout << "Game Over! Winner: " << mcts.root_state->winner << std::endl;
    return 0;
};
