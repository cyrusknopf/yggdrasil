#ifndef _GAMETREE_H_
#define _GAMETREE_H_

#include <optional>
#include <vector>

#include "utils.h"

class GameNode {
    // Pointer to the parent node of this node
    GameNode* parent;
    // Array of pointers to the children of this node
    std::vector<GameNode*> children;
    // The move made to reach this game state
    bitboard move;
    // White team array of the game state after `move`
    team white;
    // Black team array of the game state after `move`
    team black;
    // Number of wins from this node for the player !turn from this node or one
    // of its descendants
    int wins;
    // Number of times a simulation has been played from this node or one of its
    // descendants
    int visits;
    // The player whose turn it is to move from the game state specified in
    // `white` and `black`; i.e. NOT the player who made the move in `move`
    bool turn;
    // Whether this node is terminal i.e. at the game state specified by `white`
    // and `black`, has either player won or is it stalemate
    bool terminal;
    // If terminal, who won? true  = white, false = black, nullopt = stalemate
    std::optional<bool> winner;

   public:
    /*
     * Initialise a game node. Initialises with 0 wins, 1 visit, non-terminal,
     * nullopt winner, no children, and provided parent, move and team arrays.
     *
     * @param [parent] pointer to parent node
     * @param [move] bitboard of a single piece with the new move made
     * @param [white] white team array, after `move` is made
     * @param [black] black team array, after `move` is made
     * @param [turn] turn of the player whose turn it is to move from the
     * gamestate in `white` and `black`
     * @returns GameNode as constructed
     */

    GameNode(GameNode* parent, bitboard move, team& white, team& black,
             bool turn)
        : parent(parent),
          children(),
          move(move),
          white(white),
          black(black),
          wins(0),
          visits(1),
          turn(turn),
          terminal(false),
          winner(std::nullopt){};

    // Removes all children. `changeRoot` should be used when moving the root of
    // the game tree
    ~GameNode() {
        if (children.size() != 0) {
            for (GameNode* child : children) {
                delete child;
            }
            children.clear();
        }
    };

    /*
     * Creates a node with the provided attributes, with its parent being the
     * provided `parent`, and adds the newly created node to the `children`
     * array of the node pointed to by `parent`. The turn of the child node is
     * the negation of the `parent`'s turn
     *
     * @param [parent] parent node TODO remove for `this`
     * @param [move] bitboard of single piece who moved
     * @param [white] white team array after `move`
     * @param [black] black team array after `move`
     * @returns pointer to the created child
     */
    GameNode* addChild(GameNode* parent, bitboard move, team& white,
                       team& black);

    /*
     * Removes the child from `this`' `children` array. Sets the `parent`
     * pointer of `newOrphan` to nullptr
     *
     * @param [newOrphan] node to remove from `this`
     */
    void removeChild(GameNode* newOrphan);

    GameNode* getParent() const;

    void setParent(GameNode* newParent);

    std::vector<GameNode*>& getChildren();

    void setChildren(std::vector<GameNode*> newChildren);

    /*
     * Gets a random child from the `children` vector of `this`
     *
     * @param [seed] int seed for MT RNG
     * @returns pointer to randomly selected child node
     */
    GameNode* getRandomChild(int seed);

    bitboard getMove() const;

    team getWhite() const;

    void setWhite(team& boards);

    team getBlack() const;

    void setBlack(team& boards);

    int getVisits();

    /*
     * Adds 1 to `this` node's `visits` member
     */
    void incrVisits();

    int getWins() const;

    /*
     * Adds 1 to `this` node's `wins` member
     */
    void incrWins();

    bool getTurn() const;

    /*
     * Sets `this`node's turn to the logical negation of its current value
     */
    void nextTurn();

    bool getTerminal() const;

    void setTerminal();

    std::optional<bool> getWinner() const;

    void setWinner(bool victor);

    /*
     * Calculates the evaluation score of a node based on the formula seen here:
     * https://en.wikipedia.org/wiki/Monte_Carlo_tree_search#Exploration_and_exploitation
     * (Chang, Fu, Hu, and Marcus)
     */
    double evaluate(double constantofInquisitiveness);
};

/*
 * Dynamically allocates memory for a GameNode on the heap with:
 * `parent` = nullptr, `move` = 0, `turn` = true
 * and team arrays as provided
 *
 * @param [white] white team array
 * @param [black] white team array
 * @returns pointer to dynamically allocated GameNode
 */
GameNode* initialiseTree(team& white, team& black);

/*
 * Changes the root of the game tree from `oldRoot` to `newRoot`. Memory of
 * `oldRoot` is managed and freed
 *
 * @param [oldRoot] current root of tree
 * @param [newRoot] new desired root
 * @returns pointer to the new root
 */
GameNode* changeRoot(GameNode* oldRoot, GameNode* newRoot);

/*
 * Changes the root of the game tree from `currentRoot` to the child of the
 * current root whose `white` and `black` team arrays are that of the provided
 * arrays
 * Uses `changeRoot`
 *
 * @param [currentRoot] current root of the game tree
 * @param [white] white team array which is used to match the new root
 * @param [black] black team array which is used to match the new root
 * @returns pointer to the new root
 */
GameNode* updateRootOnMove(GameNode* currentRoot, team& newWhite,
                           team& newBlack);

/*
 * Finds the child of `root` which has the largest `visits` attribute
 *
 * @param [root] node to search children of
 * @returns pointer to most visited child
 */
GameNode* getMostVisitedChild(GameNode* root);

#endif  // !_GAMETREE_H_
