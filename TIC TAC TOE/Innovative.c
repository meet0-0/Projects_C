#include <stdio.h>

char board[3][3];
char player = 'X';

void start()
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            board[i][j] = ' ';
        }
    }
}

void print()
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            printf(" %c ", board[i][j]);
            if (j < 3 - 1)
                printf("|");
        }
        printf("\n");
        if (i < 3 - 1)
            printf("---|---|---\n");
    }
}

int Win()
{
    for (int i = 0; i < 3; ++i)
    {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player))
            return 1;
    }
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player))
        return 1;
    return 0;
}

int Draw()
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (board[i][j] == ' ')
                return 0;
        }
    }
    return 1;
}

void switchh()
{
    player = (player == 'X') ? 'O' : 'X';
}

void play()
{
    int row, col;
    start();

    while (1)
    {
        print();
        printf("Player %c, enter row & column respectively(0, 1, or 2): ", player);
        scanf("%d %d", &row, &col);

        if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ')
        {
            printf("Invalid move.\n");
            continue;
        }

        board[row][col] = player;

        if (Win())
        {
            print();
            printf("Player %c carries the W\n", player);
            break;
        }
        else if (Draw())
        {
            print();
            printf("Draw!\n");
            break;
        }
        else
        {
            switchh();
        }
    }
}

int main()
{
    play();
    return 0;
}