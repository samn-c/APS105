/*
 * File:        project_reversi_skeleton.c
 * Author:      APS105H1 Teaching Team
 * Modified by: Sam Chowdhury
 * Date:        7 Apr 2021
 */

#include "project_reversi_skeleton.h" //DO NOT modify this line
// to take inputs from the user
#include <stdio.h>

// =========   Function declaration  ==========

// functions to switch between chars and indices of the board
int c2i(char c) {
    return c - 97;
}
char i2c(int i) {
    return i + 97;
}

// creation of the board
void createBoard(char board[][26], int n) {
    // create empty board
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            board[i][j] = 'U';
        }
    }
    
    // place centre pieces 
    board[n/2 - 1][n/2 - 1] = 'W';
    board[n/2 - 1][n/2] = 'B';
    board[n/2][n/2 - 1] = 'B';
    board[n/2][n/2] = 'W';

    //output the board
    printBoard(board, n);
}

// to swap all the pieces between the player's pieces
void swapper(char board[][26], int dirs[8][2], int n, int row, int col, char colour) {
    //set initial spot to colour
    board[row][col] = colour;

    // for every possible direction
    for (int h = 0; h < 8; h++) {
        //if possible to change this direction 
        if (checkLegalInDirection(board, n, row, col, colour, dirs[h][0], dirs[h][1])) {
            //change every piece to colour until the same colour piece
            for(int i = row + dirs[h][0], j = col + dirs[h][1]; board[i][j] != colour; i += dirs[h][0], j += dirs[h][1]) {
                board[i][j] = colour;
            }
        }
    }
}

// to check if position is valid
bool move(char board[][26], int dirs[8][2], int n, int row, int col, char colour, bool placing) {
    //directions
    for (int l = 0; l < 8; l++) {
        //if possible
        if (checkLegalInDirection(board, n, row, col, colour, dirs[l][0], dirs[l][1])) {
            //swap positions in every direction
            swapper(board, dirs, n, row, col, colour);
            
            //output board for part 1
            if (placing) {
                // output board
                printBoard(board, n);
            }

            //success
            return true;
        }
    }
    
    //only fails when human places
    if (placing) {
        return false;
    }
}

// ========= Function implementation ==========
/*
 * Function:  printBoard 
 * --------------------
 * Print the whole board to the terminal window.
 */
void printBoard(char board[][26], int n) {
    printf("  ");
    for (int i = 0; i < n; i++) {
        printf("%c", i2c(i));
    }
    
    for (int i = 0; i < n; i++) {
        printf("\n%c ", i2c(i));

        for (int j = 0; j < n; j++) {
            printf("%c", board[i][j]);
        }
    }
    printf("\n");
}

/*
 * Function:  positionInBounds 
 * --------------------
 * Checks whether the specified (row, col) lies within the board dimensions.
 */
bool positionInBounds(int n, int row, int col) {
    if (row >= 0 && row < n && col >= 0 && col < n){ 
        return true;
    }
    return false;  
}

/*
 * Function:  checkLegalInDirection 
 * --------------------
 * Checks whether (row, col) is a legal position for a tile of colour by “looking” in the direction 
 * specified by deltaRow and deltaCol.
 */
bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {
    //increment as that position was already checked
    row += deltaRow;
    col += deltaCol;
    
    //if next position is valid
    if (board[row][col] != 'U' && board[row][col] != colour) {
        //loop until possible or impossible

        do {
            row += deltaRow;
            col += deltaCol;

            if (board[row][col] == colour && positionInBounds(n, row, col)) {
                return true;
            }
            else if (board[row][col] == 'U') {
                return false;
            }
        } while (positionInBounds(n, row, col));
    }
    return false;             
}

/*
 * Function:  makeMove 
 * --------------------
 * The player "turn" makes a move at (row, col).
 * Note: This function MUST NOT change board, only row and col can be changed to reflect the move.
 */
int makeMove(const char board[26][26], int n, char turn, int* row, int* col) {
    //directions
    int dirs[8][2] = {{-1,-1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    //counts for flipped pieces
    int totalCount = 0;
    int tempCount = 0;
    //temporary board
    char tBoard[26][26];

    //create temporary board
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            tBoard[i][j] = board[i][j];
        }
    }

    // for every position and every direction    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            //if empty spot
            if (tBoard[i][j] == 'U') {
                //for every direction
                for (int k = 0; k < 8; k++) {
                    //temporary row and col values to change through moves
                    int tRow = i;
                    int tCol = j;
                    
                    //if possible to move this way
                    if (checkLegalInDirection(tBoard, n, tRow, tCol, turn, dirs[k][0], dirs[k][1])) {
                        //increment as that position was already checked
                        tRow += dirs[k][0];
                        tCol += dirs[k][1];
                        
                        //if next position is valid
                        if (tBoard[tRow][tCol] != 'U' && tBoard[tRow][tCol] != turn) {
                            //add to flip count
                            tempCount++;

                            //loop until possible or impossible
                            do {
                                tRow += dirs[k][0];
                                tCol += dirs[k][1];

                                //check if still possible
                                if (tBoard[tRow][tCol] == turn && positionInBounds(n, tRow, tCol)) {
                                    break;
                                }

                                //add to flip count
                                tempCount++;
                            } while (positionInBounds(n, tRow, tCol));
                        }
                    }
                }

                //if it's a higher flip count (greed)
                if (tempCount > totalCount) {
                    //set it to the recommended move
                    totalCount = tempCount;
                    *row = i;
                    *col = j;
                }
                //reset count
                tempCount = 0;
            }
        }
    }
    
    //return that move is possible (if > 0, possible)
    return totalCount;
}

#ifndef COMPETE_MODE // DO NOT DELETE THIS LINE
int main(void) {
    //declaration
    int n;
    int cRow = 0;
    int cCol = 0;
    char play, comp, position[3], board[26][26];
    bool canMovePlayer = true;
    bool canMoveComp = true;

    //take setup inputs
    printf("Enter the board dimension: ");
    scanf("%d", &n);

    printf("Computer plays (B/W) : ");
    scanf(" %c", &comp);
    
    //set player
    play = comp == 'W'? 'B' : 'W';

    //initialize board and directions
    int dirs[8][2] = {{-1,-1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    createBoard(board, n);

    //for loop switching between players
    for (int i = play == 'B' ? 0 : 1; canMoveComp || canMovePlayer; i++) {
        if (i % 2 == 0) {
            //player
            //if possible to move
            if (makeMove(board, n, play, &cRow, &cCol) > 0) {
                canMovePlayer = true;
                //enter move
                printf("Enter move for colour %c (RowCol): ", play);
                scanf(" %s", &position);

                //break if invalid move, otherwise make move
                if (board[c2i(position[0])][c2i(position[1])] != 'U' || !move(board, dirs, n, c2i(position[0]), c2i(position[1]), play, true)) {
                    break;
                }
            }
            //if no moves possible
            else if (canMovePlayer) {
                //check if computer can still move
                if  (canMoveComp && makeMove(board, n, comp, &cRow, &cCol) > 0) {
                    //output player has no moves
                    printf("%c has no valid move.\n", play);
                }   

                //set false so no more player moving
                canMovePlayer = false;
            }
        }
        else{
            //bot
            //if possible to move
            if (makeMove(board, n, comp, &cRow, &cCol) > 0) {
                canMoveComp = true;

                //move
                move(board, dirs, n, cRow, cCol, comp, false);

                //tell human where bot moved
                printf("Computer places %c at %c%c.\n", comp, i2c(cRow), i2c(cCol));
                printBoard(board, n);
            }
            //if no moves possible
            else if (canMoveComp) {
                //if player can make moves, tell them that computer cant
                if  (canMovePlayer && makeMove(board, n, play, &cRow, &cCol) > 0) {
                    printf("%c player has no valid move.\n", comp);
                }

                //no more bot moving
                canMoveComp = false;
            }
        }
    }

    //if proper end to game
    if (!canMovePlayer && !canMoveComp) {
        //count player pieces
        int Bcount = 0;
        int Wcount = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'W') {
                    Wcount++;
                }
                else if (board[i][j] == 'B') {
                    Bcount++;
                }
            }
        }

        //output winner
        if (Bcount > Wcount) {
            printf("B player wins.");
        }
        else if (Wcount > Bcount) {
            printf("W player wins.");
        }
        else {
            printf("Draw!");
        }
    }
    //invalid move end
    else {
        printf("Invalid move.\n");
        printf("%c player wins.", comp);
    }

    return 0;
}
#endif // DO NOT DELETE THIS LINE