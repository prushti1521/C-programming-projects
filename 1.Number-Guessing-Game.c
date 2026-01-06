

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
