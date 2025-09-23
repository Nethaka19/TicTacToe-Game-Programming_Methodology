#include <stdio.h>
#include "tictactoe.h"

int main() {
    char board[MAX][MAX];
    int n;

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
        fprintf(logf, "\n=== New Game Started (Board %dx%d) ===\n", n, n);
        log_board(logf, board, n);
    }

    int turn = 0; // 0 = Player X, 1 = Player O
    int game_over = 0;
    int move_no = 0;

    while (!game_over) {
        display_board(board, n);

        int r, c;
        char symbol = (turn == 0) ? 'X' : 'O';
        printf("Player %c, enter the row,PRESS ENTER and enter the column,PRESS ENTER (1-%d): ", symbol, n);
        scanf("%d %d", &r, &c);

        // Convert to 0-based index
        r--; c--;

        if (!is_valid_move(board, n, r, c)) {
            printf("Invalid move. Try again.\n");
            continue; // retry same player
        }

        make_move(board, r, c, symbol);
        move_no++;

        // Log the move
        if (logf) log_move(logf, move_no, symbol, r, c, board, n);

        // Check win
        if (check_win(board, n, r, c, symbol)) {
            display_board(board, n);
            printf("Player %c wins!\n", symbol);
            if (logf) fprintf(logf, "Player %c wins!\n", symbol);
            game_over = 1;
        }
        // Check draw
        else if (check_draw(board, n)) {
            display_board(board, n);
            printf("It's a draw!\n");
            if (logf) fprintf(logf, "Game ended in a draw.\n");
            game_over = 1;
        }
        else {
            // Switch turn
            turn = 1 - turn;
        }
    }

    if (logf) {
        fprintf(logf, "=== Game Over ===\n");
        fclose(logf);
    }

    return 0;
}

