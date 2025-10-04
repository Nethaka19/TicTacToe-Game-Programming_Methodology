#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tictactoe.h"


// Menu and Gameplay
int main() {
    char board[MAX][MAX];
    int n, mode;

    srand(time(NULL));

    // Choose game mode
    printf("Select game mode:\n");
    printf("1. Player vs Player\n");
    printf("2. Player vs Computer\n");
    printf("Enter choice: ");
    scanf("%d", &mode);

    // Get board size
    printf("Enter board size (3 to 10): ");
    scanf("%d", &n);
    if (n < 3 || n > 10) {
        printf("Invalid size, defaulting to 3.\n");
        n = 3;
    }

    init_board(board, n);

    // Open log file
    FILE *logf = fopen("game_log.txt", "a");
    if (!logf) {
        printf("Warning: could not open log file!\n");
    } else {
        fprintf(logf, "\n=== New Game Started (Board %dx%d, Mode: %s) ===\n",
                n, n, (mode == 1) ? "P vs P" : "P vs C");
        log_board(logf, board, n);
    }

    int turn = 0;       // 0 = Player X, 1 = Player O (or Computer)
    int move_no = 0;    // Count of total moves
    int game_over = 0;  // Flag to stop when game ends

    // Main game loop
    while (!game_over) {
        display_board(board, n);

        int r, c;
        char symbol = (turn == 0) ? 'X' : 'O';

        if (mode == 1 || (mode == 2 && turn == 0)) {
            // Human player's turn
            printf("Player %c, enter row and column (1-%d): ", symbol, n);
            scanf("%d %d", &r, &c);
            r--; c--;
        } else {
            // Computer's turn
            if (!get_computer_move(board, n, &r, &c)) {
                printf("No valid moves for computer.\n");
                break;
            }
            printf("Computer plays at (%d,%d)\n", r + 1, c + 1);
        }

        // Validate move
        if (!is_valid_move(board, n, r, c)) {
            printf("Invalid move. Try again.\n");
            continue;
        }

        // Apply move
        make_move(board, r, c, symbol);
        move_no++;

        // Log the move
        if (logf) log_move(logf, move_no, symbol, r, c, board, n);

        // Check for win/draw
        if (check_win(board, n, r, c, symbol)) {
            display_board(board, n);
            printf("Player %c wins!\n", symbol);
            if (logf) fprintf(logf, "Player %c wins!\n", symbol);
            game_over = 1;
        } else if (check_draw(board, n)) {
            display_board(board, n);
            printf("It's a draw!\n");
            if (logf) fprintf(logf, "Game ended in a draw.\n");
            game_over = 1;
        } else {
            // Switch turn
            turn = 1 - turn;
        }
    }

    if (logf) {
        fprintf(logf, "=== Game Over ===\n");
        fclose(logf);
    }

    printf("\nGame log saved to 'game_log.txt'.\n");
    return 0;
}

