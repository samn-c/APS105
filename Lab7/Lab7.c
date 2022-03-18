/*
 * File:        project_reversi_skeleton.c
 * Author:      APS105H1 Teaching Team
 * Modified by: Sam Chowdhury
 * Date:        20 Mar 2021
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

    printBoard(board, n);
    
    // take input
    char input[3];    
    printf("Enter board configuration:\n");

    // while they keep wanting to input, assign each input to each position
    while (input[0] != '!') {
        scanf("%s", &input);

        if (input[0] == '!') {
            break;
        }

        board[c2i(input[1])][c2i(input[2])] = input[0];
    }

    // output created board
    printBoard(board, n);
}

// to swap all the pieces between the player's pieces
void swapper(char board[][26], int dirs[8][2], int n, char input[3]) {
    board[c2i(input[1])][c2i(input[2])] = input[0];

    // for every possible direction
    for (int h = 0; h < 8; h++) { 
        if (checkLegalInDirection(board, n, c2i(input[1]), c2i(input[2]), input[0], dirs[h][0], dirs[h][1])) {
        //this is checking the same position, which has changed. fix this!
            for(int i = c2i(input[1]) + dirs[h][0], j = c2i(input[2]) + dirs[h][1]; board[i][j] != input[0]; i += dirs[h][0], j += dirs[h][1]) {
                board[i][j] = input[0];
            }
        }
    }
}

// to check if position is valid
int checkPlayer(char board[][26], int dirs[8][2], int n, bool placing) {
    char input[3];
    char *colour = "WB";

    if (placing) {
        printf("Enter a move:\n");
        scanf("%s", &input);
    }

    // both colours
    for (int i = 0; i < 2; i++) {
        if (!placing) {
            printf("Available moves for %c:\n", colour[i]);
        }

        //for every position and every direction    
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                for (int l = 0; l < 8; l++) {
                    if (placing && board[c2i(input[1])][c2i(input[2])] == 'U' && checkLegalInDirection(board, n, c2i(input[1]), c2i(input[2]), input[0], dirs[l][0], dirs[l][1])) {
                        printf("Valid move.\n");

                        //swap positions in every direction
                        swapper(board, dirs, n, input);

                        //output board
                        printBoard(board, n);
                        return 0;
                    }
                    else if (!placing && board[j][k] == 'U' && checkLegalInDirection(board, n, j, k, colour[i], dirs[l][0], dirs[l][1])) {
                        printf("%c%c\n", i2c(j), i2c(k));
                        break;
                    }
                }
            }
        }
    }
    
    if (placing) {
        printf("Invalid move.\n");
        printBoard(board, n);
    }

    return 0;
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
int makeMove(const char board[26][26], int n, char turn, int *row, int *col) {
    (void)board;
    (void)n;
    (void)turn;
    (void)row;
    (void)col;
    return 0;
}

#ifndef COMPETE_MODE // DO NOT DELETE THIS LINE
int main(void) {
    //board dimension
    int n;
    printf("Enter the board dimension: ");
    scanf("%d", &n);

    //initialize board and directionss
    char board[26][26];
    int dirs[8][2] = {{-1,-1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    createBoard(board, n);

    //show possible positions
    checkPlayer(board, dirs, n, false);
    
    //user placing
    checkPlayer(board, dirs, n, true);

    return 0;
}
#endif // DO NOT DELETE THIS LINE