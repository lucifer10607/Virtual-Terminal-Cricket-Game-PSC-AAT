#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Function to simulate the first player's inning (User or System)
int first_inning(const char* batsman_name) {
    int runs = 0;
    int ball_batsman;
    int ball_bowler;
    int is_out = 0; // 0 means not out, 1 means out

    printf("\n--- %s is Batting (First Inning) ---\n", batsman_name);
    while (is_out == 0)
        {
        // Decide who is the User for input
        if (batsman_name[0] == 'Y') { // If "Your Team" is batting
            printf("Enter your shot (0-6): ");
            // Input validation loop (a bit complex, but necessary for robustness)
            while (scanf("%d", &ball_batsman) != 1 || ball_batsman < 0 || ball_batsman > 6) {
                printf("Invalid input. Please enter a number between 0 and 6: ");
                while (getchar() != '\n'); // Clear the input buffer
            }
            ball_bowler = rand() % 7; // System bowls a random number
        } else { // If "System Team" is batting
            ball_batsman = rand() % 7; // System bats a random number

            printf("Enter your bowl (0-6): ");
            // Input validation
            while (scanf("%d", &ball_bowler) != 1 || ball_bowler < 0 || ball_bowler > 6) {
                printf("Invalid input. Please enter a number between 0 and 6: ");
                while (getchar() != '\n');
            }
        }

        printf("Ball bowled: %d | Shot played: %d\n", ball_bowler, ball_batsman);
        // Check for OUT condition
        if (ball_batsman == ball_bowler)
            {
            is_out = 1;
            printf("--- WICKET! %s is OUT! ---\n", batsman_name);
        }
        else
            {
            // Add runs (only if the batsman is the one who inputs the runs, which is always ball_batsman)
            runs += ball_batsman;
            printf("Runs Scored this ball: %d. Total Runs: %d\n", ball_batsman, runs);
        }
    }
    printf("\n*** %s INNING ENDS. Total Runs: %d ***\n", batsman_name, runs);
    return runs;
}
// Function to simulate the second player's inning (User or System)
int second_inning(const char* batsman_name, int target_score) {
    int runs = 0;
    int ball_batsman;
    int ball_bowler;
    int is_out = 0; // 0 means not out, 1 means out
    printf("\n--- %s is Batting (Second Inning) ---\n", batsman_name);
    printf("Target Score to win: %d\n", target_score);

    while (is_out == 0 && runs < target_score) {

        // Decide who is the User for input
        if (batsman_name[0] == 'Y') { // If "Your Team" is batting
            printf("Enter your shot (0-6): ");
            // Input validation
            while (scanf("%d", &ball_batsman) != 1 || ball_batsman < 0 || ball_batsman > 6) {
                printf("Invalid input. Please enter a number between 0 and 6: ");
                while (getchar() != '\n');
            }
            ball_bowler = rand() % 7; // System bowls
        } else { // If "System Team" is batting
            ball_batsman = rand() % 7; // System bats

            printf("Enter your bowl (0-6): ");
            // Input validation
            while (scanf("%d", &ball_bowler) != 1 || ball_bowler < 0 || ball_bowler > 6) {
                printf("Invalid input. Please enter a number between 0 and 6: ");
                while (getchar() != '\n');
            }
        }

        printf("Ball bowled: %d | Shot played: %d\n", ball_bowler, ball_batsman);

        // Check for OUT condition
        if (ball_batsman == ball_bowler) {
            is_out = 1;
            printf("--- WICKET! %s is OUT! ---\n", batsman_name);
        } else {
            runs += ball_batsman;
            printf("Runs Scored this ball: %d. Total Runs: %d\n", ball_batsman, runs);
        }

        // Check if the target is reached after scoring
        if (runs >= target_score && is_out == 0) {
            printf("\n*** %s REACHES THE TARGET! ***\n", batsman_name);
            break;
        }
    }

    printf("\n*** %s INNING ENDS. Total Runs: %d ***\n", batsman_name, runs);
    return runs;
}

// Main function
int main() {
    // Basic setup for randomness

    int user_runs = 0;
    int system_runs = 0;
    int target = 0;
    int toss_choice;
    int toss_result;
    int user_batting_first = 0; // 0 for false, 1 for true

    printf("===========================================\n");
    printf("   Welcome to Virtual Terminal Cricket \n");
    printf("===========================================\n\n");

    // --- 1. TOSS ---
    printf("--- TOSS TIME ---\n");
    printf("Choose (1) for Heads or (2) for Tails: ");
    if (scanf("%d", &toss_choice) != 1 || (toss_choice != 1 && toss_choice != 2)) {
        // Simple error handling
        printf("Invalid input. Defaulting to Heads (1).\n");
        toss_choice = 1;
        while (getchar() != '\n');
    }

    toss_result = (rand() % 2) + 1; // 1=Heads, 2=Tails

    printf("The coin is tossed... It's %s!\n", (toss_result == 1 ? "Heads" : "Tails"));

    if (toss_choice == toss_result) {
        printf("You WIN the toss! Choose (1) to Bat or (2) to Bowl: ");
        int choice_after_toss;
        if (scanf("%d", &choice_after_toss) != 1 || (choice_after_toss != 1 && choice_after_toss != 2)) {
            printf("Invalid input. Defaulting to Bat (1).\n");
            choice_after_toss = 1;
        }
        user_batting_first = (choice_after_toss == 1);
        printf("You chose to %s first.\n", (user_batting_first == 1 ? "Bat" : "Bowl"));
    } else {
        printf("The System WINS the toss and chooses to Bat first.\n");
        user_batting_first = 0; // System always bowls first if they win the toss in this simple version
    }

    // --- 2. GAME INNINGS ---
    if (user_batting_first == 1) {
        // User Bats First
        user_runs = first_inning("Your Team");
        target = user_runs + 1;

        // System Bats Second
        system_runs = second_inning("System Team", target);

    } else {
        // System Bats First
        system_runs = first_inning("System Team");
        target = system_runs + 1;

        // User Bats Second
        user_runs = second_inning("Your Team", target);
    }

    // --- 3. DETERMINE WINNER ---
    printf("\n===========================================\n");
    printf("           FINAL SCORECARD \n");
    printf("===========================================\n");
    printf("Your Team Runs: %d\n", user_runs);
    printf("System Team Runs: %d\n", system_runs);

    if (user_runs > system_runs) {
        printf("\n CONGRATULATIONS! You WIN the match by %d runs! \n", user_runs - system_runs);
    } else if (system_runs > user_runs) {
        printf("\n Tough luck! The System Team WINS the match by %d runs! \n", system_runs - user_runs);
    } else {
        printf("\n The match is a TIE! Well played by both teams! \n");
    }

    printf("===========================================\n");

    return 0;
}
