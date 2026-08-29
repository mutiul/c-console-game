#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void clear_input(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

int main(void) {
    int secret;
    int guess;
    int attempts = 0;

    srand((unsigned int)time(NULL));
    secret = rand() % 100 + 1;

    puts("================================");
    puts("       NUMBER GUESSING GAME     ");
    puts("================================");
    puts("I picked a number from 1 to 100.");

    while (1) {
        printf("Enter your guess: ");

        if (scanf("%d", &guess) != 1) {
            puts("Please enter a whole number.");
            clear_input();
            continue;
        }

        attempts++;

        if (guess < 1 || guess > 100) {
            puts("Your guess must be between 1 and 100.");
        } else if (guess < secret) {
            puts("Too low!");
        } else if (guess > secret) {
            puts("Too high!");
        } else {
            printf("You won in %d attempt%s!\n", attempts,
                   attempts == 1 ? "" : "s");
            break;
        }
    }

    return 0;
}
