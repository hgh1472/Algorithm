/*
연결리스트에 대한 합병정렬 구현
head는 더미 노드로 정렬은 head->next부터 정렬을 수행한다.
정렬 과정
1) 하나의 리스트를 n / 2를 기준으로 두 개의 L1, L2 부리스트로 나눈다.
2) L1, L2에 대해서도 합병정렬을 수행한다.
3) 정렬된 L1, L2를 통해 전체 리스트 L에 합병정렬을 해준다.

L1, L2를 통해 정렬된 하나의 리스트 L을 만드는 과정
L은 L1과 L2 리스트를 훑으면서 둘 중 작은 값을 L에 넣어준다.
여기서 L에 넣는다는 것은 하나의 노드를 할당하는 것이 아니라, L이 L1 또는 L2에 있는 노드를 가르키게 한다.
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    struct node *next;
} Node;

Node *getNode(int num) {
    Node *new = (Node *)malloc(sizeof(Node));
    new->key = num;
    new->next = NULL;
    return new;
}

void insertion(int n, Node *head) {
    int key;

    for (int i = 0; i < n; i++) {
        scanf("%d", &key);
        head->next = getNode(key);
        head = head->next;
    }
    head->next = NULL;
}

void partition(Node *L, Node **L1, Node **L2, int n) {
    *L1 = L;
    for (int i = 0; i < n / 2 - 1; i++) L = L->next;
    *L2 = L->next;
    L->next = NULL;
}

Node *Merge(Node *L1, Node *L2) {
    Node *L = (Node *)malloc(sizeof(Node));
    Node *temp = L;

    while (L1 != NULL && L2 != NULL) {
        if (L1->key <= L2->key) {
            temp->next = getNode(L1->key);
            L1 = L1->next;
            temp = temp->next;
        } else {
            temp->next = getNode(L2->key);
            L2 = L2->next;
            temp = temp->next;
        }
    }
    while (L1 != NULL) {
        temp->next = getNode(L1->key);
        L1 = L1->next;
        temp = temp->next;
    }
    while (L2 != NULL) {
        temp->next = getNode(L2->key);
        L2 = L2->next;
        temp = temp->next;
    }
    temp->next = NULL;
    return L->next;
}

void rMergeSort(Node **L, int n) {
    if (n <= 1) return;

    Node *L1, *L2;
    Node *temp = *L;
    partition(*L, &L1, &L2, n);
    rMergeSort(&L1, n / 2);
    rMergeSort(&L2, n / 2 + (n % 2));
    *L = Merge(L1, L2);
}

void mergeSort(Node **L, int n) { rMergeSort(L, n); }

void printList(Node *h) {
    while (h->next != NULL) {
        h = h->next;
        printf(" %d", h->key);
    }
    printf("\n");
}

int main() {
    int n;
    Node *head = (Node *)malloc(sizeof(Node));

    scanf("%d", &n);
    insertion(n, head);
    mergeSort(&(head->next), n);
    printList(head);
}