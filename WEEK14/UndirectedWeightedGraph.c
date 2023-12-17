#include <stdio.h>
#include <stdlib.h>
#define INFINITY 2147480000
#define SWAP(x, y, tmp) ((tmp) = (x), (x) = (y), (y) = (tmp))
#define TRUE 1
#define FALSE 0

typedef struct vertex {
    int vertexNumber;
    struct incident *IncidentLists;
    struct vertex *next;
} Vertex;

typedef struct edge {
    struct vertex *firstVertex;
    struct vertex *secondVertex;
    int weight;
    struct edge *next;
} Edge;

typedef struct incident {
    struct edge *Edge;
    struct incident *next;
} Incident;

typedef struct graph {
    struct vertex *vertices;
    struct edge *edges;
    int countOfVertices;
    int countOfEdges;
} Graph;

typedef struct heapNode {
    int vertexNumber;
    int distance;
} HeapNode;

typedef struct heap {
    HeapNode **heap;
    int index;
} Heap;

Vertex *getVertex() {
    Vertex *vertex = (Vertex *)malloc(sizeof(Vertex));
    vertex->next = NULL;
    return vertex;
}

Edge *getEdge() {
    Edge *edge = (Edge *)malloc(sizeof(Edge));
    edge->firstVertex = NULL;
    edge->secondVertex = NULL;
    edge->weight = 0;
    edge->next = NULL;
    return edge;
}

Incident *getIncident() {
    Incident *incident = (Incident *)malloc(sizeof(Incident));
    incident->next = NULL;
    incident->Edge = NULL;
    return incident;
}

HeapNode *getHeapNode() {
    HeapNode *heapNode = (HeapNode *)malloc(sizeof(HeapNode));
    heapNode->distance = INFINITY;
    return heapNode;
}

Heap *getHeap(int countOfVertices) {
    Heap *h = (Heap *)malloc(sizeof(Heap));
    h->heap = (HeapNode **)malloc(sizeof(HeapNode *) * (countOfVertices + 1));

    for (int i = 1; i <= countOfVertices; i++) {
        h->heap[i] = getHeapNode();
        h->heap[i]->vertexNumber = i;
    }
    h->index = 0;
    return h;
}

Graph *setGraph(int countOfVertices, int countOfEdges) {
    Graph *g = (Graph *)malloc(sizeof(Graph));
    g->countOfVertices = countOfVertices;
    g->countOfEdges = countOfEdges;
    g->vertices = getVertex();
    g->edges = getEdge();

    Vertex *tempVertex = g->vertices;
    Edge *tempEdge = g->edges;
    for (int i = 1; i <= countOfVertices; i++) {
        tempVertex->next = getVertex();
        tempVertex = tempVertex->next;
        tempVertex->IncidentLists = getIncident();
        tempVertex->vertexNumber = i;
    }

    for (int i = 0; i < countOfEdges; i++) {
        tempEdge->next = getEdge();
        tempEdge = tempEdge->next;
    }
    return g;
}

Vertex *getVertexPointer(Graph *g, int vertexNumber) {
    Vertex *tempVertex = g->vertices;
    while (tempVertex->next != NULL) {
        tempVertex = tempVertex->next;
        if (tempVertex->vertexNumber == vertexNumber) return tempVertex;
    }
    return NULL;
}

Vertex *getOppositeVertex(Edge *edge, Vertex *vertex) {
    if (edge->firstVertex == vertex) return edge->secondVertex;
    return edge->firstVertex;
}

void insertUndirectedEdge(Graph *g, int firstVertex, int secondVertex, int weight, int index) {
    Edge *tempEdge = g->edges;
    Vertex *first = getVertexPointer(g, firstVertex);
    Vertex *second = getVertexPointer(g, secondVertex);

    for (int i = 0; i < index; i++) tempEdge = tempEdge->next;
    tempEdge->firstVertex = first;
    tempEdge->secondVertex = second;
    tempEdge->weight = weight;

    Incident *tempIncident = first->IncidentLists;
    while (tempIncident->next != NULL) tempIncident = tempIncident->next;
    tempIncident->next = getIncident();
    tempIncident = tempIncident->next;
    tempIncident->Edge = tempEdge;

    tempIncident = second->IncidentLists;
    while (tempIncident->next != NULL) tempIncident = tempIncident->next;
    tempIncident->next = getIncident();
    tempIncident = tempIncident->next;
    tempIncident->Edge = tempEdge;
}

Graph *buildGraph(int countOfVertices, int countOfEdges) {
    int firstVertex, secondVertex, weight;
    Graph *g = setGraph(countOfVertices, countOfEdges);

    for (int i = 1; i <= countOfEdges; i++) {
        scanf("%d %d %d", &firstVertex, &secondVertex, &weight);
        insertUndirectedEdge(g, firstVertex, secondVertex, weight, i);
    }
    return g;
}

void upHeap(Heap *h, int index) {
    HeapNode *tmp;

    if (index == 1 || h->heap[index / 2]->distance <= h->heap[index]->distance) return;
    SWAP(h->heap[index], h->heap[index / 2], tmp);
    upHeap(h, index / 2);
}

void downHeap(Heap *h, int index) {
    if (index * 2 > h->index) return;
    int smaller = index * 2;
    HeapNode *tmp;
    if (h->index >= index * 2 + 1 && h->heap[smaller]->distance > h->heap[index * 2 + 1]->distance) smaller = index * 2 + 1;
    if (h->heap[index]->distance < h->heap[smaller]->distance) return;
    SWAP(h->heap[index], h->heap[smaller], tmp);
    return downHeap(h, smaller);
}

void replaceKey(Heap *h, int vertex, int distance) {
    int index = 1;
    while (index <= h->index) {
        if (h->heap[index]->vertexNumber == vertex) break;
        index++;
    }
    h->heap[index]->distance = distance;
    upHeap(h, index);
}

int isEmpty(Heap *h) { return h->index == 0; }

Vertex *removeMin(Graph *g, Heap *h) {
    HeapNode *temp;
    int min = h->heap[1]->vertexNumber;
    SWAP(h->heap[1], h->heap[h->index], temp);
    h->index = h->index - 1;
    downHeap(h, 1);
    free(h->heap[h->index + 1]);
    return getVertexPointer(g, min);
}

void insertKey(Heap *h, int vertexNumber, int distance) {
    h->index++;
    h->heap[h->index]->vertexNumber = vertexNumber;
    h->heap[h->index]->distance = distance;
    upHeap(h, h->index);
}

int isInHeap(Heap *h, Vertex *vertex) {
    int vertexNumber = vertex->vertexNumber;
    int index = 1;
    for (int i = 1; i <= h->index; i++) {
        if (h->heap[i]->vertexNumber == vertexNumber) return TRUE;
    }
    return FALSE;
}

int **getDistance(int countOfVertices) {
    int **distance = (int **)malloc(sizeof(int *) * (countOfVertices + 1));
    for (int i = 1; i <= countOfVertices; i++) {
        distance[i] = (int *)malloc(sizeof(int) * (countOfVertices + 1));
        for (int j = 1; j <= countOfVertices; j++) distance[i][j] = INFINITY;
    }
    return distance;
}

void freeDistance(int **distance, int index) {
    for (int i = 0; i < index; i++) free(distance[i]);
    free(distance);
}

void freeHeap(Heap *h) { free(h); }

void freeIncidentList(Incident *incident) {
    if (incident->next != NULL) freeIncidentList(incident->next);
    free(incident);
}

void freeVertices(Vertex *vertex) {
    if (vertex->next != NULL) freeVertices(vertex->next);

    if (vertex->IncidentLists != NULL) freeIncidentList(vertex->IncidentLists);
    free(vertex);
}

void freeEdges(Edge *edge) {
    if (edge->next != NULL) freeEdges(edge->next);
    free(edge);
}

void freeGraph(Graph *g) {
    freeVertices(g->vertices);
    freeEdges(g->edges);
}

void applyDijkstraShortestPaths(Graph *g, int startVertex) {
    int **distance;
    Heap *h;
    Incident *tempIncident;
    Vertex *vertex, *tempVertex;

    distance = getDistance(g->countOfVertices);
    distance[startVertex][startVertex] = 0;
    h = getHeap(g->countOfVertices);
    for (int i = 1; i <= g->countOfVertices; i++) insertKey(h, i, INFINITY);
    replaceKey(h, startVertex, 0);
    while (!isEmpty(h)) {
        vertex = removeMin(g, h);
        tempIncident = vertex->IncidentLists;
        while (tempIncident->next != NULL) {
            tempIncident = tempIncident->next;
            tempVertex = getOppositeVertex(tempIncident->Edge, vertex);
            if (isInHeap(h, tempVertex)) {
                if (distance[startVertex][vertex->vertexNumber] + tempIncident->Edge->weight < distance[startVertex][tempVertex->vertexNumber]) {
                    distance[startVertex][tempVertex->vertexNumber] = distance[startVertex][vertex->vertexNumber] + tempIncident->Edge->weight;
                    replaceKey(h, tempVertex->vertexNumber, distance[startVertex][tempVertex->vertexNumber]);
                }
            }
        }
    }
    for (int i = 1; i <= g->countOfVertices; i++) {
        if (distance[startVertex][i] != INFINITY && i != startVertex) printf("%d %d\n", i, distance[startVertex][i]);
    }

    freeHeap(h);
    freeGraph(g);
}

int main() {
    int countOfVertices, countOfEdges, startVertex;

    scanf("%d %d %d", &countOfVertices, &countOfEdges, &startVertex);

    Graph *g = buildGraph(countOfVertices, countOfEdges);

    applyDijkstraShortestPaths(g, startVertex);
}