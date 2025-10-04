#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tictactoe.h"

int main(void) {
    int n, mode;

    srand((unsigned) time(NULL));

    // Choose mode
    printf("Select game mode:\n");
    printf(" 1. Player vs Player\n");
    printf(" 2. Player vs Computer\n");
    printf(" 3. Three Players (mix humans/computers)\n");
    printf("Enter choice: ");
    if (scanf("%d", &mode) != 1) mode = 1;
    if (mode < 1 || mode > 3) mode = 1;

    // Board size
    printf("Enter board size (3–10): ");
    if (scanf("%d", &n) != 1 || n < 3 || n > 10) {
        n = 3;
        printf("Invalid size, defaulting to 3x3.\n");
    }

    // Restrict small boards for 3-player mode
    if (mode == 3 && n < 5) {
        printf("For 3-player mode, minimum board size is 5. Using 5x5.\n");
        n = 5;
    }

    // allocate dynamic board
    char **board = create_board(n);
    init_board(board, n);

    // log file
    FILE *logf = fopen("game_log.txt", "w");
    if (logf) {
        fprintf(logf, "=== New Game (Mode %d, %dx%d) ===\n", mode, n, n);
        log_board(logf, board, n);
    }

    // player setup
    char symbols[3] = {'X','O','Z'};
    int numPlayers = (mode == 3) ? 3 : 2;
    int human[3] = {0,0,0};

    if (mode == 1) { human[0] = human[1] = 1; }
    else if (mode == 2) { human[0] = 1; human[1] = 0; }
    else {
        for (int i = 0; i < 3; i++) {
            char ans;
            printf("Is Player %c human? (y/n): ", symbols[i]);
            scanf(" %c", &ans);
            human[i] = (ans=='y'||ans=='Y');
        }
        if (!human[0] && !human[1] && !human[2]) human[0] = 1;
    }

    int turn=0, move_no=0, game_over=0;
    while (!game_over) {
        display_board(board, n);
        char sym = symbols[turn];
        int r=-1, c=-1;

        if (human[turn]) {
            printf("Player %c enter row and column (1-%d): ", sym, n);
            scanf("%d %d", &r, &c);
            r--; c--;
        } else {
            get_computer_move(board,n,&r,&c);
            printf("Computer %c plays at (%d,%d)\n", sym, r+1, c+1);
        }

        if (!is_valid_move(board,n,r,c)) {
            printf("Invalid move. Try again.\n");
            continue;
        }

        make_move(board,r,c,sym);
        move_no++;
        if (logf) log_move(logf,move_no,sym,r,c,board,n);

        if (check_win(board,n,r,c,sym)) {
            display_board(board,n);
            printf("Player %c wins!\n", sym);
            if (logf) fprintf(logf,"Player %c wins!\n",sym);
            game_over=1;
        } else if (check_draw(board,n)) {
            display_board(board,n);
            printf("It's a draw!\n");
            if (logf) fprintf(logf,"Game ended in draw.\n");
            game_over=1;
        } else {
            turn = (turn+1)%numPlayers;
        }
    }

    if (logf) { fprintf(logf,"=== Game Over ===\n"); fclose(logf); }
    free_board(board,n);

    printf("Game log saved to game_log.txt\n");
    return 0;
}

