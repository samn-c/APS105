// Cent Splitter
// Code to divide cents into the largest form of coin types
// By Sam Chowdhury
// 05 Feb 2021

// Header file to handle input/output
#include <stdio.h>

int main(int argc, char **argv) {  
    //declare variables for total cents and number of coin type
    int cents, quantity;

    // do while input is exceeds the range of 1 to 99 cents
    do {
        //ask for input
        printf("Please give an amount in cents less than 100: ");
        scanf("%d", &cents);

        //if the user entered an improper value, leave
        if (cents > 99 || cents < 1) {
            printf("Goodbye");
            break;
        }

        //outputs total cents
        printf("%d cents:", cents);

        // arrays with coin value and name corresponding to index
        int coins[4] = {25, 10, 5, 1};
        char types[4][8] = {"quarter", "dime", "nickel", "cent"};

        //for loop to iteratively sort through the number of coin types 
        for (int i = 0; i < 4; i++) {
            //if there is enough to have the coin type
            if (cents >= coins[i]) {
                //calculate number of coin type
                quantity = cents / coins[i];

                //subtract from total cents
                cents -= quantity * coins[i];
                
                //output the number of coins and the coin name
                printf(" %d %s", quantity, types[i]);
                
                //for plural
                if (quantity > 1) {
                    printf("s");
                }

                //if there is other coin types
                if (cents > 0) {
                    printf(",");
                }
            }
        }

        //end sentence
        printf(".\n");
    }while (1);

    //return statement ending the function (and the program)
	return 0;
}