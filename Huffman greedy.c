#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FREQ 256

struct Node
{
    char data;
    int freq;
    struct Node *left;
    struct Node *right;
    struct Node *next;
};

struct MapEntry
{
    char key;
    char value[256];
    struct MapEntry *next;
};

struct Node *newNode(char data, int freq)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = data;
    node->freq = freq;
    node->left = NULL;
    node->right = NULL;
    node->next = NULL;
    return node;
}

void insert(struct Node **head, struct Node *newNode)
{
    struct Node *current = *head;
    struct Node *prev = NULL;

    while (current != NULL && current->freq < newNode->freq)
    {
        prev = current;
        current = current->next;
    }
    if (prev == NULL)
    {
        newNode->next = *head;
        *head = newNode;
    }
    else
    {
        newNode->next = current;
        prev->next = newNode;
    }
}

struct Node *pop(struct Node **head)
{
    struct Node *temp = *head;
    *head = (*head)->next;
    temp->next = NULL;
    return temp;
}

void calculateFreq(const char *s, int *freq)
{
    for (int i = 0; s[i] != '\0'; i++)
    {
        freq[(unsigned char)s[i]]++;
    }
}

void storeCodes(struct Node *root, struct MapEntry **mapHead, char *str, int strIndex)
{
    if (root == NULL)
    {
        return;
    }

    if (root->data != '$')
    {
        str[strIndex] = '\0';
        struct MapEntry *newEntry = (struct MapEntry *)malloc(sizeof(struct MapEntry));
        newEntry->key = root->data;
        strncpy(newEntry->value, str, 256);
        newEntry->next = *mapHead;
        *mapHead = newEntry;
    }

    str[strIndex] = '0';
    storeCodes(root->left, mapHead, str, strIndex + 1);

    str[strIndex] = '1';
    storeCodes(root->right, mapHead, str, strIndex + 1);
}

struct Node *getHuffmanCodes(int *freq, struct MapEntry **mapHead)
{
    struct Node *pq = NULL;

    for (int i = 0; i < MAX_FREQ; i++)
    {
        if (freq[i] > 0)
        {
            struct Node *node = newNode((char)i, freq[i]);
            insert(&pq, node);
        }
    }

    while (pq->next != NULL)
    {
        struct Node *left = pop(&pq);
        struct Node *right = pop(&pq);

        struct Node *top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        insert(&pq, top);
    }

    char str[256] = "";
    storeCodes(pq, mapHead, str, 0);

    return pq;
}

const char *map_get(struct MapEntry *mapHead, char key)
{
    struct MapEntry *current = mapHead;
    while (current != NULL)
    {
        if (current->key == key)
        {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

char *decodeString(struct Node *root, const char *s)
{
    char *ans = (char *)malloc((strlen(s) + 1) * sizeof(char));
    int ansIndex = 0;
    struct Node *curr = root;

    for (int i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == '0')
        {
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }

        if (curr->left == NULL && curr->right == NULL)
        {
            ans[ansIndex++] = curr->data;
            curr = root;
        }
    }

    ans[ansIndex] = '\0';
    return ans;
}

int main()
{
    char s[1000];
    printf("Enter the string: ");
    scanf("%s", s);

    int freq[MAX_FREQ] = {0};

    calculateFreq(s, freq);

    struct MapEntry *mapHead = NULL;

    struct Node *root = getHuffmanCodes(freq, &mapHead);

    printf("Huffman Codes are:\n");
    struct MapEntry *current = mapHead;
    while (current != NULL)
    {
        printf("%c: %s\n", current->key, current->value);
        current = current->next;
    }

    char encodedString[1000] = "";
    for (int i = 0; s[i] != '\0'; i++)
    {
        const char *code = map_get(mapHead, s[i]);
        strcat(encodedString, code);
    }

    printf("Encoded String: %s\n", encodedString);

    char *decodedString = decodeString(root, encodedString);
    printf("Decoded String: %s\n", decodedString);

    free(decodedString);

    current = mapHead;
    while (current != NULL)
    {
        struct MapEntry *temp = current;
        current = current->next;
        free(temp);
    }

    free(root);

    return 0;
}
