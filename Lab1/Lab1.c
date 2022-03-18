// Math Operations
// Takes three numbers and calculates half their sum, twice their prpduct, and the average
// By Sam Chowdhury
// 16 Jan 2021

// Header file to handle input/output
#include <stdio.h>

int main(int argc, char **argv)
{
    // Declaring variables as doubles, the user will input
	double inputNumber1;
	double inputNumber2;
	double inputNumber3;

    // Code asks user for numbers, and stores it into the corresponding integer variables
	printf("Enter First Number: ");
	scanf("%lf", &inputNumber1);
	
	printf("Enter Second Number: ");
	scanf("%lf", &inputNumber2);
	
	printf("Enter Third Number: ");
	scanf("%lf", &inputNumber3);
	
    // Calculate the sum and product of the numbers and store them as doubles
    double sum = inputNumber1 + inputNumber2 + inputNumber3;
    double product = inputNumber1 * inputNumber2 * inputNumber3;
    
    // Initializing variables to store output values of half the sum, twice the product and the average of the inputs
    double halfSum = sum/2;
    double twiceProduct = product * 2;
    double average = sum/3;

    //output message with two decimal places
    printf("Half the Sum: %.2lf\n", halfSum);
    printf("Twice the Product: %.2lf\n", twiceProduct);
    printf("Average: %.2lf\n", average);

    //return statement ending the function (and the program)
	return 0;
}
