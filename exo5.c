#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct BinarySearchTree {
    Node* root;
} BinarySearchTree;

void addValue(BinarySearchTree* table, int index, int value) {
    insertNode(&table[index].root, value);
}

Node* createNode(int value) {
    Node* newNode = malloc(sizeof(Node));
    newNode->value = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void insertNode(Node** root, int value) {
    if (*root == NULL) {
        *root = createNode(value);
        return;
    }
    if (value < (*root)->value) {
        insertNode(&(*root)->left, value);
    } else {
        insertNode(&(*root)->right, value);
    }
}


void fillEmptyTrees(BinarySearchTree* table, int size, int maxNodes) {
    for (int i = 0; i < size; i++) {
        if (table[i].root == NULL) {
            int nodes = rand() % maxNodes + 1;
            for (int j = 0; j < nodes; j++) {
                int value = rand() % 1001; // Valeurs entre 0 to 1000
                insertNode(&table[i].root, value);
            }
        }
    }
}

void bubbleSort(BinarySearchTree* table, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            // Get the root values for comparison
            int rootValue1 = (table[j].root != NULL) ? table[j].root->value : INT_MAX;
            int rootValue2 = (table[j + 1].root != NULL) ? table[j + 1].root->value : INT_MAX;

            // Swap if out of order
            if (rootValue1 > rootValue2) {
                // Swap the entire tree objects
                BinarySearchTree temp = table[j];
                table[j] = table[j + 1];
                table[j + 1] = temp;
            }
        }
    }
}
BinarySearchTree* initializeTable(int size) {
    BinarySearchTree* table = (BinarySearchTree*)malloc(size * sizeof(BinarySearchTree));
    for (int i = 0; i < size; i++) {
        table[i].root = NULL; // Initialize all trees as empty
    }
    return table;
}

Node* searchNode(Node* root, int value) {
    if (root == NULL) return NULL;
    if (root->value == value) return root;
    if (value < root->value) return searchNode(root->left, value);
    return searchNode(root->right, value);
}



int searchInTree(BinarySearchTree* table, int size, int index, int value) {
    if (index < 0 || index >= size) {
        printf("Erreur: Index %d hors limites (0 à %d).\n", index, size - 1);
        return 0; // Invalid index
    }
    if (table[index].root == NULL) {
        printf("L'arbre à l'index %d est vide.\n", index);
        return 0; // Tree is empty
    }
    return searchNode(table[index].root, value);
}



int searchInAllTrees(BinarySearchTree* table, int size, int value) {
    if (size <= 0) {
        printf("Error: The array is empty.\n");
        return -1;
    }

    for (int i = 0; i < size; i++) {
        int result = searchInAllTrees(table, size, value);
        if (result != -1) {
           printf("Value %d found in tree %d.\n", value, result);
        } else {
           printf("Value %d NOT found in any tree.\n", value);
}

    }

    printf("Value %d NOT found in any tree.\n", value);
    return -1;
}


int treeSize(Node* root) {
    if (root == NULL) return 0;
    return 1 + treeSize(root->left) + treeSize(root->right);
}

int findMin(Node* root) {
    while (root && root->left != NULL) {
        root = root->left;
    }
    return root ? root->value : -1;
}

int findMax(Node* root) {
    while (root && root->right != NULL) {
        root = root->right;
    }
    return root ? root->value : -1;
}

void inorderTraversal(Node* root) {
    if (root) {
        inorderTraversal(root->left);
        printf("%d ", root->value);
        inorderTraversal(root->right);
    }
}

void preorderTraversal(Node* root) {
    if (root) {
        printf("%d ", root->value);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

void postorderTraversal(Node* root) {
    if (root) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->value);
    }
}

void menu() {
    int size, choice, index, value, maxNodes;
    printf("Enter the size of the array: ");
    scanf("%d", &size);

    BinarySearchTree* table = initializeTable(size);

    srand(time(NULL)); // Initialize random seed for automatic filling

    while (1) {
        printf("\nMenu:\n");
        printf("1. Add a value to a tree\n");
        printf("2. Automatically fill empty slots\n");
        printf("3. Sort the array by tree root values\n");
        printf("4. Search for a value in a specific tree\n");
        printf("5. Search for a value in all trees\n");
        printf("6. Display a tree (inorder, preorder, postorder)\n");
        printf("7. Show all root values in the array\n");
        printf("0. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the index of the tree and the value to add: ");
                scanf("%d %d", &index, &value);
                if (index < 0 || index >= size) {
                    printf("Error: Index %d is out of bounds (0 to %d).\n", index, size - 1);
                } else {
                    addValue(table, index, value);
                    printf("Value %d added to tree %d.\n", value, index);
                }
                break;

            case 2:
                printf("Enter the maximum number of nodes per tree: ");
                scanf("%d", &maxNodes);
                fillEmptyTrees(table, size, maxNodes);
                printf("Empty slots have been filled with random trees.\n");
                break;

            case 3:
                bubbleSort(table, size);
                printf("Array sorted by root values of the trees.\n");
                printf("Sorted root values: ");
                printf("Sorted root values (after sorting by root):\n");
                for (int i = 0; i < size; i++) {
                if (table[i].root != NULL)
                    printf("Tree %d Root: %d\n", i, table[i].root->value);
                else
                    printf("Tree %d is empty\n", i);
                }
                printf("\n");
                break;

            case 4:
                printf("Enter the index of the tree and the value to search for: ");
                scanf("%d %d", &index, &value);
                if (searchInTree(table, size, index, value)) {
                    printf("Value %d found in tree %d.\n", value, index);
                } else {
                    printf("Value %d NOT found in tree %d.\n", value, index);
                }
                break;

            case 5:
                printf("Enter the value to search for in all trees: ");
                scanf("%d", &value);
                searchInAllTrees(table, size, value);
                break;

            case 6:
                printf("Enter the index of the tree to display: ");
                scanf("%d", &index);
                if (index < 0 || index >= size) {
                    printf("Error: Index %d is out of bounds (0 to %d).\n", index, size - 1);
                } else if (table[index].root == NULL) {
                    printf("The tree at index %d is empty.\n", index);
                } else {
                    printf("Inorder traversal: ");
                    inorderTraversal(table[index].root);
                    printf("\nPreorder traversal: ");
                    preorderTraversal(table[index].root);
                    printf("\nPostorder traversal: ");
                    postorderTraversal(table[index].root);
                    printf("\n");
                }
                break;

            case 7:
                printf("Root values of the trees in the array:\n");
                for (int i = 0; i < size; i++) {
                    if (table[i].root != NULL)
                        printf("Tree %d Root: %d\n", i, table[i].root->value);
                    else
                        printf("Tree %d is empty.\n", i);
                }
                break;

            case 0:
                printf("Exiting the program. Goodbye!\n");
                free(table); // Free memory allocated for the table
                return;

            default:
                printf("Invalid option. Please try again.\n");
        }
    }
}


int main() {
    printf("Welcome to the binary tree management program !\n");
    menu();
    printf("Thank you for using the program. See you soon!!\n");
    return 0;
}