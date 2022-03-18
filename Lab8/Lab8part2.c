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
    int dirs[8][2] = {{-1,-1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    
    int totalCount = 0;
    int tempCount = 0;
    char tBoard[26][26];
    char opponent = turn == 'B' ? 'W' : 'B';
    int rank = 0;
    int totalRank = 0;
    int bestDifference = 0;
    int difference = 0;

    // for every position and every direction    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int e = 0; e < n; e++) {
                for (int f = 0; f < n; f++) {
                    tBoard[e][f] = board[e][f];
                }
            }
            if (tBoard[i][j] == 'U') {
                int tRow = i;
                int tCol = j;

                for (int k = 0; k < 8; k++) {
                    if (checkLegalInDirection(tBoard, n, tRow, tCol, turn, dirs[k][0], dirs[k][1])) {
                        //increment as that position was already checked
                        tRow += dirs[k][0];
                        tCol += dirs[k][1];
                        
                        //if next position is valid
                        if (tBoard[tRow][tCol] != 'U' && tBoard[tRow][tCol] != turn) {
                            tempCount++;

                            //loop until possible or impossible
                            do {
                                tRow += dirs[k][0];
                                tCol += dirs[k][1];

                                if (tBoard[tRow][tCol] == turn && positionInBounds(n, tRow, tCol)) {
                                    break;
                                }

                                tempCount++;
                            } while (positionInBounds(n, tRow, tCol));
                        }
                    }
                }

                //case 0 1
                if (tempCount > totalCount) {
                    totalCount = tempCount;
                    if (rank <= 4) {
                        rank = 4;
                    }
                }

                //case 1 2 3
                if (rank >= 4) {
                    int OtotalCount = 0;
                    int OtempCount = 0;
                    
                    move(tBoard, dirs, n, i, j, turn, false);
                    
                    // for every position and every direction
                    for (int l = 0; l < n; l++) {
                        for (int m = 0; m < n; m++) {
                            if (tBoard[l][m] == 'U') {
                                int OtRow = l;
                                int OtCol = m;

                                for (int o = 0; o < 8; o++) {
                                    if (checkLegalInDirection(tBoard, n, OtRow, OtCol, opponent, dirs[o][0], dirs[o][1])) {
                                        //increment as that position was already checked
                                        OtRow += dirs[o][0];
                                        OtCol += dirs[o][1];
                                        
                                        //if next position is valid
                                        if (tBoard[OtRow][OtCol] != 'U' && tBoard[OtRow][OtCol] != opponent) {
                                            OtempCount++;

                                            //loop until possible or impossible
                                            do {
                                                OtRow += dirs[o][0];
                                                OtCol += dirs[o][1];

                                                if (tBoard[OtRow][OtCol] == opponent && positionInBounds(n, OtRow, OtCol)) {
                                                    break;
                                                }

                                                OtempCount++;
                                            } while (positionInBounds(n, OtRow, OtCol));
                                        }
                                    }
                                }
                            
                                if (OtempCount > OtotalCount) {
                                    OtotalCount = OtempCount;
                                }
                                
                                OtempCount = 0;
                            }
                        }
                    }

                    difference = totalCount - OtotalCount;
                    printf("your move: %d\ntheir move: %d\ndifference: %d\n", totalCount, OtotalCount, difference);

                    if (difference > 0) {
                        rank = 12;
                    }
                    else if (difference = 0) {
                        rank = 8;
                    }
                    else if (difference < 0) {
                        rank = 4;
                    }

                    // //corner
                    // if (i == 0 && j == 0 || i == n -1 && j == n -1 || i == 0 && j == n -1 || i == n -1 && j == 0) {
                    //     rank += 6;
                    // }
                    // //edge piece
                    // else if (i == 0 || j == 0 || i == n -1 || j == n -1) {
                    //     rank += 1;
                    // }
                }

                if (rank > totalRank) {
                    totalRank = rank;
                    *row = i;
                    *col = j;
                }
                else if (rank == totalRank && difference > bestDifference) {
                    bestDifference = difference;
                    *row = i;
                    *col = j;
                }
                // if same... how to determine better spot?
                else if (rank == totalRank && difference == bestDifference) {
                    //which one is closer to more of my own pieces?
                    
                    if (!(*row < i && *col < j)) {
                        *row = i;
                        *col = j;
                    }
                }

                tempCount = 0;
                totalCount = 0;
                rank = 0;
                difference = 0;
            }
        }
    }

    return totalRank;
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
            if (makeMove(board, n, play, &cRow, &cCol) > 0  && canMovePlayer) {
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
            if (makeMove(board, n, comp, &cRow, &cCol) > 0 && canMoveComp) {
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
        else {
            printf("W player wins.");
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