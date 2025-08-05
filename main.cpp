#include <iostream>
#include "game.hpp"
#include "mcts.hpp"
#include <vector>
#include <chrono>


int main () {

    /*
    State game;
    while(game.game_over == false) {
        std::vector<Move*> legal_moves;
        game.createLegalMoves(legal_moves);
        for (auto it = legal_moves.begin(); it != legal_moves.end(); ++it)
        {
            std::cout << (*it)->macro_square << " " << (*it)->micro_square << std::endl;
        }
        int mac, mic;
        std::cin >> mac >> mic;
        Move* playerMove = new Move(mac, mic);
        game.executeMove(playerMove);
        delete playerMove;
    }
    */

    MCTS mcts;
    while (mcts.root_state->game_over == false) {
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 200000; i++) {
            mcts.runTree();
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Computation time: " << duration.count() << " microseconds" << std::endl;
        Move best_move = Move(mcts.bestMove());

        /* for (auto it = mcts.root_node->child_nodes.begin(); it != mcts.root_node->child_nodes.end(); ++it)
        {
            (*it)->move->movePrint();
            std::cout << ": " << (*it)->num_wins << " wins out of " << (*it)->num_visted << " simulations (" << ((float) (*it)->num_wins) / ((float) (*it)->num_visted) * 100 << "%)"<< std::endl;
        } */
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
