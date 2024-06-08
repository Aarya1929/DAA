#include<stdio.h>

#define Sack_size 5
#define Items_tot 4

// items wt value
int items[Items_tot][2] = {{2, 12},
                           {1, 10},
                           {3, 20},
                           {2, 15}};

int V[Items_tot + 1][Sack_size + 1];

void initialize_v() {
    for (int i = 0; i < Items_tot + 1; i++) {
        V[i][0] = 0;
    }
    for (int i = 0; i < Sack_size + 1; i++) {
        V[0][i] = 0;
    }
}

int max(int n1, int n2) {
    return (n1 > n2) ? n1 : n2;
}

int knapsack(int n, int w) {
    if (n == 0 || w == 0) {
        return 0;
    }

    if (V[n][w] != -1) {
        return V[n][w];
    }

    if (items[n - 1][0] > w) {
        V[n][w] = knapsack(n - 1, w);
    } else {
        V[n][w] = max(knapsack(n - 1, w), items[n - 1][1] + knapsack(n - 1, w - items[n - 1][0]));
    }

    return V[n][w];
}

void fill_v() {
    for (int i = 1; i <= Items_tot; i++) {
        for (int j = 1; j <= Sack_size; j++) {
            V[i][j] = -1; // Initialize with -1 to indicate that the cell is not yet filled
        }
    }

    knapsack(Items_tot, Sack_size);
}

void print_v() {
    for (int i = 0; i < Items_tot + 1; i++) {
        for (int j = 0; j < Sack_size + 1; j++) {
            printf("%d ", V[i][j]);
        }
        printf("\n");
    }
}

int main() {
    initialize_v();
    fill_v();
    printf("Table V:\n");
    print_v();
    printf("\nMaximum Profit:%d\n", V[Items_tot][Sack_size]);
    return 0;
}
