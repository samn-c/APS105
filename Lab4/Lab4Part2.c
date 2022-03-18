// Triangle maker
// Makes a centered triangle
// By Sam Chowdhury
// 05 Feb 2021

// Header file to handle input/output
#include <stdio.h>

int main(int argc, char **argv)
{  
    // declare triangle row total
    int rowTot;

    //ask user for number of rows
    printf("Enter the number of rows in the triangle: ");
    scanf("%d", &rowTot);

    // initialize characteristics of the triangle
    int leftSpace = rowTot - 1;
    int centreSpace = 1;
    int bottomRow = (2 * rowTot) - 1;

    // for loop for each row
    for (int row = 1; row < rowTot; row++) {
        //print left spaces
        for (int l = 0; l < leftSpace; l++) {
            printf(" ");
        }
        
        //reduce left space by one for next row
        leftSpace--;
        
        //print left edge of triangle
        printf("*");

        //when there is a right edge
        if (row > 1) {
            //print spaces between left and right edge
            for (int c = 0; c < centreSpace; c++) {
                printf(" ");
            }

            //increase centre spaces by 2
            centreSpace += 2;

            //right edge asterisk
            printf("*");
        }

        //new line for next row
        printf("\n");
    }

    //print bottom row asterisks
    if (rowTot > 1) {
        for (int bot = 0; bot < bottomRow; bot++) {
            printf("*");
        }
    }
    else {
        printf("*");
    }

    //return statement ending the function (and the program)
	return 0;
}
