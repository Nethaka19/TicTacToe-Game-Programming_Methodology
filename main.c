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

    int turn = 0; // 0 = Player X, 1 = Player O
    int game_over = 0;

    while (!game_over) {
        display_board(board, n);

        int r, c;
        char symbol = (turn == 0) ? 'X' : 'O';
        printf("Player %c,Enter the row and press enter and then Enter the column and press enter again (1-%d): ", symbol, n);
        scanf("%d %d", &r, &c);

        // convert to 0-based index
        r--; c--;

        if (!is_valid_move(board, n, r, c)) {
            printf("Invalid move. Try again.\n");
            continue; // retry same player
        }

        make_move(board, r, c, symbol);

        // check win
        if (check_win(board, n, r, c, symbol)) {
            display_board(board, n);
            printf("Player %c wins!\n", symbol);
            game_over = 1;
        }
        // check draw
        else if (check_draw(board, n)) {
            display_board(board, n);
            printf("It's a draw!\n");
            game_over = 1;
        }
        else {
            // switch turn
            turn = 1 - turn;
        }
    }

    return 0;
}
