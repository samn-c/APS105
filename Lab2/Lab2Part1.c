// Savings Calculator
// Takes the price per pound of a produce item, its weight, and outputs savings and total charge after savings
// By Sam Chowdhury
// 16 Jan 2021

// Header file to handle input/output
#include <stdio.h>
// Header file to handle math commands
#include <math.h>

int main(int argc, char **argv)
{   
    // Declare variables for price for pound and total weight of the produce
    double priceLbs;
    double totWeight;

    // Output requests to user and take inputs 
    printf("Enter the price per pound: ");
    scanf("%lf", &priceLbs);
    printf("Enter the total weight: ");
    scanf("%lf", &totWeight);

    // initialize variables that calculate subtotal, total savings and then total charge of the produce
    double subtotal = priceLbs * totWeight;
    double saved = floor(subtotal / 3) * 0.10;
    double totCharge = subtotal - saved;

    // Output statements
    printf("The total charge is: %.2lf\n", totCharge);
    printf("You saved: %.2lf", saved);

    //return statement ending the function (and the program)
	return 0;
}