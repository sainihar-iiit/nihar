#include <stdio.h>
 
int getMax(int arr[], int n) {
    int max = arr[0];
    int i;
    for (i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}
void radixSort(int arr[], int n) {
    int max = getMax(arr, n);
    int exp,i;
    for (exp = 1; max / exp > 0; exp *= 10) {
        int output[n];
        int count[10] = {0};
 
        for (i = 0; i < n; i++) {
            count[(arr[i] / exp) % 10]++;
        }
 
       
        for (i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }
 
       
        for (i = n - 1; i >= 0; i--) {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }
 
        for (i = 0; i < n; i++) {
            arr[i] = output[i];
        }
    }
}
 
int main() {
    int n,i;
 
    printf("Enter the number of elements: ");
    scanf("%d", &n);
 
    int arr[n];
    printf("Enter %d elements:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
 
    radixSort(arr, n);
 
    printf("Sorted Array (in decreasing order): ");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
 
    return 0;
}

 

#include <stdio.h>
#include <stdlib.h>
 
struct Node {
    int data;
    struct Node* next;
};
 
void insert(struct Node** head, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
 
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}
 
void print(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}
 
int Max(struct Node* head) {
    int max = head->data;
    struct Node* temp = head->next;
    while (temp != NULL) {
        if (temp->data > max) {
            max = temp->data;
        }
        temp = temp->next;
    }
    return max;
}
 
void sort(struct Node** head) {
    int max = Max(*head);
    int j,i;
    for (i = 1; max / i > 0; i *= 10) {
        struct Node* output = NULL;
        struct Node* temp = *head;
        struct Node* buckets[10] = { NULL };
 
        while (temp != NULL) {
            int digit = (temp->data / i) % 10;
            insert(&buckets[digit], temp->data);
            temp = temp->next;
        }
 
        for (j = 9; j >= 0; j--) {
            while (buckets[j] != NULL) {
                struct Node* next = buckets[j]->next;
                buckets[j]->next = output;
                output = buckets[j];
                buckets[j] = next;
            }
        }
 
        *head = output;
    }
}
 
int main() {
int i;
    struct Node* head = NULL;
    int n, a;
 
    printf("Enter the number of elements: ");
    scanf("%d", &n);
 
    printf("Enter %d elements:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &a);
        insert(&head, a);
    }
    printf("Given Listis: \n");
    print(head);
   
    sort(&head);
   
    printf("Sorted List: \n");
    print(head);
   
   
    return 0;
}

 