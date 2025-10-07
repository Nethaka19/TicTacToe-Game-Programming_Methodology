#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tictactoe.h"

int main(void) {
    int n, mode;

    srand((unsigned) time(NULL));

    // Choose mode
    do {
        printf("Select Game Mode:\n");
        printf(" 1. Player vs Player\n");
        printf(" 2. Player vs Computer\n");
        printf(" 3. Three Player Mode\n");
        printf("Enter the choice: ");

        if (scanf("%d", &mode) != 1) {
            while (getchar() != '\n');
            printf("Invalid input. Please enter a number (1, 2, or 3).\n\n");
            mode = 0;
        } 
        else if (mode < 1 || mode > 3) {
            printf("Invalid choice. Please select 1, 2, or 3.\n\n");
        }

    } while (mode < 1 || mode > 3);

    // Board size
    if (mode == 3) {
    do {
        printf("Enter board size (5–10): ");
        scanf("%d", &n);
        if (n < 5 || n > 10)
            printf("Invalid size. Please enter between 5 and 10.\n");
    } while (n < 5 || n > 10);
} else {
    do {
        printf("Enter board size (3–10): ");
        scanf("%d", &n);
        if (n < 3 || n > 10)
            printf("Invalid size. Please enter between 3 and 10.\n");
    } while (n < 3 || n > 10);
}

//To Win Message
if (n == 3) {
        printf("\nYou need to place 3 in a row to win!\n\n");
    } else {
        printf("\nYou need to place 4 in a row to win!\n\n");
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

    if (mode == 1) {
	    //Player vs Player
	    human[0] = human[1] = 1; }
    else if (mode == 2) {
	    //Player vs Computer
	    human[0] = 1; human[1] = 0; }
    else {
         //Three Player mode
        int humanCount = 0;
        for (int i = 0; i < 3; i++) {
            char ans;
            printf("Is Player %c human? (Y/N): ", symbols[i]);
            scanf(" %c", &ans);
            human[i] = (ans == 'y' || ans == 'Y');
            if (human[i]) humanCount++;
        }

        // Enforce at least one human
        if (humanCount == 0) {
            printf("At least one player must be human! Setting Player %c as human.\n", symbols[0]);
            human[0] = 1;
        }
    }

    int turn=0, move_no=0, game_over=0;
    while (!game_over) {
        display_board(board, n);
        char sym = symbols[turn];
        int r=-1, c=-1;

        if (human[turn]) {
            printf("Player %c enter row and then column (1-%d): ", sym, n);
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
            printf("Player %c Wins.Congratulations!\n", sym);
            if (logf) fprintf(logf,"Player %c Wins.Congratulations!\n",sym);
            game_over=1;
        } else if (check_draw(board,n)) {
            display_board(board,n);
            printf("It's a Draw!\n");
            if (logf) fprintf(logf,"Game ended in Draw.\n");
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

