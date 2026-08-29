#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RESET "\x1b[0m"
#define BOLD "\x1b[1m"
#define DIM "\x1b[2m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define CLEAR "\x1b[2J\x1b[H"

typedef struct {
    const char *name;
    int maximum;
    int lives;
    int multiplier;
} Difficulty;

static const Difficulty difficulties[] = {
    {"Chill", 50, 10, 1},
    {"Classic", 100, 8, 2},
    {"Insane", 500, 7, 4}
};

static void clear_screen(void) { fputs(CLEAR, stdout); }

static void line(void) {
    puts(CYAN "+--------------------------------------------------+" RESET);
}

static void title(void) {
    clear_screen();
    line();
    puts(CYAN "|" RESET BOLD MAGENTA "              N U M B E R   R U S H               " RESET CYAN "|" RESET);
    puts(CYAN "|" RESET DIM "       Read the clues. Protect your streak.       " RESET CYAN "|" RESET);
    line();
}

static int read_number(const char *prompt, int minimum, int maximum) {
    char buffer[128];
    char *end;
    long value;

    for (;;) {
        fputs(prompt, stdout);
        fflush(stdout);
        if (fgets(buffer, sizeof buffer, stdin) == NULL) {
            putchar('\n');
            exit(0);
        }
        value = strtol(buffer, &end, 10);
        while (isspace((unsigned char)*end)) end++;
        if (end != buffer && *end == '\0' && value >= minimum && value <= maximum)
            return (int)value;
        printf(RED "  Please enter a number from %d to %d.\n" RESET, minimum, maximum);
    }
}

static char read_choice(const char *prompt) {
    char buffer[32];
    fputs(prompt, stdout);
    fflush(stdout);
    if (fgets(buffer, sizeof buffer, stdin) == NULL) return 'q';
    return (char)tolower((unsigned char)buffer[0]);
}

static void lives_bar(int lives, int total) {
    int i;
    fputs(BOLD "Lives  " RESET, stdout);
    for (i = 0; i < total; i++)
        fputs(i < lives ? RED "<3 " RESET : DIM "-- " RESET, stdout);
    putchar('\n');
}

static void heat_meter(int distance, int maximum) {
    int heat = 10 - (distance * 10 / maximum);
    int i;
    if (heat < 0) heat = 0;
    if (heat > 10) heat = 10;

    fputs(BOLD "Heat   [" RESET, stdout);
    for (i = 0; i < 10; i++) {
        if (i < heat)
            fputs(heat > 7 ? RED "#" RESET : heat > 4 ? YELLOW "#" RESET : BLUE "#" RESET, stdout);
        else
            fputs(DIM "." RESET, stdout);
    }
    puts(BOLD "]" RESET);
}

static int choose_difficulty(void) {
    title();
    puts(BOLD " Choose your challenge\n" RESET);
    puts(GREEN  "  [1] CHILL    " RESET "1-50   | 10 lives | relaxed");
    puts(YELLOW "  [2] CLASSIC  " RESET "1-100  |  8 lives | balanced");
    puts(RED    "  [3] INSANE   " RESET "1-500  |  7 lives | huge score");
    putchar('\n');
    return read_number(CYAN " Select 1-3: " RESET, 1, 3) - 1;
}

static int play_round(const Difficulty *level, int streak) {
    int secret = rand() % level->maximum + 1;
    int lives = level->lives;
    int attempts = 0;
    int previous_distance = level->maximum + 1;

    title();
    printf(BOLD " Mode: %-8s" RESET "  Range: 1-%d  Streak: %d\n\n",
           level->name, level->maximum, streak);
    puts(" A mystery number is locked in. Every miss costs a life.");
    puts(DIM " Type 0 at any time to surrender.\n" RESET);

    while (lives > 0) {
        int guess;
        int distance;
        lives_bar(lives, level->lives);
        guess = read_number(CYAN " Your guess > " RESET, 0, level->maximum);
        if (guess == 0) {
            printf(YELLOW "\n You surrendered. The number was %d.\n" RESET, secret);
            return 0;
        }
        attempts++;
        distance = abs(secret - guess);
        if (distance == 0) {
            int speed_bonus = lives * 25;
            int score = (100 + speed_bonus + streak * 50) * level->multiplier;
            puts(GREEN BOLD "\n *** JACKPOT! You cracked the code! ***" RESET);
            printf(" Number: " BOLD "%d" RESET " | Attempts: %d | Round score: " YELLOW "%d" RESET "\n",
                   secret, attempts, score);
            return score;
        }
        lives--;
        heat_meter(distance, level->maximum);
        printf(guess < secret ? BLUE " Hint: Go HIGHER!" RESET : MAGENTA " Hint: Go LOWER!" RESET);
        if (previous_distance <= level->maximum) {
            if (distance < previous_distance) printf(RED BOLD "  You're getting warmer!" RESET);
            else if (distance > previous_distance) printf(BLUE BOLD "  Colder..." RESET);
            else printf(YELLOW "  Same distance!" RESET);
        }
        if (distance == 1) printf(YELLOW BOLD "  Just one away!" RESET);
        else if (distance <= level->maximum / 20 + 1) printf(YELLOW "  Extremely close!" RESET);
        puts("\n");
        previous_distance = distance;
    }
    printf(RED BOLD " GAME OVER!" RESET " The mystery number was " BOLD "%d" RESET ".\n", secret);
    return 0;
}

int main(void) {
    int total_score = 0;
    int streak = 0;
    int best_streak = 0;
    char again = 'y';

    srand((unsigned int)time(NULL));
    while (again == 'y') {
        int difficulty = choose_difficulty();
        int round_score = play_round(&difficulties[difficulty], streak);
        if (round_score > 0) {
            streak++;
            if (streak > best_streak) best_streak = streak;
            total_score += round_score;
        } else {
            streak = 0;
        }
        printf("\n " BOLD "Total score: " YELLOW "%d" RESET
               "  |  " BOLD "Best streak: " GREEN "%d" RESET "\n", total_score, best_streak);
        again = read_choice("\n Play another round? [y/n]: ");
    }
    puts(CYAN "\n Thanks for playing Number Rush!" RESET);
    return 0;
}
