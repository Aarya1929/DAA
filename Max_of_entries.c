#include <stdio.h>

#define MAX_SIZE 10

struct CircularQueue
{
    int size;
    int front, rear;
    int elements[MAX_SIZE];
};

void initializeQueue(struct CircularQueue *queue)
{
    queue->size = 0;
    queue->front = queue->rear = -1;
}

int is_empty(struct CircularQueue *queue)
{
    return queue->front == -1;
}

int is_full(struct CircularQueue *queue)
{
    return (queue->rear + 1) % MAX_SIZE == queue->front;
}

void enqueue(struct CircularQueue *queue, int item)
{
    if (is_full(queue))
    {
        // Circular queue is full, dequeue one element
        dequeue(queue);
    }

    if (is_empty(queue))
    {
        queue->front = queue->rear = 0;
    }
    else
    {
        queue->rear = (queue->rear + 1) % MAX_SIZE;
    }

    queue->elements[queue->rear] = item;
    queue->size++;
}

int dequeue(struct CircularQueue *queue)
{
    if (is_empty(queue))
    {
        return -1; // Queue is empty
    }

    int item = queue->elements[queue->front];

    if (queue->front == queue->rear)
    {
        queue->front = queue->rear = -1;
    }
    else
    {
        queue->front = (queue->front + 1) % MAX_SIZE;
    }

    queue->size--;
    return item;
}

int get_max(struct CircularQueue *queue)
{
    if (is_empty(queue))
    {
        return -1; // Queue is empty
    }

    int max_element = queue->elements[queue->front];
    int current = (queue->front + 1) % MAX_SIZE;

    while (current != (queue->rear + 1) % MAX_SIZE)
    {
        if (queue->elements[current] > max_element)
        {
            max_element = queue->elements[current];
        }
        current = (current + 1) % MAX_SIZE;
    }

    return max_element;
}

int main()
{
    struct CircularQueue circular_queue;
    initializeQueue(&circular_queue);

    int user_input;

    while (1)
    {
        printf("Enter a number (or -1 to stop): ");
        scanf("%d", &user_input);

        if (user_input == -1)
        {
            break;
        }

        enqueue(&circular_queue, user_input);
        if(circular_queue.size==10)
        {
            int max_previous_10 = get_max(&circular_queue);
            printf("Maximum of the previous 10 elements: %d\n", max_previous_10);
        }
    }

    return 0;
}

