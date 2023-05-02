#include <stdio.h>
#include <stdlib.h>

struct HeapTree {
    struct HeapNode** array;
    int len;
    int is_max_tree;  // 1 for max heap, 0 for min heap (default is max heap)
};

struct HeapNode {
    int data;
};

void addElement2Heap(struct HeapTree** root, int data);
int removeElementFromHeap(struct HeapTree** root, int data);
void swap(struct HeapNode** a, struct HeapNode** b);
void printHeap(struct HeapTree* root);
int findElementInHeap(struct HeapTree* root, int data);
void heapHeapify(struct HeapTree* root);
void heapify(struct HeapTree* root, int index);

int heapDelete(struct HeapTree** root, int data);
int heapInsert(struct HeapTree** root, int data);
struct HeapNode* heapPeek(struct HeapTree* root);
struct HeapNode* heapPopPeek(struct HeapTree** root);

int main() {
    struct HeapTree* root = (struct HeapTree*)malloc(sizeof(struct HeapTree));
    root->len = 0;
    root->is_max_tree = 1;

    heapInsert(&root, 10);
    heapInsert(&root, 12);
    heapInsert(&root, 13);
    heapInsert(&root, 21);
    heapInsert(&root, 15);

    printHeap(root);

    struct HeapNode* x = heapPopPeek(&root);

    printHeap(root);

    printf("\n\n*Program ended successfully*\n");
}

struct HeapNode* heapPopPeek(struct HeapTree** root) {
    struct HeapNode* temp = heapPeek(*root);
    heapDelete(root, temp->data);
    return temp;
}

struct HeapNode* heapPeek(struct HeapTree* root) {
    struct HeapNode* x = (struct HeapNode*)malloc(sizeof(struct HeapNode));
    x->data = root->array[0]->data;
    return x;
}

int heapDelete(struct HeapTree** root, int data) {
    if (removeElementFromHeap(root, data) == -1)
        return -1;

    heapHeapify(*root);
}

int heapInsert(struct HeapTree** root, int data) {
    addElement2Heap(root, data);
    heapHeapify(*root);
    return 1;
}

int removeElementFromHeap(struct HeapTree** root, int data) {
    int index = findElementInHeap(*root, data);
    if (index == -1) return -1;

    swap(&(*root)->array[index], &(*root)->array[(*root)->len - 1]);
    (*root)->len--;
    free((*root)->array[(*root)->len]);
    (*root)->array = (struct HeapNode**)realloc((*root)->array, (*root)->len * sizeof(struct HeapNode*));

    return 1;
}

void heapHeapify(struct HeapTree* root) {
    int i = root->len - 1;
    for (i = i / 2; i >= 0; i--) {
        heapify(root, i);
    }
}

void heapify(struct HeapTree* root, int index) {
    int leftIndex = 2 * index + 1;
    int rightIndex = 2 * index + 2;
    int M = index;

    if (root->is_max_tree == 1) {
        if (leftIndex < root->len && root->array[leftIndex]->data > root->array[M]->data)
            M = leftIndex;

        if (rightIndex < root->len && root->array[rightIndex]->data > root->array[M]->data)
            M = rightIndex;
    } else {
        if (leftIndex < root->len && root->array[leftIndex]->data < root->array[M]->data)
            M = leftIndex;

        if (rightIndex < root->len && root->array[rightIndex]->data < root->array[M]->data)
            M = rightIndex;
    }
    if (M != index) {
        swap(&root->array[index], &root->array[M]);
        heapify(root, M);
    }
}

void swap(struct HeapNode** a, struct HeapNode** b) {
    struct HeapNode* temp = *a;
    *a = *b;
    *b = temp;
}

void addElement2Heap(struct HeapTree** root, int data) {
    struct HeapNode* newNode = (struct HeapNode*)malloc(sizeof(struct HeapNode));
    newNode->data = data;

    (*root)->len++;

    if ((*root)->len == 1)  // if the heap is empty
        (*root)->array = (struct HeapNode**)malloc(sizeof(struct HeapNode*));
    else
        (*root)->array = (struct HeapNode**)realloc((*root)->array, (*root)->len * sizeof(struct HeapNode*));

    (*root)->array[(*root)->len - 1] = newNode;
}

int findElementInHeap(struct HeapTree* root, int data) {
    int i;
    for (i = 0; i < root->len; i++) {
        if (root->array[i]->data == data)
            return i;
    }
    return -1;
};

void printHeap(struct HeapTree* root) {
    int i;
    printf("\n");
    for (i = 0; i < root->len; i++) {
        printf("%d ", root->array[i]->data);
    }
    printf("\n");
}