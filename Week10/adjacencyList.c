#include <stdio.h>
#include <stdlib.h>

typedef struct incidenceList {
    struct incidenceList *next;
    struct edge *edge;
} IncidenceList;

typedef struct vertex {
    int data;
    struct incidenceList *incidence;
} Vertex;

typedef struct edge {
    int weight;
    struct vertex *start;
    struct vertex *end;
} Edge;

int calculatePosition(int start, int end) {
    int tmp;

    if (start == 1) return end;
    if (start == 2) return 6 + end;
    if (start == 3) return 11 + end;
    if (start == 4) return 15 + end;
    if (start == 5) return 18 + end;
    if (start == 6) return 21;
}

struct incidenceList *makeIncidenceList() {
    struct incidenceList *new = (struct incidenceList *)malloc(sizeof(struct incidenceList));
    new->next = NULL;
    new->edge = NULL;
    return new;
}

void initGraph(Vertex *vertex, Edge *edge) {
    for (int i = 1; i <= 6; i++) {
        vertex[i].data = i;
        vertex[i].incidence = makeIncidenceList();
    }
    for (int i = 1; i <= 21; i++) {
        if (1 <= i && i <= 6) {
            edge[i].start = vertex[1];
            edge[i].end = vertex[i];
        }
        if (7 <= i && i <= 11) {
            edge[i].start = vertex[2];
            edge[i].end = vertex[i - 6];
        }
        if () }
}

void changeWeight(Vertex *vertex, Edge *edge, int start, int end, int weight) {
    IncidenceList *temp;
    int tmp;
    if (end > start) {
        tmp = end;
        end = start;
        start = end;
    }
    int position = calculatePosition(start, end);
    temp = vertex[start].incidence;
    while (temp->next != NULL) {
        temp = temp->next;
        if (temp->edge->end->data == end) break;
    }
    if (weight == 0) {
        free(temp);
        return;
    }
    if (temp->next == NULL) {
        temp->next = makeIncidenceList();
        temp = temp->next;
        temp->edge = &edge[position];
    }
    temp->edge->weight = weight;
    temp->edge->start = &vertex[start];
    temp->edge->end = &vertex[end];
}

void printEdgeWeight(Edge *edge, int nodeNumber) {
    for (int i = 1; i <= 6; i++) {
        if (edge[i].start->data == nodeNumber) {
            printf(" %d", edge[i].start->data);
            printf(" %d", edge[i].weight);
        }
        if (edge[i].end->data == nodeNumber) {
            printf(" %d", edge[i].end->data);
            printf(" %d", edge[i].weight);
        }
    }
    printf("\n");
}

int main(void) {
    Vertex vertex[6];
    Edge edge[25];
    char command;
    int nodeNumber, start, end, weight;

    changeWeight(vertex, edge, 1, 2, 1);
    changeWeight(vertex, edge, 1, 3, 1);
    changeWeight(vertex, edge, 1, 4, 1);
    changeWeight(vertex, edge, 1, 6, 2);
    changeWeight(vertex, edge, 2, 3, 1);
    changeWeight(vertex, edge, 3, 5, 4);
    changeWeight(vertex, edge, 5, 5, 4);
    changeWeight(vertex, edge, 5, 6, 3);
    while (1) {
        scanf("%c", &command);
        if (command == 'q') break;
        switch (command) {
            case 'a':
                scanf("%d", &nodeNumber);
                printEdgeWeight(edge, nodeNumber);
                break;
            case 'm':
                scanf("%d %d %d", &start, &end, &weight);
                changeWeight(vertex, edge, start, end, weight);
                break;
            default:
                break;
        }
        getchar();
    }
    return 0;
}