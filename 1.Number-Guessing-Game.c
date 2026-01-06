/*
 Number Guessing Game
 --------------------
   A simple console-based C program where the computer generates
   a random number and the user tries to guess it.
 
   The program provides feedback for each guess (too high / too low)
   and counts the total number of attempts until the correct number
   is guessed.
 
 * Concepts used:
  - Random number generation
  - Loops and conditional statements
  - User input/output

 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int RandomNo, guessedNo, attempts = 0;

    srand(time(0));

    // Generate random number between 1 and 100
    RandomNo = (rand() % 100) + 1;

    printf("Welcome to Number Guessing Game!!\n");
    printf("Guess a number between 1 and 100.\n");
 

    while (1) {
        printf("Enter your guess: ");
        scanf("%d", &guessedNo);
        attempts++;

        if (guessedNo > RandomNo) {
            printf("Too high! Try again.\n");
        } 
        else if (guessedNo < RandomNo) {
            printf("Too low! Try again.\n");
        } 
        else {
            printf("\nCongratulations! You guessed the correct number in %d attempts.\n", attempts);
            break;
        }
    }

    return 0;
}
