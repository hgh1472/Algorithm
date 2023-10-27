#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
} Node;

typedef struct q
{
    Node *queue[1000];
    int front;
    int rear;
} QueueType;

Node *Parent(Node *head, int n);
void upHeap(Node *head, Node *v, int n);
void downHeap(Node *head);
void printHeap(Node *v);

Node *findNode(Node *head, int n)
{
    int binary[30];

    int i = 0;
    while (n > 1)
    {
        binary[i++] = n % 2;
        n /= 2;
    }
    for (int j = i - 1; j >= 0; j--)
    {
        if (binary[j] == 0)
            head = head->left;
        else
            head = head->right;
    }
    return head;
}

Node *init(int key)
{
    Node *new = (Node *)malloc(sizeof(Node));
    new->data = key;
    new->right = NULL;
    new->left = NULL;
    return new;
}

void upHeap(Node *head, Node *v, int n)
{
    if (head == v)
        return;
    Node *p = Parent(head, n);
    if (v->data <= p->data)
        return;
    int tmp;
    tmp = v->data;
    v->data = p->data;
    p->data = tmp;
    upHeap(head, p, n / 2);
}

void insertItem(Node **H, Node **last, int key, int n)
{
    if (n == 1)
    {
        *H = init(key);
        *last = *H;
        return;
    }
    else
    {
        Node *p = Parent(*H, n);
        if (n % 2 == 0)
        {
            p->left = init(key);
            p = p->left;
            *last = p;
        }
        else
        {
            p->right = init(key);
            p = p->right;
            *last = p;
        }
        upHeap(*H, p, n);
    }
}

void removeMin(Node **last, Node *head, int n)
{
    printf("%d\n", head->data);
    head->data = (*last)->data;
    Node *p = Parent(head, n);
    if (n % 2 == 0)
    {
        free(p->left);
        p->left = NULL;
    }
    else
    {
        free(p->right);
        p->right = NULL;
    }
    downHeap(head);
}

void downHeap(Node *v)
{
    if (v->right == NULL && v->left == NULL)
        return;
    Node *smaller = v->left;
    if (v->right != NULL)
    {
        if (v->left->data < v->right->data)
            smaller = v->right;
    }
    if (smaller->data <= v->data)
        return;
    int tmp = smaller->data;
    smaller->data = v->data;
    v->data = tmp;
    downHeap(smaller);
}

Node *Parent(Node *head, int n)
{
    int binary[30];

    int i = 0;
    while (n > 1)
    {
        binary[i++] = n % 2;
        n /= 2;
    }
    for (int j = i - 1; j > 0; j--)
    {
        if (binary[j] == 0)
            head = head->left;
        else
            head = head->right;
    }
    return head;
}

void enqueue(QueueType *q, Node *temp)
{
    q->rear = (q->rear + 1) % 1000;
    q->queue[q->rear] = temp;
}

Node *dequeue(QueueType *q)
{
    q->front = (q->front + 1) % 1000;
    return q->queue[q->front];
}
void printHeap(Node *v)
{
    QueueType q;
    q.front = 0;
    q.rear = 0;
    enqueue(&q, v);
    while (q.front != q.rear)
    {
        v = dequeue(&q);
        printf(" %d", v->data);
        if (v->left != NULL)
            enqueue(&q, v->left);
        if (v->right != NULL)
            enqueue(&q, v->right);
    }
}

int main()
{
    Node *head = NULL;
    Node *Last = NULL;
    char command;
    int key;
    int n = 0;

    while (1)
    {
        scanf("%c", &command);
        getchar();
        if (command == 'q')
            break;
        switch (command)
        {
        case 'i':
            scanf("%d", &key);
            getchar();
            insertItem(&head, &Last, key, ++n);
            printf("0\n");
            break;
        case 'd':
            removeMin(&Last, head, n);
            n--;
            break;
        case 'p':
            printHeap(head);
            printf("\n");
            break;
        default:
            break;
        }
    }
    return 0;
}