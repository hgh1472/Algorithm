#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node
{
    int key;
    struct node *left;
    struct node *right;
} Node;
Node *root;

Node *make(int num)
{
    Node *new = (Node *)malloc(sizeof(Node));
    new->key = num;
    new->left = NULL;
    new->right = NULL;
    return new;
}

Node *find(Node *s, int num)
{
    Node *temp = s;
    if (temp == NULL)
        return NULL;
    if (temp->key == num)
        return temp;
    temp = find(temp->left, num);
    if (temp != NULL)
        return temp;
    return find(s->right, num);
}

void add(int num1, int num2, int num3)
{
    if (root->key == 0)
    {
        root->key = num1;
        if (num2 != 0)
            root->left = make(num2);
        if (num3 != 0)
            root->right = make(num3);
    }
    else
    {
        Node *r = find(root, num1);
        if (num2 != 0)
            r->left = make(num2);
        if (num3 != 0)
            r->right = make(num3);
    }
}

void search(char command[])
{
    Node *temp = root;
    int idx = 0;
    int cnt = strlen(command);
    printf(" %d", root->key);
    for (int i = 0; i < cnt; i++)
    {
        if (command[i] == 'R')
            temp = temp->right;
        else
            temp = temp->left;
        printf(" %d", temp->key);
    }
    printf("\n");
}

void _input(Node *r)
{
    Node *temp = root;
    int num1, num2, num3;
    scanf("%d %d %d", &num1, &num2, &num3);
    if (num2 == 0 && num3 == 0)
        return;
    r->key = num1;
    if (num2 != 0)
    {
        r->left = make(num2);
        _input(r->left);
    }
    if (num3 != 0)
    {
        r->right = make(num3);
        _input(r->right);
    }
}

int main()
{
    int n;
    int s;
    int num1, num2, num3;
    char com[105];

    int cnt = 0;
    root = (Node *)malloc(sizeof(Node));
    root->key = 0;
    root->left = NULL;
    root->right = NULL;
    scanf("%d", &n);
    _input(root);
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%s", com);
        search(com);
    }
    return 0;
}