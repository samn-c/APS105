#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define BOARDROWS 9
#define BOARDCOLS 11

bool dumpComputer = false; //causes dump of computer board before game if true (for debugging)

// boards. 0 means empty, non-zero means ship is there, number is size, -tive means hit on a ship
int playerBoard[BOARDROWS+1][BOARDCOLS+1];
int computerBoard[BOARDROWS+1][BOARDCOLS+1];
int compShotBoard[BOARDROWS+1][BOARDCOLS+1];

int getRand(int lowval,int highval){
    return (rand()%(highval+1-lowval) + lowval);
}

int getShot(bool fromUser, int board[BOARDROWS+1][BOARDCOLS+1]){
    int row,col;
    
    while(1){
        if(fromUser){
            printf("Give a shot (row, col):");
            scanf("%d%d",&row,&col);
            if(col<1 || col > BOARDCOLS || row < 1 || row > BOARDROWS)
                printf("Invalid input\n");
            else  //valid input
                break;
        }
        else { //computer generated
            row=getRand(1,BOARDROWS);
            col=getRand(1,BOARDCOLS);
            if(compShotBoard[row][col]==0) { //make sure haven't shot here before
                compShotBoard[row][col]=1; //valid shot
                break;
            }
        }
    } //will leave this loop with valid input
    if(board[row][col] != 0){
        if(board[row][col]>0)
            board[row][col]= -1*board[row][col]; //make sure is -tive
        return -1*board[row][col]; //a hit!
    }
    return 0; //miss
}
            

bool allShipsNotHit(int board[BOARDROWS+1][BOARDCOLS+1]){
    for(int i=1;i<=BOARDROWS;i++){
        for(int j=1;j<=BOARDCOLS;j++){
            if(board[i][j]>0) //ship and not hit
                return(true);
        }
    }
    return (false); //no ships found not all hit
}

bool noneLeft(int valueToFind,int board[BOARDROWS+1][BOARDCOLS+1]){
    for(int i=1;i<=BOARDROWS;i++){
        for(int j=1;j<=BOARDCOLS;j++){
            if(board[i][j]==valueToFind) //ship and not hit
                return(false);
        }
    }
    return (true); //no ships found, all hit
}

/*
########################################################################################################################
########################################################################################################################
########################################################################################################################
*/
//function to deploy given inputs and board
int deployer (int size, int row, int col, int ori, int board[BOARDROWS+1][BOARDCOLS+1]) {
    //if within the limits of the board
    if (row > 0 && row <= BOARDROWS && col > 0 && col <= BOARDCOLS) {
        //store end position of ship based on orientation (note: index + 1)
        int sum = ori ? row + size : col + size;

        //check if end position exceeds limits of board
        if (ori == 0 && sum < 13 || ori == 1 && sum < 11) {
            //set pointer increment based on orientation
            int increment = ori ? BOARDCOLS + 1 : 1;

            //loop to check if ship can be placed (no overlaps)
            for (int i = 0, *pPosition = &board[row][col]; i < size; i++, pPosition += increment) {
                if (*pPosition != 0) {
                    //exit function, tell the user a ship exists
                    return 0;
                }
            }

            //loop to place ship values at each index
            for (int i = 0, *pPosition = &board[row][col]; i < size; i++, pPosition += increment) {
                *pPosition = size;
            }

            //exit function, success
            return 1;
        }
    }
    //exit function, invalid input
    return 2;
}

//function to get input values to deploy ships
void populateBoard (bool getUserInput, int board[BOARDROWS+1][BOARDCOLS+1]){
    int row, col, ori;

    //tell user details of how to input
    if (getUserInput) {
        printf("Rows are 1 - 9, Columns are 1 - 11\n");
        printf("Orientation is 0 for across, 1 for down\n");
    }

    //iterate through this process for each ship size
    for (int size = 5; size > 0; size--) {
        //loop until a successful placement is made
        while (1) {
            //ask user for input
            if (getUserInput) {
                printf("Give starting row, starting column and orientation (3 inputs) for ship of size=%d:", size);
                scanf("%d %d %d", &row, &col, &ori);
            }
            //get random inputs for computer
            else {
                row = getRand(1, 9);
                col = getRand(1, 11);
                ori = getRand(0, 1);
            }
            
            //run deployer function, and store return in variable
            int deployed = deployer(size, row, col, ori, board);
            
            //based on return
            if (deployed == 1) {
                //exit loop, successful
                break;
            }
            //tell the user their placement was unsuccessful (and the reason)
            else if (getUserInput) {
                deployed == 0 ? printf("Conflicts with ship already placed\n") : printf("Invalid Input\n");
            }
        }
    }
}
/*
########################################################################################################################
########################################################################################################################
########################################################################################################################
*/

void showBoard(int board[BOARDROWS+1][BOARDCOLS+1]){
    printf("   Cols\n");
    printf("    1  2  3  4  5  6  7  8  9 10 11\n");
    printf("     ________________________________\n");
    for(int i=1;i<=BOARDROWS;i++){
        printf("R%d|",i);
        for(int j=1;j<=BOARDCOLS;j++){
            if(board[i][j]>=0)
                printf(" ");
            printf("%d ",board[i][j]);
        }
        printf("|\n");
    }
    printf("  __________________________________\n");
}

int main(int argc, char **argv)
{
    bool playerBoardOK,computerBoardOK;
    
    // initialize the seed randomly. 

     	srand(time(NULL)); 

    //init the boards
    for(int i=0;i<BOARDROWS;i++){
        for(int j=0;j<BOARDCOLS;j++){
            playerBoard[i][j]=0;
            computerBoard[i][j]=0;
            compShotBoard[i][j]=0;
        }
    }

    populateBoard(true,playerBoard);
    populateBoard(false,computerBoard);
    // showBoard(playerBoard); //debug
    // showBoard(computerBoard); //debug

    int b;
    scanf("%d", &b);

    printf("Your board is\n");
    showBoard(playerBoard);
    if(dumpComputer){
        printf("\n\nComputer board is\n");
        showBoard(computerBoard);
    }

    // play starts here
    playerBoardOK=true;
    computerBoardOK=true;
    while(playerBoardOK && computerBoardOK){
        int hit=getShot(true,computerBoard); //shot from user
        if(hit){
            printf("HIT on size %d\n",hit);
            if(noneLeft(hit,computerBoard))
                printf("Sunk computer's %d\n",hit);
        }
        else
            printf("MISS!!\n");
        hit=getShot(false,playerBoard);
        if(hit){
            printf("Computer hits! Size=%d\n", hit);
            if(noneLeft(hit,playerBoard))
                printf("Sunk your %d\n",hit);
        }
        else
            printf("Computer miss!\n");
        playerBoardOK = allShipsNotHit(playerBoard);
        computerBoardOK = allShipsNotHit(computerBoard);
        
        // showBoard(playerBoard); //debug
        // showBoard(computerBoard); //debug
   }
   if(playerBoardOK)
       printf("You win!\n");
    else
        printf("You lose.\n");
    showBoard(computerBoard);

	return 0;
}