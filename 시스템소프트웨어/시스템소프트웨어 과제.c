#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct Tree {
    double data;
    struct Tree* left;
    struct Tree* right;
} Tree;

Tree* root = NULL;

void insert(Tree** node, double data) {
    if (*node == NULL) {
        Tree* newNode = (Tree*)malloc(sizeof(Tree));
        if (newNode == NULL) {
            exit(1);
        }
        newNode->data = data;
        newNode->left = newNode->right = NULL;
        *node = newNode;
    }
    else {
        if (data < (*node)->data) {
            insert(&((*node)->left), data);
        }
        else if (data > (*node)->data) {
            insert(&((*node)->right), data);
        }
    }
}

int getSize(Tree* node) {
    if (node == NULL) {
        return 0;
    }
    else {
        return 1 + getSize(node->left) + getSize(node->right);
    }
}

bool isPrime(int num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;

    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) {
            return false;
        }
    }

    return true;
}

int countPrime(Tree* node) {
    int count = 0;

    if (node == NULL) {
        return 0;
    }
    if (isPrime(node->data + 1) || isPrime(node->data - 1)) {
        count++;
    }
    count += countPrime(node->left);
    count += countPrime(node->right);

    return count;
}

void delete(Tree* node) {
    if (node == NULL) {
        return;
    }
    delete(node->left);
    delete(node->right);
    free(node);
}


int main() {
    double num;

    FILE* file = fopen("input.txt", "r");
    if (file == NULL) {
        return 1;
    }

    while (fscanf(file, "%lf", &num) != EOF) {
        insert(&root, num);
    }

    int treeSize = getSize(root);
    printf("Only one count : %d\n", treeSize);

    int primeCount = countPrime(root);
    printf("Near prime count : %d\n", primeCount);

    delete(root);

    fclose(file);

    return 0;
}