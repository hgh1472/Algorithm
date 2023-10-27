#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    struct node *parent;
    struct node *left;
    struct node *right;
} Node;

int findElement(int k);
void insertItem(int key, Node *head);
Node *treeSearch(Node *v, int k);
void removeElement(Node **head, int k);
int isExternal(Node *w);
int isInternal(Node *w);
Node *inOrderSucc(Node *w);
void expandExternal(Node *w);
Node *getNode(int key);
Node *reduceExternal(Node *z, Node **root);

Node *getNode(int key) {
    Node *new = (Node *)malloc(sizeof(Node));
    new->key = key;
    new->parent = NULL;
    new->left = NULL;
    new->right = NULL;
    return new;
}

Node *treeSearch(Node *v, int k) {
    if (isExternal(v)) return v;
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

Node *inOrderSucc(Node *w) {
    w = w->right;
    if (isExternal(w)) return NULL;
    while (isInternal(w->left)) w = w->left;
    return w;
}

void removeElement(Node **head, int k) {
    Node *w = treeSearch(*head, k);
    if (isExternal(w)) {
        printf("X\n");
        return;
    }
    int e = w->key;
    Node *z = w->left;
    if (!isExternal(z)) z = w->right;
    if (isExternal(z))
        reduceExternal(z, head);
    else {
        Node *y = inOrderSucc(w);
        z = y->left;
        w->key = y->key;
        reduceExternal(z, head);
    }
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
    Node *w = z->parent;
    Node *zs = sibling(z);
    if (w->parent == NULL) {
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
    Node *l = getNode(0);  // 빈 노드는 데이터를 0으로 설정
    Node *r = getNode(0);  // 빈 노드는 데이터를 0으로 설정

    // 각각의 자식노드와 부모노드를 연결해준다.
    l->parent = z;
    r->parent = z;
    z->left = l;
    z->right = r;
}

void insertItem(int k, Node *head) {
    Node *w = treeSearch(head, k);
    if (isInternal(w))
        return;
    else {
        w->key = k;
        expandExternal(w);
    }
}

void Seek(Node *head, int k) {
    if (isInternal(treeSearch(head, k)))
        printf("%d\n", k);
    else
        printf("X\n");
}

void printTree(Node *v) {
    if (isExternal(v))
        return;
    else {
        printf(" %d", v->key);
        printTree(v->left);
        printTree(v->right);
    }
}

void freeTree(Node *v) {
    if (v->left != NULL) freeTree(v->left);
    if (v->right != NULL) freeTree(v->right);
    free(v);
}
int main() {
    char command;
    int key;
    Node *head = getNode(0);

    while (1) {
        scanf("%c", &command);
        if (command == 'q') break;
        switch (command) {
            case 'i':
                scanf("%d", &key);
                insertItem(key, head);
                break;
            case 'd':
                scanf("%d", &key);
                removeElement(&head, key);
                break;
            case 's':
                scanf("%d", &key);
                Seek(head, key);
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