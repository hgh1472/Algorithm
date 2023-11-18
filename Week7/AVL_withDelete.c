#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    int height;
    struct node *parent;
    struct node *left;
    struct node *right;
} Node;

void findElement(Node *head, int k);
void insertItem(int key, Node **head);
Node *treeSearch(Node *v, int k);
void removeElement(Node **head, int k);
int isExternal(Node *w);
int isInternal(Node *w);
Node *inOrderSucc(Node *w);
void expandExternal(Node *w);
Node *getNode();
Node *reduceExternal(Node *z, Node **root);
void searchAndFixAfterInsertion(Node *w, Node **head);
Node *restructure(Node *x, Node *y, Node *z, Node **head);
void searchAndFixAfterRemoval(Node *w, Node **head);

int max(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}

Node *getNode() {
    Node *new = (Node *)malloc(sizeof(Node));
    return new;
}

Node *treeSearch(Node *v, int k) {
    if (isExternal(v)) return v;  // 트리에 k를 key로 가지는 노드가 존재하지 않음.
    /*
    k가 해당 노드의 key값과 같다면 해당 노드를 반환한다.
    k가 탐색하는 노드의 key값보다 작다면 왼쪽 부트리를 탐색.
    반대로 k가 key값보다 크다면 오른쪽 부트리를 탐색.
    */
    if (k == v->key)
        return v;
    else if (k < v->key)
        return treeSearch(v->left, k);
    else
        return treeSearch(v->right, k);
}

int isExternal(Node *w) {
    if (w->left == NULL && w->right == NULL)
        return 1;
    else
        return 0;
}

int isInternal(Node *w) {
    if (w->left != NULL || w->right != NULL)
        return 1;
    else
        return 0;
}

Node *inOrderSucc(Node *w) {  // 중위순회를 했을 때, w노드의 다음 순서 노드를 찾는다.
    w = w->right;
    if (isExternal(w)) return NULL;
    while (isInternal(w->left)) w = w->left;
    return w;
}

void removeElement(Node **head, int k) {
    Node *zs;
    Node *w = treeSearch(*head, k);  // 삭제 key를 저장한 노드를  찾는다.
    if (isExternal(w)) {             // w가 외부노드 = k를 key값으로 가지는 노드가 없다.
        printf("X\n");
        return;
    }
    Node *z = w->left;
    if (!isExternal(z)) z = w->right;
    /*
    자식들 중 외부노드 z가 있다면,
    w를 루트로하는 부트리를 sibling(z)를 루트로하는 부트리로 대체한다.
    */
    if (isExternal(z))
        zs = reduceExternal(z, head);
    else {  // 외부노드가 없다면 중위순회 계승자를 찾는다.
        Node *y = inOrderSucc(w);
        z = y->left;
        w->key = y->key;
        zs = reduceExternal(z, head);
    }
    searchAndFixAfterRemoval(zs->parent, head);  // 제거 후 불균형을 교정한다.
    printf("%d\n", k);
}

Node *sibling(Node *w) {
    if (w->parent == NULL) return NULL;
    if (w->parent->left == w)
        return w->parent->right;
    else
        return w->parent->left;
}

Node *reduceExternal(Node *z, Node **root) {
    Node *w = z->parent;      // w는 삭제되는 노드.
    Node *zs = sibling(z);    // zs는 w의 자리로 올라가게 된다.
    if (w->parent == NULL) {  // w가 루트노드라면, zs가 루트노드가 된다.
        *root = zs;
        zs->parent = NULL;
    } else {
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
void expandExternal(Node *z)  // 노드 확장
{
    Node *l = getNode();
    Node *r = getNode();

    // 각각의 자식노드와 부모노드를 연결해준다.

    l->left = NULL;
    l->right = NULL;
    l->parent = z;
    l->height = 0;

    r->left = NULL;
    r->right = NULL;
    r->parent = z;
    r->height = 0;

    z->left = l;
    z->right = r;
    z->height = 1;
}

Node *restructure(Node *x, Node *y, Node *z, Node **head) {
    Node *a, *b, *c, *T0, *T1, *T2, *T3;
    /*
    x, y, z노드를 중위순회를 했을 때 방문하는 순으로 a, b, c로 지정한다.
    x, y, z의 부트리들 중 x, y, z를 루트로 하는 부트리를 제외한 4개의 부트리 = T0, T1, T2, T3
    4개의 부트리(T0, T1, T2, T3)는 중위순회 방문 순이다.
    */
    if (y == z->left) {      // y가 z의 왼쪽 자식노드 = z가 맨 마지막 순서, 즉 c = z이다.
        if (x == y->left) {  // x가 y의 왼쪽 자식 노드 = x -> y -> z순으로 방문한다.
            a = x;
            b = y;
            c = z;
            T0 = x->left;
            T1 = x->right;
            T2 = y->right;
            T3 = z->right;
        } else {  // x가 y의 오른쪽 자식 노드 = y -> x -> z순으로 방문한다.
            a = y;
            b = x;
            c = z;
            T0 = y->left;
            T1 = x->left;
            T2 = x->right;
            T3 = z->right;
        }
    } else {                 // y가 z의 오른쪽 자식 노드 = z가 첫번째 방문노드, 즉 a = z이다.
        if (x == y->left) {  // x가 y의 왼쪽 자식 노드 = z -> x -> y순으로 방문한다.
            a = z;
            b = x;
            c = y;
            T0 = z->left;
            T1 = x->left;
            T2 = x->right;
            T3 = y->right;
        } else {  // x가 y의 오른쪽 자식 노드 = z -> y -> x순으로 방문한다.
            a = z;
            b = y;
            c = x;
            T0 = z->left;
            T1 = y->left;
            T2 = x->left;
            T3 = x->right;
        }
    }
    // z를 루트로 하는 부트리를 b를 루트로 하는 부트리로 대체한다.
    b->parent = z->parent;
    if (z->parent == NULL)  // z가 루트노드일 경우, head를 b로 바꿔준다.
        *head = b;
    else {
        if (z == z->parent->left)
            z->parent->left = b;
        else
            z->parent->right = b;
    }
    // T0와 T1을 각각 a의 왼쪽 및 오른쪽 부트리로 교정하고 높이를 수정한다.
    a->left = T0;
    T0->parent = a;
    a->right = T1;
    T1->parent = a;
    a->height = max(T0->height, T1->height) + 1;
    // T2와 T3를 각각 c의 왼쪽 및 오른쪽 부트리로 교정하고 높이를 수정한다.
    c->left = T2;
    T2->parent = c;
    c->right = T3;
    T3->parent = c;
    c->height = max(T2->height, T3->height) + 1;
    // a와 c를 각각 v의 왼쪽 및 오른쪽 자식으로 만들고 높이를 수정한다.
    b->left = a;
    a->parent = b;
    b->right = c;
    c->parent = b;
    b->height = max(a->height, c->height) + 1;
    return b;
}

void searchAndFixAfterInsertion(Node *w, Node **head) {
    Node *x, *y, *z;
    while (w != NULL) {  // w에서 루트를 향해 올라간다.
        w->height = max(w->left->height, w->right->height) + 1;
        if (abs(w->left->height - w->right->height) > 1) {  // 불균형인 상황이 있다면,
            // z를 불균형 노드로 지정한다.
            z = w;
            // z의 높은 자식을 y로 지정.
            if (w->left->height > w->right->height)
                y = w->left;
            else
                y = w->right;
            // y의 높은 자식을 x로 지정.
            if (y->left->height > y->right->height)
                x = y->left;
            else
                x = y->right;
            // 불균형 노드를 대상으로 개조 작업을 수행한다.
            w = restructure(x, y, z, head);
            break;
        }
        w = w->parent;
    }
}

void searchAndFixAfterRemoval(Node *w, Node **head) {
    Node *x, *y, *z;
    while (w != NULL) {  // w에서 루트를 향해 올라간다.
        w->height = max(w->left->height, w->right->height) + 1;
        if (abs(w->left->height - w->right->height) > 1) {  // 불균형인 상황이 있다면,
            // z를 불균형 노드로 지정한다.
            z = w;
            // z의 높은 자식노드를 y로 지정한다.
            if (w->left->height > w->right->height)
                y = w->left;
            else
                y = w->right;
            // y의 자식 노드들 중, 어느 한쪽이 높으면 높은 자식을 x로 지정
            if (y->left->height > y->right->height)
                x = y->left;
            else if (y->left->height < y->right->height)
                x = y->right;
            else {  // 높이가 갔다면, y와 같은 방향의 자식 노드가 x 노드가 된다.
                if (y == z->left)
                    x = y->left;
                else
                    x = y->right;
            }
            // 불균형 노드를 대상으로 개조 작업 수행.
            w = restructure(x, y, z, head);
            /*
            삽입과 다르게 1회의 개조만으로 높이 균형을 전역적으로 복구하지 못한다.
            따라서 루트를 향해 올라가면서 모두 검사한다.
            */
        }
        w = w->parent;
    }
}

void insertItem(int k, Node **head) {
    Node *w = treeSearch(*head, k);
    if (isInternal(w))  // 이미 존재한다면 삽입 작업을 하지 않는다.
        return;
    else {
        w->key = k;
        w->height = 1;
        expandExternal(w);
        searchAndFixAfterInsertion(w, head);  // 불균형을 찾아서 수리한다.
    }
}

void findElement(Node *head, int k) {
    Node *w = treeSearch(head, k);
    // w가 내부노드 = 트리안에 k를 key값으로 가지는 노드가 존재.
    if (isInternal(w))
        printf("%d\n", k);
    else
        printf("X\n");
}

void printTree(Node *v) {  // 전위순회로 출력한다.
    if (isExternal(v))
        return;
    else {
        printf(" %d", v->key);
        printTree(v->left);
        printTree(v->right);
    }
}

void freeTree(Node *v) {  // AVL트리를 할당해제 해주는 함수.
    if (v->left != NULL) freeTree(v->left);
    if (v->right != NULL) freeTree(v->right);
    free(v);
}
int main() {
    char command;
    int key;
    Node *head = getNode();
    head->height = 0;
    head->left = NULL;
    head->right = NULL;
    head->parent = NULL;

    while (1) {
        scanf("%c", &command);
        if (command == 'q') break;
        switch (command) {
            case 'i':
                scanf("%d", &key);
                insertItem(key, &head);
                break;
            case 'd':
                scanf("%d", &key);
                removeElement(&head, key);
                break;
            case 's':
                scanf("%d", &key);
                findElement(head, key);
                break;
            case 'p':
                printTree(head);
                printf("\n");
                break;
            default:
                break;
        }
        getchar();
    }
    freeTree(head);
    return 0;
}