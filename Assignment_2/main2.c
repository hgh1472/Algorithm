#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *parent;
    struct node *left;
    struct node *right;
} Node;

// 레벨 순서로 순회하기 위한 큐 자료구조.
typedef struct q
{
    Node *queue[1000]; // 노드 포인터를 담을 배열.
    int front;
    int rear;
} QueueType;

Node *getnode(int key);
int isRoot(Node *v);
void upHeap(Node *v);
void advanceLast(Node **Last);
void expandExternal(Node *z);
void insertItem(Node **H, Node **Last, int key);
Node *root(Node *v);
void retreatLast(Node **last);
Node *reduceExternal(Node *z);
void removeMax(Node **last);
int isExternal(Node *v);
void downHeap(Node *v);
void enqueue(QueueType *q, Node *temp);
Node *dequeue(QueueType *q);
void printHeap(Node *v);
void freeTree(Node *v);

Node *getnode(int key) // 노드를 할당
{
    Node *new = (Node *)malloc(sizeof(Node));
    new->data = key;
    new->parent = NULL;
    new->right = NULL;
    new->left = NULL;
    return new;
}

int isRoot(Node *v) // 노드 v가 루트노드인지 판별한다.
{
    if (v->parent == NULL)
        return 1;
    return 0;
}

void upHeap(Node *v) // 노드 삽입 후, upHeap을 통해 자리를 찾는다.
{
    if (isRoot(v)) // 루트노드면 return.
        return;
    if (v->data <= v->parent->data) // 부모노드의 값이 더 크면 return.
        return;

    // 자식노드의 값이 더 크기 때문에, v 노드와 v의 부모노드의 값을 바꾼다.
    int tmp = v->data;
    v->data = v->parent->data;
    v->parent->data = tmp;
    upHeap(v->parent); // data 값이 바뀐 부모노드도 같은 upHeap과정을 수행한다.
}

void advanceLast(Node **last) // 노드 삽입 후 last노드의 자리를 수정한다.
{
    while ((*last)->parent != NULL && (*last)->parent->right == (*last)) // 노드가 오른쪽 노드라면,
        (*last) = (*last)->parent;                                       // 부모 노드로 이동
    if ((*last)->parent != NULL && (*last)->parent->left == (*last))     // 왼쪽 자식 노드라면
        (*last) = (*last)->parent->right;                                // 형제 노드로 이동
    while ((*last)->left != NULL)                                        // 왼쪽 자식 노드가 존재한다면
        (*last) = (*last)->left;                                         // 왼쪽 자식 노드로 이동
}

void expandExternal(Node *z) // 노드 확장
{
    Node *l = getnode(0); // external 노드는 데이터를 0으로 설정
    Node *r = getnode(0); // external 노드는 데이터를 0으로 설정
    l->parent = z;
    r->parent = z;
    z->left = l;
    z->right = r;
}

void insertItem(Node **H, Node **Last, int key)
{
    if (*Last == NULL) // 첫 노드 삽입일 때
    {
        *H = getnode(key);
        *Last = *H;
        expandExternal(*H);
        return;
    }
    advanceLast(Last); // last 노드 위치 수정
    Node *z = *Last;
    z->data = key;
    expandExternal(z); // 삽입 노드 확장
    upHeap(z);         // 삽입노드 upHeap 수행
}

Node *root(Node *v) // 루트노드로 이동
{
    while (v->parent != NULL)
        v = v->parent;
    return v;
}

void retreatLast(Node **last) // 삭제시 last노드 수정
{
    // 왼쪽 자식 노드라면, 부모노드로 이동.
    while ((*last)->parent != NULL && (*last)->parent->left == (*last))
        (*last) = (*last)->parent;
    // 오른쪽 자식 노드라면, 형제 노드로 이동.
    if ((*last)->parent != NULL && (*last)->parent->right == (*last))
        (*last) = (*last)->parent->left;
    // 오른쪽 자식 노드가 내부노드라면, 오른쪽 자식 노드로 이동.
    while ((*last)->right->data != 0)
        (*last) = (*last)->right;
}

Node *reduceExternal(Node *z) // 노드 확장 해제, z는 제거되는 last노드의 오른쪽 자식 노드.
{
    // w는 last 노드의 위치.
    Node *w = z->parent;
    Node *zs;
    // zs는 z의 형제노드.
    zs = w->left;
    // 제거되는 노드가 루트노드라면, zs는 z의 부모노드가 된다.
    if (isRoot(w))
    {
        z->parent = zs;
        zs->parent = NULL;
    }
    // 루트노드가 아니라면, w와 zs의 위치를 바꾼다.
    else
    {
        Node *g = w->parent;
        zs->parent = g;
        if (w == g->left)
            g->left = zs;
        else
            g->right = zs;
    }
    free(z);
    free(w);
    return zs;
}
void removeMax(Node **last)
{
    Node *r = root(*last);
    int k = r->data;
    Node *w = *last;
    r->data = w->data; // 루트노드의 data를 last 노드의 data로 바꾼다.
    retreatLast(last); // last 노드 위치 수정
    Node *z = w->right;
    reduceExternal(z); // 기존 last 노드 할당 해제
    downHeap(r);
    printf("%d\n", k);
}

int isExternal(Node *v) // 외부노드인지 판별
{
    if (v->data == 0)
        return 1;
    return 0;
}
void downHeap(Node *v)
{
    if (isExternal(v->left) && isExternal(v->right)) // 힙의 끝 자리라면 return.
        return;
    Node *bigger = v->left;
    if (!isExternal(v->right))
    {
        if (v->right->data > bigger->data)
            bigger = v->right;
    }
    if (v->data >= bigger->data) // 자식노드들 중 가장 큰 값이 부모노드 값보다 작다면 return.
        return;
    // 부모노드와 bigger노드의 data 값을 swap한다.
    int tmp = v->data;
    v->data = bigger->data;
    bigger->data = tmp;
    downHeap(bigger); // bigger 노드에 대해서도 downHeap과정 수행.
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
void printHeap(Node *v) // 레벨순회를 통한 힙 자료구조 출력.
{
    QueueType q; // 레벨순회를 위해 큐 자료구조 선언.
    q.front = 0;
    q.rear = 0;
    if (!isExternal(v))
        enqueue(&q, v);
    while (q.front != q.rear) // 큐가 완전히 빌 때 까지
    {
        v = dequeue(&q);
        printf(" %d", v->data);
        if (v->left->data != 0) // v 의 왼쪽 자식노드가 외부노드가 아니라면 삽입
            enqueue(&q, v->left);
        if (v->right->data != 0) // v의 오른쪽 자식노드가 외부노드가 아니라면 삽입
            enqueue(&q, v->right);
    }
}

void freeTree(Node *v) // 트리 자료구조 할당 해제
{
    if (v != NULL)
    {
        freeTree(v->left);
        freeTree(v->right);
        free(v);
    }
}

int main()
{
    Node *head = NULL;
    Node *Last = NULL;
    char command;
    int key;

    while (1)
    {
        scanf("%c", &command);
        getchar();
        if (command == 'q')
            break;
        // switch 문을 통한 명령 구분
        switch (command)
        {
        case 'i':
            scanf("%d", &key);
            getchar();
            insertItem(&head, &Last, key);
            printf("0\n");
            break;
        case 'd':
            removeMax(&Last);
            break;
        case 'p':
            printHeap(head);
            printf("\n");
            break;
        default:
            break;
        }
    }
    freeTree(head);
    return 0;
}