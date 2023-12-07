#include <stdio.h>
#include <stdlib.h>

#define INQUEUE 0
#define NOTINQUEUE 1

#define NONE_EXIST

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
    int countOfVertices;
    int countOfEdges;
} Graph;

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

Graph *initGraph() {
    scanf("%d %d", &countOfVertices, &countOfEdges);

    Graph *new = (Graph *)malloc(sizeof(Graph));
    new->vertices = getVetex();
    new->Edges = getEdge();
    new->countOfVertices = countOfVertices;
    new->countOfEdges = countOfEdges;

    Vertex *tempVertex = new->vertices;
    for (int i = 1; i <= countOfVertices; i++) {
        tempVertex->next = getVetex();
        tempVertex = tempVertex->next;
        tempVertex->vertexNumber = i;
    }
    Edge *tempEdge = new->Edges;
    for (int i = 0; i < countOfEdges; i++) {
        tempEdge->next = getEdge();
        tempEdge = tempEdge->next;
        tempEdge->weight = NOT_CONNECT;
        tempEdge->firstVertex = NULL;
        tempEdge->secondVertex = NULL;
    }
    return new;
}

int isEmptyEdge(Edge *edge) { return edge->weight == NONE_EXIST; }

void insertEdge(Graph *g, int firstVertex, int secondVertex, int weight) {
    Edge *tempEdge = g->edges;

    while (!isEmptyEdge(tempEdge)) tempEdge = tempEdge->next;
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

void setGraph(Graph *g) {
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

Graph *initMST(Graph *g) {
    Graph *g = (Graph *)malloc(sizeof(Graph));
    g->vertices = getVertex();
    g->edges = getEdge();
    g->countOfVertices = g->countOfVertices;
    g->countOfEdges = g->countOfVertices - 1;

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

void makeMST(Graph *g, int startVertex) {
    Graph *MST;
    Edge *tempEdge;
    AdjacencyList *tempAdjacencyList;
    int count = g->countOfVertices;

    MST = initMST(g);
    int totalWeight = 0;
    int *isinQueue = (int *)malloc(sizeof(int) * (g->countOfVertices + 1));
    int opposite;

    tempAdjacencyList = getVertexpointer(g, 2)->edgeList;
    while (tempAdjacencyList->next != NULL) {
        tempAdjacencyList = tempAdjacencyList->next;
        if (tempAdjacencyList->Edge == NULL) printf("1\n");
    }
    int *distance = (int *)malloc(sizeof(int) * (count + 1));
    for (int i = 0; i <= count; i++) distance[i] = 2147483647;
    distance[startVertex] = 0;
    printf(" %d", startVertex);
    while (count > 1) {
        isinQueue[startVertex] = NOTINQUEUE;
        tempAdjacencyList = getVertexpointer(g, startVertex)->edgeList;
        while (tempAdjacencyList->next != NULL) {
            tempAdjacencyList = tempAdjacencyList->next;
            opposite = getOppositeVertex(tempAdjacencyList->Edge, startVertex);
            if (isinQueue[opposite] == INQUEUE && tempAdjacencyList->Edge->weight < distance[opposite]) {
                distance[opposite] = tempAdjacencyList->Edge->weight;
                insertEdge(MST, tempAdjacencyList->Edge->firstVertex, tempAdjacencyList->Edge->secondVertex, tempAdjacencyList->Edge->weight);
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
    int firstVertex, secondVertex;
    Graph *g;

    g = initGraph();

    setGraph(g);

    makeMST(g, 1);
    return 0;
}