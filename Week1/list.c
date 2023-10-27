#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    char data;
    struct node *next;
    struct node *prev;
} Node;

void add(Node *head, int r, char e)
{
    int cnt = 1;
    Node *temp;

    temp = head;
    while (cnt < r && temp->next->next != NULL)
    {
        cnt++;
        temp = temp->next;
    }
    if (cnt != r)
    {
        printf("invalid position\n");
        return;
    }
    else
    {
        Node *new = (Node *)malloc(sizeof(Node));
        new->data = e;
        new->next = temp->next;
        new->prev = temp;
        temp->next->prev = new;
        temp->next = new;
    }
}

void delete(Node *head, int r)
{
    Node *temp;
    temp = head;
    int cnt = 0;
    while (cnt < r && temp->next->next != NULL)
    {
        temp = temp->next;
        cnt++;
    }
    if (cnt != r)
    {
        printf("invalid position\n");
        return;
    }
    temp->next->prev = temp->prev;
    temp->prev->next = temp->next;
    free(temp);
}

char get(Node *head, int r)
{
    Node *temp;
    temp = head;
    int cnt = 0;
    while (cnt < r && temp->next->next != NULL)
    {
        temp = temp->next;
        cnt++;
    }
    if (cnt != r)
    {
        printf("invalid position\n");
        return '\0';
    }
    return temp->data;
}

void print(Node *head)
{
    Node *temp;
    temp = head;
    while (temp->next->next != NULL)
    {
        temp = temp->next;
        printf("%c", temp->data);
    }
    printf("\n");
}

int main()
{
    Node *head = (Node *)malloc(sizeof(Node));
    Node *tail = (Node *)malloc(sizeof(Node));
    head->next = tail;
    head->prev = NULL;
    tail->next = NULL;
    tail->prev = head;
    int n;
    char c;
    int r;
    char e;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        getchar();
        scanf("%c", &c);
        if (c == 'A')
        {
            scanf("%d %c", &r, &e);
            add(head, r, e);
        }
        else if (c == 'D')
        {
            scanf("%d", &r);
            delete (head, r);
        }
        else if (c == 'G')
        {
            scanf("%d", &r);
            e = get(head, r);
            if (e != '\0')
                printf("%c\n", e);
        }
        else if (c == 'P')
            print(head);
    }
    return 0;
}