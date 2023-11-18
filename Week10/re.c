#include <stdio.h>
#include <stdlib.h>

typedef struct incidenceList {
    int endPoint;
    int weight;
    struct incidenceList *next;
} IncidenceList;

typedef struct vertex {
    struct incidenceList *edges;
} Vertex;

typedef struct graph {
    struct vertex vertices[10];
} Graph;

IncidenceList *getIncidenceList() {
    IncidenceList *new = (IncidenceList *)malloc(sizeof(IncidenceList));
    new->next = NULL;
    return new;
}
Graph initGraph() {
    Graph g;
    for (int i = 0; i < 10; i++) {
        g.vertices[i].edges = getIncidenceList();
    }
    return g;
}

void printGraph(Graph g, int nodeNumber) {
    Vertex target = g.vertices[nodeNumber];
    IncidenceList *temp = target.edges;
    while (temp->next != NULL) {
        temp = temp->next;
        if (temp->weight != 0) printf(" %d %d", temp->endPoint, temp->weight);
    }
    printf("\n");
}

Graph modifyWeight(Graph *g, int startPoint, int endPoint, int newWeight) {
    Vertex target = g->vertices[startPoint];
    IncidenceList *temp = target.edges;
    while (temp->next != NULL) {
        temp = temp->next;
        if (temp->endPoint == endPoint) {
            temp->weight = newWeight;
            return *g;
        }
    }
    temp->next = getIncidenceList();
    temp->endPoint = endPoint;
    temp->weight = newWeight;
    return *g;
}

Graph setGraph(Graph *g) {
    modifyWeight(g, 1, 2, 1);
    modifyWeight(g, 2, 1, 1);

    modifyWeight(g, 1, 3, 1);
    modifyWeight(g, 3, 1, 1);

    modifyWeight(g, 1, 4, 1);
    modifyWeight(g, 4, 1, 1);
    IncidenceList *temp = g->vertices[4].edges;
    temp =

        modifyWeight(g, 1, 6, 2);
    modifyWeight(g, 6, 1, 2);

    modifyWeight(g, 2, 3, 1);
    modifyWeight(g, 3, 2, 1);

    modifyWeight(g, 3, 5, 4);
    modifyWeight(g, 5, 3, 4);

    modifyWeight(g, 5, 5, 4);

    modifyWeight(g, 5, 6, 3);
    modifyWeight(g, 6, 5, 3);
    return *g;
}
int main() {
    Graph g = initGraph();
    char command;
    int nodeNumber, firstEndPoint, secondEndPoint, newWeight;

    g = setGraph(&g);
    while (1) {
        scanf("%c", &command);
        if (command == 'q') break;
        switch (command) {
            case 'a':
                scanf("%d", &nodeNumber);
                printGraph(g, nodeNumber);
                break;
            case 'm':
                scanf("%d %d %d", &firstEndPoint, &secondEndPoint, &newWeight);
                g = modifyWeight(&g, firstEndPoint, secondEndPoint, newWeight);
                g = modifyWeight(&g, secondEndPoint, firstEndPoint, newWeight);
            default:
                break;
        }
    }
    return 0;
}