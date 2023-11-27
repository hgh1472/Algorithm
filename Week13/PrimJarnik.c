#include <stdio.h>
#include <stdlib.h>

#define INQUEUE 0
#define NOTINQUEUE 1
typedef struct adjacencyList {
    struct edge *Edge;
    struct adjacencyList *next;
} AdjacencyList;

typedef struct vertex {
    int vertexNumber;
    struct adjacencyList *edgeList;
    struct vertex *next;
} Vertex;

typedef struct edge {
    struct vertex *firstVertex;
    struct vertex *secondVertex;
    int weight;
    struct edge *next;
} Edge;

typedef struct graph {
    Vertex *vertices;
    Edge *edges;
} Graph;

typedef struct mst {
    int *distance;
} MST;

typedef struct heap {
    int *arr;
    int n;
} Heap;

AdjacencyList *getAdjacencyList() {
    AdjacencyList *new = (AdjacencyList *)malloc(sizeof(AdjacencyList));
    new->Edge = NULL;
    new->next = NULL;
    return new;
}

Vertex *getVertex() {
    Vertex *new = (Vertex *)malloc(sizeof(Vertex));
    new->next = NULL;
    new->edgeList = getAdjacencyList();
    new->vertexNumber = 0;
    return new;
}

Edge *getEdge() {
    Edge *new = (Edge *)malloc(sizeof(Edge));
    new->firstVertex = NULL;
    new->secondVertex = NULL;
    new->weight = 0;
    new->next = NULL;
    return new;
}

Vertex *getVertexpointer(Graph *g, int vertex) {
    Vertex *tempVertex = g->vertices;

    for (int i = 1; i < vertex; i++) tempVertex = tempVertex->next;
    return tempVertex;
}

Graph *initGraph(int countVertex, int countEdge) {
    Graph *g = (Graph *)malloc(sizeof(Graph));
    g->vertices = getVertex();
    g->edges = getEdge();

    Vertex *tempVertex = g->vertices;
    for (int i = 0; i < countVertex; i++) {
        tempVertex->vertexNumber = (i + 1);
        tempVertex->next = getVertex();
        tempVertex = tempVertex->next;
    }

    Edge *tempEdge = g->edges;
    for (int i = 0; i < countEdge; i++) {
        tempEdge->next = getEdge();
        tempEdge = tempEdge->next;
    }
    return g;
}

int getVertexCount(Graph *g) {
    int count = 0;
    Vertex *temp = g->vertices;
    while (temp->next != NULL) {
        temp = temp->next;
        count++;
    }
    return count;
}
void insertEdge(Graph *g, int firstVertex, int secondVertex, int weight) {
    Edge *tempEdge = g->edges;

    while (tempEdge->weight != 0) tempEdge = tempEdge->next;
    tempEdge->firstVertex = getVertexpointer(g, firstVertex);
    tempEdge->secondVertex = getVertexpointer(g, secondVertex);
    tempEdge->weight = weight;

    AdjacencyList *tempAdjacencyList = tempEdge->firstVertex->edgeList;
    while (tempAdjacencyList->next != NULL) tempAdjacencyList = tempAdjacencyList->next;
    tempAdjacencyList->next = getAdjacencyList();
    tempAdjacencyList = tempAdjacencyList->next;
    tempAdjacencyList->Edge = tempEdge;

    tempAdjacencyList = tempEdge->secondVertex->edgeList;
    while (tempAdjacencyList->next != NULL) tempAdjacencyList = tempAdjacencyList->next;
    tempAdjacencyList->next = getAdjacencyList();
    tempAdjacencyList = tempAdjacencyList->next;
    tempAdjacencyList->Edge = tempEdge;
}

void setGraph(Graph *g, int countVertex, int countEdge) {
    int firstVertex, secondVertex, weight;

    for (int i = 0; i < countEdge; i++) {
        scanf("%d %d %d", &firstVertex, &secondVertex, &weight);
        insertEdge(g, firstVertex, secondVertex, weight);
    }
}

int getOppositeVertex(Edge *edge, int vertexNumber) {
    if (edge->firstVertex->vertexNumber == vertexNumber) return edge->secondVertex->vertexNumber;
    return edge->firstVertex->vertexNumber;
}

int findMin(int *distance, int count, int *isQueue) {
    int min = 2147483647;
    int i = 0;
    for (int j = 1; j <= count; j++) {
        if (min > distance[j] && isQueue[j] == INQUEUE) {
            min = distance[j];
            i = j;
        }
    }
    return i;
}

void makeMST(Graph *g, int startVertex) {
    Heap h;
    MST mst;
    Edge *tempEdge;
    AdjacencyList *tempAdjacencyList;
    int count = getVertexCount(g);
    int totalWeight = 0;
    int *isinQueue = (int *)malloc(sizeof(int) * (count + 1));
    int opposite;

    tempAdjacencyList = getVertexpointer(g, 2)->edgeList;
    while (tempAdjacencyList->next != NULL) {
        tempAdjacencyList = tempAdjacencyList->next;
        if (tempAdjacencyList->Edge == NULL) printf("1\n");
    }
    h.arr = (int *)malloc(sizeof(int) * (count + 1));
    mst.distance = (int *)malloc(sizeof(int) * (count + 1));
    for (int i = 0; i <= count; i++) mst.distance[i] = 2147483647;
    mst.distance[startVertex] = 0;
    printf(" %d", startVertex);
    while (count > 1) {
        isinQueue[startVertex] = NOTINQUEUE;
        tempAdjacencyList = getVertexpointer(g, startVertex)->edgeList;
        while (tempAdjacencyList->next != NULL) {
            tempAdjacencyList = tempAdjacencyList->next;
            opposite = getOppositeVertex(tempAdjacencyList->Edge, startVertex);
            if (isinQueue[opposite] == INQUEUE && tempAdjacencyList->Edge->weight < mst.distance[opposite]) {
                mst.distance[opposite] = tempAdjacencyList->Edge->weight;
            }
        }
        startVertex = findMin(mst.distance, getVertexCount(g), isinQueue);
        totalWeight += mst.distance[startVertex];
        printf(" %d", startVertex);
        count--;
    }
    printf("\n%d\n", totalWeight);
}
int main() {
    int countVertex, countEdge, weight;
    int firstVertex, secondVertex;
    Graph *g;

    scanf("%d %d", &countVertex, &countEdge);
    g = initGraph(countVertex, countEdge);

    setGraph(g, countVertex, countEdge);

    makeMST(g, 1);
    return 0;
}