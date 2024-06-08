#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100

typedef struct
{
    int rows[MAX_N];
} Solution;

Solution results[MAX_N];
int result_count = 0;

int isSafe(int board[MAX_N][MAX_N], int row, int col, int n)
{
    int i, j;

    for (i = 0; i < col; i++)
    {
        if (board[row][i] == 1)
        {
            return 0;
        }
    }

    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
    {
        if (board[i][j] == 1)
        {
            return 0;
        }
    }

    for (i = row, j = col; i < n && j >= 0; i++, j--)
    {
        if (board[i][j] == 1)
        {
            return 0;
        }
    }

    return 1;
}

int solveNQUtil(int board[MAX_N][MAX_N], int col, int n)
{
    if (col == n)
    {
        Solution sol;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (board[i][j] == 1)
                {
                    sol.rows[i] = j + 1;
                }
            }
        }
        results[result_count++] = sol;
        return 1;
    }

    int res = 0;
    for (int i = 0; i < n; i++)
    {
        if (isSafe(board, i, col, n))
        {
            board[i][col] = 1;

            res = solveNQUtil(board, col + 1, n) || res;

            board[i][col] = 0;
        }
    }

    return res;
}

int nQueen(int n)
{
    int board[MAX_N][MAX_N] = {0};
    result_count = 0;

    if (!solveNQUtil(board, 0, n))
    {
        return 0;
    }

    return 1;
}

int main()
{
    int n;
    printf("Enter the number of Queens: ");
    scanf("%d", &n);

    if (n == 1)
    {
        printf("[1]\n");
    }
    else if (n == 2 || n == 3)
    {
        printf("No solution\n");
    }
    else
    {
        // Solve the N-Queens problem
        int found = nQueen(n);

        if (!found)
        {
            printf("No solution\n");
            return 0;
        }

        int index = -1;
        while (1)
        {
            int k;
            printf("Enter 1 for the next solution: ");
            scanf("%d", &k);
            if (k == 1)
            {
                index++;
                if (index >= result_count)
                {
                    break;
                }

                printf("\n");
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        if (results[index].rows[i] == j + 1)
                        {
                            printf("1 ");
                        }
                        else
                        {
                            printf("0 ");
                        }
                    }
                    printf("\n");
                }
                printf("\n");
            }
        }
        printf("All solutions are printed\n");
    }

    return 0;
}
