// Nickel Rounder
// Rounds an inputted price to the nearest nickel (5 cents)
// By Sam Chowdhury
// 16 Jan 2021

// Header file to handle input/output
#include <stdio.h>
// Header file to handle math commands
#include <math.h>

int main(int argc, char **argv)
{
    // Declaring variable for price
    double price;

    // Ask for input, take input of the price
    printf("Enter the price as a float with two decimals: ");
    scanf("%lf", &price);

    // Calculate nickel rounding
    // multiplying by 2 converts nickel rounding to decimal rounding
    // multiplying by 10 brings 2nd decimal place to rounding position
    // round function rounds
    // divide by 20 to undo conversion changes (which were just for rounding)
    double charge = (round(price * 20) / 20);

    //Output message
    printf("The total charge is: %.2lf", charge);

    //return statement ending the function (and the program)
	return 0;
}