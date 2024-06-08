#include <stdio.h>

// Function to find the survivor in Josephus problem
int josephus(int n, int k) {
    // Create an array to represent people and initialize with 0
    int people[n];
    for (int i = 0; i < n; i++) {
        people[i] = i + 1;
    }

    // Elimination process
    int index = 0;
    for (int count = 1; count < n; count++) {
        int step = 0;
        while (step < k) {
            if (people[index] != -1) {
                step++;
            }
            if (step < k) {
                index = (index + 1) % n;
            }
        }
        people[index] = -1; // Eliminate the k-th person
    }

    // Find the survivor
    int survivor = -1;
    for (int i = 0; i < n; i++) {
        if (people[i] != -1) {
            survivor = people[i];
            break;
        }
    }

    return survivor;
}

// Driver code
int main() {
    int n = 6; // Number of people
    int k = 2; // Elimination every k-th person

    int survivor = josephus(n, k);
    printf("The survivor is person %d\n", survivor);

    return 0;
}

