// Pascal's Triangle
// Print out Pascal's Triangle based on user inputted rows
// By Sam Chowdhury
// 10 Feb 2021

// Header file to handle input/output
#include <stdio.h>

//function to calculate factorial
int factorial (int n) {   
    //the lowest result of factorial is 1
    int result = 1;

    //calculate the factorial by looping and multiplying by each integer from 1 to n
    for (int i = 1; i <= n; i++) {
        result *= i;
    }

    //end function
    return result;
}

//function to calcualte choice
int choose (int n, int r) {
    //calculation for choice using factorial function
    int choice = factorial(n) / (factorial(r) * factorial(n-r));
    
    //end function
    return choice;
}

//function to calculate number of spaces between values basedo n digits
int space (int value) {
    //zero digits to start with
    int digits = 0;
    
    //divide by 10 each time to count digits
    while (value != 0) {
        value /= 10;

        digits++;
    }
    
    //subtract from total spaces
    int spaces = 6 - digits;
    
    //end function
    return spaces;
}

//function to print pascal's triangle
void triangle(int row) {
    //calculate the spaces to the left of the first row
    int leftSpaces = (row * 3) - 3;

    //each row
    for (int n = 0; n < row; n++) {
        //output the left spaces
        for (int i = 1; i <= leftSpaces; i++) {
            printf(" ");
        }
        
        //each following row has 3 less spaces
        leftSpaces -= 3;

        //each value in the row
        for (int r = n; r >= 0; r--) {
            //use choose function for value
            int value = choose(n, r);

            //output value
            printf("%d", value);

            //output following spaces based on space function
            for (int i = 1; i <= space(value); i++) {
                printf(" ");
            }
        }
        
        //new line for next row
        printf("\n");
    }
}

//main function
int main(int argc, char **argv) {   
    //declare input variable
    int input;

    //run until input is negative
    while (1) {
        //ask for and store input
        printf("Enter the number of rows: ");
        scanf("%d", &input);

        //if input is within range, print triangle using function
        if (input > 0) {
            triangle(input);
        }
        //if the input is negative, end program
        else if (input < 0) {
            break;
        }
        //else the input is zero, asks for input again
    }

    //return statement ending the function (and the program)
	return 0;
}