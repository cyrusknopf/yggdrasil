#ifndef _DRIVER_H_
#define _DRIVER_H_

/*
 * Contains logic for running a game where the user is white and MCTS agent is
 * black
 *
 * @param [moveTime] time given to the MCTS agent to make a move
 */
void userVsMCTS(int moveTime);

/*
 * Contains logic for running a game where the random agent is white and MCTS
 * agent is black
 *
 * @param [moveTime] time given to the MCTS agent to make a move
 */
void randomVsMCTS(int moveTime);

#endif
