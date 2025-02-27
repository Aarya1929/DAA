#include <stdio.h>

#define MAX_SIZE 128

int size_of_grid, a, b, cnt = 0;
int arr[MAX_SIZE][MAX_SIZE];

// Placing tile at the given coordinates
void place(int x1, int y1, int x2, int y2, int x3, int y3) {
    cnt++;
    arr[x1][y1] = cnt;
    arr[x2][y2] = cnt;
    arr[x3][y3] = cnt;
}

// Quadrant names
// 1   2
// 3   4

// Function based on divide and conquer
void tile(int n, int x, int y) {
    int r = 0, c = 0;
    if (n == 2) {
        cnt++;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (arr[x + i][y + j] == 0) {
                    arr[x + i][y + j] = cnt;
                }
            }
        }
        return;
    }

    // finding hole location
    for (int i = x; i < x + n; i++) {
        for (int j = y; j < y + n; j++) {
            if (arr[i][j] != 0) {
                r = i;
                c = j;
            }
        }
    }

    // If missing tile is in the 1st quadrant
    if (r < x + n / 2 && c < y + n / 2)
        place(x + n / 2, y + (n / 2) - 1, x + n / 2,
              y + n / 2, x + n / 2 - 1, y + n / 2);

    // If missing Tile is in the 3rd quadrant
    else if (r >= x + n / 2 && c < y + n / 2)
        place(x + (n / 2) - 1, y + (n / 2), x + (n / 2),
              y + n / 2, x + (n / 2) - 1, y + (n / 2) - 1);

    // If missing Tile is in the 2nd quadrant
    else if (r < x + n / 2 && c >= y + n / 2)
        place(x + n / 2, y + (n / 2) - 1, x + n / 2,
              y + n / 2, x + n / 2 - 1, y + n / 2 - 1);

    // If missing Tile is in the 4th quadrant
    else if (r >= x + n / 2 && c >= y + n / 2)
        place(x + (n / 2) - 1, y + (n / 2), x + (n / 2),
              y + (n / 2) - 1, x + (n / 2) - 1,
              y + (n / 2) - 1);

    // dividing it again into 4 quadrants
    tile(n / 2, x, y + n / 2);
    tile(n / 2, x, y);
    tile(n / 2, x + n / 2, y);
    tile(n / 2, x + n / 2, y + n / 2);
}

// Driver code
int main() {
    // size of box
    size_of_grid = 8;

    // Coordinates which will be marked
    a = 0;
    b = 0;

    // Here tile cannot be placed
    arr[a][b] = -1;
    tile(size_of_grid, 0, 0);

    // The grid is
    for (int i = 0; i < size_of_grid; i++) {
        for (int j = 0; j < size_of_grid; j++)
            printf("%d ", arr[i][j]);
        printf("\n");
    }

    return 0;
}
