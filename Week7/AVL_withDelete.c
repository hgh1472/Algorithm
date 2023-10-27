#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    int height;
    struct node *parent;
    struct node *left;
    struct node *right;
} Node;

int findElement(int k);
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

    new->height = 1;
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
    Node *zs;
    Node *w = treeSearch(*head, k);
    if (isExternal(w)) {
        printf("X\n");
        return;
    }
    Node *z = w->left;
    if (!isExternal(z)) z = w->right;
    if (isExternal(z))
        zs = reduceExternal(z, head);
    else {
        Node *y = inOrderSucc(w);
        z = y->left;
        w->key = y->key;
        zs = reduceExternal(z, head);
    }
    searchAndFixAfterRemoval(zs->parent, head);
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
    Node *l = getNode();  // 빈 노드는 데이터를 0으로 설정
    Node *r = getNode();  // 빈 노드는 데이터를 0으로 설정

    // 각각의 자식노드와 부모노드를 연결해준다.
    l->parent = z;
    r->parent = z;
    z->left = l;
    z->right = r;
}

Node *restructure(Node *x, Node *y, Node *z, Node **head) {
    Node *a, *b, *c, *T0, *T1, *T2, *T3;
    if (y == z->left) {
        if (x == y->left) {
            a = x;
            b = y;
            c = z;
            T0 = x->left;
            T1 = x->right;
            T2 = y->right;
            T3 = z->right;
        } else {
            a = y;
            b = x;
            c = z;
            T0 = y->left;
            T1 = x->left;
            T2 = x->right;
            T3 = z->right;
        }
    } else {
        if (x == y->left) {
            a = z;
            b = x;
            c = y;
            T0 = z->left;
            T1 = x->left;
            T2 = x->right;
            T3 = y->right;
        } else {
            a = z;
            b = y;
            c = x;
            T0 = z->left;
            T1 = y->left;
            T2 = x->left;
            T3 = x->right;
        }
    }

    b->parent = z->parent;
    if (z->parent == NULL)
        *head = b;
    else {
        if (z == z->parent->left)
            z->parent->left = b;
        else
            z->parent->right = b;
    }

    a->left = T0;
    T0->parent = a;
    a->right = T1;
    T1->parent = a;
    a->height = max(T0->height, T1->height) + 1;

    c->left = T2;
    T2->parent = c;
    c->right = T3;
    T3->parent = c;
    c->height = max(T2->height, T3->height) + 1;

    b->left = a;
    a->parent = b;
    b->right = c;
    c->parent = b;
    b->height = max(a->height, c->height) + 1;
    return b;
}

void searchAndFixAfterInsertion(Node *w, Node **head) {
    Node *x, *y, *z;
    while (w != NULL) {
        w->height = max(w->left->height, w->right->height) + 1;
        if (abs(w->left->height - w->right->height) > 1) {
            z = w;
            if (w->left->height > w->right->height)
                y = w->left;
            else
                y = w->right;
            // y는 z의 자식노드
            if (y->left->height > y->right->height)
                x = y->left;
            else
                x = y->right;
            // x는 y의 자식노드
            w = restructure(x, y, z, head);
            break;
        }
        w = w->parent;
    }
}

void searchAndFixAfterRemoval(Node *w, Node **head) {
    Node *x, *y, *z;
    while (w != NULL) {
        w->height = max(w->left->height, w->right->height) + 1;
        if (abs(w->left->height - w->right->height) > 1) {
            z = w;
            if (w->left->height > w->right->height)
                y = w->left;
            else
                y = w->right;
            // y는 z의 자식노드

            if (y->left->height > y->right->height)
                x = y->left;
            else if (y->left->height < y->right->height)
                x = y->right;
            else {
                if (y == z->left)
                    x = y->left;
                else
                    x = y->right;
            }
            // x는 y의 자식노드
            w = restructure(x, y, z, head);
        }
        w = w->parent;
    }
}

void insertItem(int k, Node **head) {
    Node *w = treeSearch(*head, k);
    if (isInternal(w))
        return;
    else {
        w->key = k;
        w->height = 1;
        expandExternal(w);
        searchAndFixAfterInsertion(w, head);
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
    Node *head = getNode();

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