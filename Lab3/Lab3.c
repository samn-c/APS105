// Simple Blackjack
// A game of Blackjack with infinite number of repeats of cards (not limited to 4 of each)
// By Sam Chowdhury
// 25 Jan 2021

// Header file to handle input/output
#include <stdio.h>
// Header file for random values 
#include <stdlib.h>
// Header file for time
#include <time.h>

int main(int argc, char **argv)
{  
    // statement to change the randomization seed based on arguments when the code is run
    if (argc==1)
        srand(time(NULL));
    else
        srand(atoi(argv[1]));

    // declaring variables for decision 
    int decision, drawnCard;

    // initializing the first cards for both the player and dealer (with random cards)
    int dealerCards = rand() % 13 + 1;
    int playerCards = rand() % 13 + 1;

    // Outputting the cards initial cards to the user
    printf("First cards: player %d, dealer %d", playerCards, dealerCards);
    
    // Limiting the dealer card value to 10
    if (dealerCards > 10) {
        dealerCards = 10;
    }

    // Limiting the player card value to 10
    if (playerCards > 10) {
        playerCards = 10;
    }

    // loop while the game is still 
    while (playerCards <= 21 && dealerCards <= 21) {
        
        // Ask user for their decision
        printf("\nType 1 for Hit, 0 to Stay:");
        scanf("%d", &decision);

        // for hit
        if (decision == 1) {
            // draws a card
            drawnCard = rand() % 13 + 1;

            //limit the value of the card
            if (drawnCard > 10) {
                playerCards += 10;
            }
            else {
                playerCards += drawnCard;
            }
            
            // output to user
            printf("Player gets a %d, worth is %d", drawnCard, playerCards);
        }

        // for staying
        else if (decision == 0) {
            // begin output message
            printf("Dealer gets: ");

            // while the dealer is below 17 (still able to get cards)
            while (dealerCards < 17) {
                // draws a card
                drawnCard = rand() % 13 + 1;

                //limit the value of the card
                if (drawnCard > 10) {
                    dealerCards += 10;
                }
                else {
                    dealerCards += drawnCard;
                }

                //outputs the card to user
                printf("%d ", drawnCard);
            }

            //break loop since the game is over after Staying
            break;
        }

        // reset decision choice
        decision = 2;
    }


    //outputs based on outcome of the game
    if (dealerCards > 21) {
        printf("\nDealer over 21, Player wins");
    } 
    else if (playerCards > 21) {
        printf("\nPlayer over 21, Dealer wins");
    }
    else if (dealerCards == playerCards) {
        printf("\nTie!");
    }
    else if (dealerCards > playerCards) {
        printf("\nDealer better than Player, Dealer wins");
    }
    else if (dealerCards < playerCards) {
        printf("\nPlayer better than Dealer, Player wins");
    }

    //return statement ending the function (and the program)
	return 0;
}