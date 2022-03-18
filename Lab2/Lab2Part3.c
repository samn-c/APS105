// Interest Compounding
// Money grows overtime, calculate the growth in user's money based on interest rate and time invested
// By Sam Chowdhury
// 16 Jan 2021

// Header file to handle input/output
#include <stdio.h>
// Header file to handle math commands
#include <math.h>

int main(int argc, char **argv)
{
    // Declare variables for input
    double dePosit;
    double rate;
    double compound;
    double time;

    // Ask for inputs, get inputs
    printf("The amount deposited P: ");
    scanf("%lf", &dePosit);
    printf("The interest rate r: ");
    scanf("%lf", &rate);
    printf("The number of times the interest is compounded n: ");
    scanf("%lf", &compound);
    printf("The period of time t the money is invested (in years): ");
    scanf("%lf", &time);

    // Calculate value of money invested after the time inputted, with given compounding values 
    double value = dePosit * pow((1 + (rate / compound)), (compound * time));
    
    //output value of investment
    printf("The future value of the investment A: %.2lf", value);

    //return statement ending the function (and the program)
	return 0;
}