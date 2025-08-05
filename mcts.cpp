#include <vector>
#include <cmath>
#include <cstdlib>
#include "game.hpp"
#include "mcts.hpp"

float Node::calculateUCBValue()
{
    if (num_visted == 0)
        return 10000 + std::rand() % 100;
    return  (((float)num_wins) / ((float)num_visted) ) + exploration_coff * std::sqrt(std::log(parent_node->num_visted) / num_visted);
}
Node::Node(Node *parent, Move *m, int t) : parent_node(parent), move(m), num_visted(0), num_wins(0), turn(t), is_root(false) {};
Node::~Node()
{
    if (!is_root)
        child_nodes.clear();
    delete move;
}

MCTS::MCTS()
{
    root_state = new State();
    root_node = new Node(nullptr, nullptr, root_state->turn);
    root_node->is_root = true;
};

void MCTS::runTree()
{
    Node *current_node = root_node;
    State *current_state = new State(*root_state);

    // Select
    while (current_node->child_nodes.size() > 0)
    {
        Node *best_node = nullptr;
        for (auto it = current_node->child_nodes.begin(); it != current_node->child_nodes.end(); ++it)
        {
            if ((best_node == nullptr) || ((*it)->calculateUCBValue() > best_node->calculateUCBValue()))
            {
                best_node = (*it);
            }
        }
        current_node = best_node;
        current_state->executeMove(best_node->move);
    };

    // Expand
    std::vector<Move *> legal_moves;
    current_state->createLegalMoves(legal_moves);

    for (auto it = legal_moves.begin(); it != legal_moves.end(); ++it)
    {
        current_node->child_nodes.push_back(new Node(current_node, (*it), current_state->getNextTurn()));
    }

    if (current_node->child_nodes.size() > 0)
    {
        current_node = current_node->child_nodes[std::rand() % current_node->child_nodes.size()];
        current_state->executeMove(current_node->move);
    }
    // Roll Out
    while (current_state->game_over == false)
    {
        std::vector<Move *> random_move_list;
        current_state->createLegalMoves(random_move_list);
        current_state->executeMove(random_move_list[std::rand() % random_move_list.size()]);

        random_move_list.clear(); // Supposedly calls destructor for elements
    }

    // Backpropagate

    int result = current_state->winner;

    while (current_node->is_root == false)
    {
        current_node->num_visted += 1;
        current_node->num_wins += (result == current_node->turn) ? 0 : 1;

        current_node = current_node->parent_node;
    }
    current_node->num_visted += 1;
    current_node->num_wins += (result == current_node->turn) ? 1 : 0;
    delete current_state;
    current_state = nullptr;

}

Move MCTS::bestMove()
{
    Node *best_node = nullptr;
    for (auto it = root_node->child_nodes.begin(); it != root_node->child_nodes.end(); ++it)
    {
        if ((best_node == nullptr) || ((*it)->num_visted > best_node->num_visted))
        {
            best_node = (*it);
        }
    }
    return *(best_node->move);
}

void MCTS::makeMove(Move *m)
{
    Node *next_root;
    for (auto it = root_node->child_nodes.begin(); it != root_node->child_nodes.end(); ++it)
    {
        if (*((*it)->move) == *(m))
        {
            next_root = (*it);
        }
        else
        {
            delete (*it);
        }
    }
    delete root_node;
    root_node = next_root;
    root_node->is_root = true;
    root_node->parent_node = nullptr;
    root_state->executeMove(root_node->move);
}
