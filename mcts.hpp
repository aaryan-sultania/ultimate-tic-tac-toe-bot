#ifndef MCTS_H
#define MCTS_H

#include <vector>
#include <cmath>
#include <cstdlib>
#include "game.hpp"

const int exploration_coff = 1.41;


class Node {
    public:

    Node* parent_node; // Pointer to parent node
    std::vector<Node*> child_nodes; // Pointers to child node

    Move* move; // The move made to reach this node

    int num_visted;
    int num_wins;
    int turn;
    bool is_root;
    float calculateUCBValue();
    Node(Node* parent, Move* m, int t);
    ~Node ();
};

class MCTS {
    public:

    Node* root_node;
    State* root_state; 
    void runTree();
    Move bestMove();
    void makeMove(Move* m);
    MCTS();
};

#endif