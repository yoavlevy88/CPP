#ifndef _BOARD_H_
#define _BOARD_H_
#include "TheSnakesGame.h"

const char* board_example[ROWS] = {
//	         10        20        30        40        50        60        70       79
//	01234567890123456789012345678901234567890123456789012345678901234567890123456789
	"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++", // 0
	"+ Green Snake:                   Level:                         Yellow Snake:  +", // 1
	"+ Mission:                                                                     +", // 2
	"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++", // 3
	"+                                                                              +", // 4
	"+                                                                              +", // 5
	"+                                                                              +", // 6
	"+                                                                              +", // 7
	"+                                                                              +", // 8
	"+                                                                              +", // 9
	"+                                                                              +", // 10
	"+                                                                              +", // 11
	"+                                                                              +", // 12
	"+                                                                              +", // 13
	"+                                                                              +", // 14
	"+                                                                              +", // 15
	"+                                                                              +", // 16
	"+                                                                              +", // 17
	"+                                                                              +", // 18
	"+                                                                              +", // 19
	"+                                                                              +", // 20
	"+                                                                              +", // 21
	"+                                                                              +", // 22
	"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"  // 23
//   01234567890123456789012345678901234567890123456789012345678901234567890123456789
};

const char *Start_Board[ROWS] = {
	//	         10        20        30        40        50        60        70       79
	//	01234567890123456789012345678901234567890123456789012345678901234567890123456789
	"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++", // 0
	"+                                                                              +", // 1
	"+               ******  ******  ******  ******  **  **                         +", // 2
	"+               **      **  **  **  **     **    ****                          +", // 3
	"+               **      *****   ******    **      **                           +", // 4
	"+               **      **  **  **  **   **       **                           +", // 5
	"+               ******  **  **  **  **  ******    **                           +", // 6
	"+                                                                              +", // 7
	"+                      ******  **  **  ******  **  **  ******                  +", // 8
	"+                      **      *** **  **  **  ** **   **                      +", // 9
	"+                      ******  ******  ******  ****    ******                  +", // 10
	"+        * *               **  ** ***  **  **  ** **   **                      +", // 11
	"+         *            ******  **  **  **  **  **  **  ******                  +", // 12	
	"+       *****                                                                  +", // 13
	"+      * *** *                                                                 +", // 14
	"+     *********        *************            *************                  +", // 15
	"+     *********       ***************          ***************                 +", // 16
	"+      *******       ******     ******        ******     ******                +", // 17
	"+       ******      ******       ******      ******       ******               +", // 18
	"+        ******   *******         ******    ******         *******             +", // 19
	"+         **************           **************           *************      +", // 20
	"+          ************             ************             *************     +", // 21
	"+                                                                              +", // 22
	"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"  // 23
//   01234567890123456789012345678901234567890123456789012345678901234567890123456789
};

const char *Yellow[ROWS] = {
	//	         10        20        30        40        50        60        70       79
	//	01234567890123456789012345678901234567890123456789012345678901234567890123456789
	"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++", // 0
	"+                                                                              +", // 1
	"+               **  **  ******  **      ******  **         **                  +", // 2
	"+                ****   **      **      **  **  **         **                  +", // 3
	"+                 **    ******  **      **  **  **   ***   **                  +", // 4
	"+                 **    **      **      **  **   ** ** ** **                   +", // 5
	"+                 **    ******  ******  ******    ***   ***                    +", // 6
	"+                                                                              +", // 7
	"+                        **         **  ******  **        **                   +", // 8
	"+                        **         **  **  **  ******    **                   +", // 9
	"+                        **   ***   **  **  **  **  **    **                   +", // 10
	"+        * *              ** ** ** **   **  **  **  **                         +", // 11
	"+         *                ***   ***    ******  **  **    **                   +", // 12	
	"+       *****                                                                  +", // 13
	"+      * *** *                                                                 +", // 14
	"+     *********        *************            *************                  +", // 15
	"+     *********       ***************          ***************                 +", // 16
	"+      *******       ******     ******        ******     ******                +", // 17
	"+       ******      ******       ******      ******       ******               +", // 18
	"+        ******   *******         ******    ******         *******             +", // 19
	"+         **************           **************           *************      +", // 20
	"+          ************             ************             *************     +", // 21
	"+                                                                              +", // 22
	"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"  // 23
//   01234567890123456789012345678901234567890123456789012345678901234567890123456789
};

const char *Green[ROWS] = {
	//	         10        20        30        40        50        60        70       79
	//	01234567890123456789012345678901234567890123456789012345678901234567890123456789
	"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++", // 0
	"+                                                                              +", // 1
	"+              ******   *****   ******  ******  **                             +", // 2
	"+             **        *  **   **      **      ******                         +", // 3
	"+            **  ****   ****    ******  ******  **  **                         +", // 4
	"+             **   **   ** **   **      **      **  **                         +", // 5
	"+              *****    **  **  ******  ******  **  **                         +", // 6
	"+                                                                              +", // 7
	"+                        **         **  ******  **        **                   +", // 8
	"+                        **         **  **  **  ******    **                   +", // 9
	"+                        **   ***   **  **  **  **  **    **                   +", // 10
	"+        * *              ** ** ** **   **  **  **  **                         +", // 11
	"+         *                ***   ***    ******  **  **    **                   +", // 12	
	"+       *****                                                                  +", // 13
	"+      * *** *                                                                 +", // 14
	"+     *********        *************            *************                  +", // 15
	"+     *********       ***************          ***************                 +", // 16
	"+      *******       ******     ******        ******     ******                +", // 17
	"+       ******      ******       ******      ******       ******               +", // 18
	"+        ******   *******         ******    ******         *******             +", // 19
	"+         **************           **************           *************      +", // 20
	"+          ************             ************             *************     +", // 21
	"+                                                                              +", // 22
	"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"  // 23
//   01234567890123456789012345678901234567890123456789012345678901234567890123456789
};

const char* Instructions[ROWS] = {
	//	         10        20        30        40        50        60        70       79
	//	01234567890123456789012345678901234567890123456789012345678901234567890123456789
	"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++", // 0
	"+                             INSTRUCTIONS                                     +",	// 1									                                                                                                                                              ", // 1
	"+                           ================                                   +", // 2
	"+                                                                              +", // 3
	"+  CRAZY SNAKE is a math game. In each level appears a question.               +", // 4
	"+  In oredr to complete a level, the player has to collect a correct answer.   +", // 5
	"+                                                                              +", // 6
	"+  Each level contains two Snakes contoroled by the players:                   +", // 7
	"+  Player one(Yellow snake): UP 'w', DOWN 'x', LEFT 'a', RIGHT 'd' & 'z' SHOOT +", // 8
	"+  Player two(Green snake): UP 'i', DOWN 'm', LEFT 'j', RIGHT 'l' & 'n' SHOOT  +", // 9
	"+  Collection of a wrong answer will cause a Point to the other player.        +", // 10
	"+  The first palyer that win 12 points will win the game.                      +", // 11
	"+                                                                              +", // 12
	"+      If you want to see Replay(End of stage), go to Submenu and press 7!     +", // 19
	"+                                                                              +", // 20
	"+        ****  **** **** ***        *    *  *  *** *  *    *                   +", // 13
	"+        *     *  * *  * *  *       *    *  * *    * *     *                   +", // 14
	"+        * **  *  * *  * *  *       *    *  * *    **      *                   +", // 15
	"+        *  *  *  * *  * *  *       *    *  * *    * *                         +", // 16
	"+        ****  **** **** ***        **** ****  *** *  *    *                   +", // 17
	"+                                                                              +", // 18
	"+                        PRESS ANY KEY FOR MAIN MENU                           +", // 21
	"+                                                                              +", // 22
	"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"  // 23
};
#endif