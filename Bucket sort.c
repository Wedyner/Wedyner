#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void insert(struct Node** bucket, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;

    if (*bucket == NULL) {
        *bucket = newNode;
    } else {
        struct Node* current = *bucket;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

struct Node* insertionSort(struct Node* bucket) {
    if (bucket == NULL || bucket->next == NULL) {
        return bucket;
    }

    struct Node* sorted = NULL;
    struct Node* current = bucket;

    while (current != NULL) {
        struct Node* next = current->next;

        if (sorted == NULL || sorted->data >= current->data) {
            current->next = sorted;
            sorted = current;
        } else {
            struct Node* search = sorted;
            while (search->next != NULL && search->next->data < current->data) {
                search = search->next;
            }
            current->next = search->next;
            search->next = current;
        }

        current = next;
    }

    return sorted;
}

void displayArray(int array[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void displayBucket(struct Node* bucket) {
    struct Node* current = bucket;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void displayBuckets(struct Node* buckets[], int numBuckets) {
    printf("\nBuckets antes da ordenacao:\n");
    for (int i = 0; i < numBuckets; i++) {
        printf("Bucket %d: ", i);
        displayBucket(buckets[i]);
    }

    for (int i = 0; i < numBuckets; i++) {
        buckets[i] = insertionSort(buckets[i]);
    }

    printf("\nBuckets apos a ordenacao:\n");
    for (int i = 0; i < numBuckets; i++) {
        printf("Bucket %d: ", i);
        displayBucket(buckets[i]);
    }
}

void bucketSort(int array[], int n, int numBuckets) {
    struct Node* buckets[numBuckets];
    for (int i = 0; i < numBuckets; i++) {
        buckets[i] = NULL;
    }

    for (int i = 0; i < n; i++) {
        int bucketIndex = (numBuckets * array[i]) / (100 + 1);
        insert(&buckets[bucketIndex], array[i]);
    }

    displayBuckets(buckets, numBuckets);

    int index = 0;
    for (int i = 0; i < numBuckets; i++) {
        struct Node* current = buckets[i];
        while (current != NULL) {
            array[index++] = current->data;
            current = current->next;
        }
    }
}

int main() {
    int numBuckets, n, choice;

    do {
        printf("\nDigite o numero de buckets: ");
        scanf("%d", &numBuckets);

        printf("Digite o numero de elementos: ");
        scanf("%d", &n);

        int array[n];

        printf("Escolha o caso (1 para melhor caso, 2 para pior caso, 0 para sair): ");
        scanf("%d", &choice);

        if (choice != 0) {
            if (choice == 1) {
                printf("Digite os elementos (em ordem crescente):\n");
                for (int i = 0; i < n; i++) {
                    scanf("%d", &array[i]);
                }
            } else {
                printf("Digite os elementos (em ordem decrescente):\n");
                for (int i = 0; i < n; i++) {
                    scanf("%d", &array[i]);
                }
            }

            printf("\nArray antes da ordenacao:\n");
            displayArray(array, n);

            bucketSort(array, n, numBuckets);

            printf("\nArray apos a ordenacao:\n");
            displayArray(array, n);
        }

    } while (choice != 0);

    return 0;
}
