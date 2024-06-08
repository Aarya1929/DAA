#include <stdio.h>

#define DECK_SIZE 52

struct CircularQueue {
    int size;
    int front, rear;
    int cards[DECK_SIZE];
};

void initializeDeck(struct CircularQueue* deck) {
    deck->size = 0;
    deck->front = deck->rear = -1;

    for (int i = 1; i <= DECK_SIZE; i++) {
        enqueue(deck, i);
    }
}

int is_empty(struct CircularQueue* deck) {
    return deck->front == -1;
}

int is_full(struct CircularQueue* deck) {
    return (deck->rear + 1) % DECK_SIZE == deck->front;
}

void enqueue(struct CircularQueue* deck, int card) {
    if (is_full(deck)) {
        printf("Deck is full. Cannot enqueue more cards.\n");
        return;
    }

    if (is_empty(deck)) {
        deck->front = deck->rear = 0;
    } else {
        deck->front = (deck->front - 1 + DECK_SIZE) % DECK_SIZE;
    }

    deck->cards[deck->front] = card;
    deck->size++;
}

int dequeue(struct CircularQueue* deck) {
    if (is_empty(deck)) {
        printf("Deck is empty. Cannot dequeue more cards.\n");
        return -1;
    }

    int card = deck->cards[deck->rear];

    if (deck->front == deck->rear) {
        deck->front = deck->rear = -1;
    } else {
        deck->rear = (deck->rear - 1 + DECK_SIZE) % DECK_SIZE;
    }

    deck->size--;
    return card;
}

void shuffleDeck(struct CircularQueue* deck, int numShuffles) {
    for (int i = 0; i < numShuffles; i++) {
        int lastCard = dequeue(deck);
        enqueue(deck, lastCard);
    }
}

int main() {
    struct CircularQueue deck;
    initializeDeck(&deck);

    int numShuffles;
    printf("Enter the number of shuffles: ");
    scanf("%d", &numShuffles);

    shuffleDeck(&deck, numShuffles);

    int topCard = deck.front;
    printf("Top card after %d shuffles: %d\n", numShuffles, topCard);

    int showCardNumber;
    printf("Enter the index number to find the card after: ");
    scanf("%d", &showCardNumber);

    int cardIndex = showCardNumber+1;

    if (cardIndex != deck.rear) {
        printf("Card after card index %d: %d\n", showCardNumber, deck.cards[cardIndex]);
    }
    else
    {
        printf("Card index %d is not found in the remaining cards.\n", cardIndex);
    }

    return 0;
}
