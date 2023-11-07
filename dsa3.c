⦁	#include <stdio.h>
               #include <stdlib.h>
 
struct Node {
    int row;
    int col;
    int value;
    struct Node* next;
};
 
struct Node* createNode(int row, int col, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->row = row;
    newNode->col = col;
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}
 
void insertNode(struct Node** head, int row, int col, int value) {
    struct Node* newNode = createNode(row, col, value);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}
 
void displaySparseMatrix(struct Node* head) {
    if (head == NULL) {
        printf("Sparse matrix is empty.\n");
        return;
    }
    printf("Row\tColumn\tValue\n");
    while (head != NULL) {
        printf("%d\t%d\t%d\n", head->row, head->col, head->value);
        head = head->next;
    }
}
 
int main() {
    int rows, cols;
    printf("Enter the number of rows and columns in the sparse matrix: ");
    scanf("%d %d", &rows, &cols);
 
    struct Node* sparseMatrix = NULL;
 
    printf("Enter the elements of the sparse matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int value;
            scanf("%d", &value);
            if (value != 0) {
                insertNode(&sparseMatrix, i, j, value);
            }
        }
    }
 
    printf("\nLinked list representation of the sparse matrix:\n");
    displaySparseMatrix(sparseMatrix);
 
    return 0;
}
