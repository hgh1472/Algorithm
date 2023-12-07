#include <stdio.h>
#include <stdlib.h>

#define NOT_CONNECT -1
#define TRUE 1
#define FALSE 0

typedef struct vertex {
    int vertexNumber;
    struct vertex *next;
} Vertex;

typedef struct edge {
    struct vertex *firstVertex;
    struct vertex *secondVertex;
    int weight;
    struct edge *next;
} Edge;

typedef struct graph {
    struct vertex *vertices;
    struct edge *Edges;
    int countOfVertices;
    int countOfEdges;
} Graph;

typedef struct heap {
    int *weightHeap;
    int idx;
} Heap;

typedef struct disjointSet {
    int *root;
    int *rank;
} DisjointSet;

Graph *setGraph();
Vertex *getVertexPointer(Graph *g, int vertexNumber);
void insertEdge(Graph *g, int firstVertex, int secondVertex, int weight);
void upHeap(int *H, int index);
void downHeap(Heap *h, int index);
int removeMin(Heap *h);
Heap *getHeap(int countOfEdges);
void insertAllEdges(Heap *h, Graph *g);
void defineEachVertex(DisjointSet *s, Graph *g);
DisjointSet *getDisjointSet(int countOfVertices);
Graph *setMST(Graph *g);
Edge *findEdgeWithWeight(Graph *g, int weight);
int findSack(DisjointSet *d, int vertex);
int isSameSack(DisjointSet *d, int firstVertex, int secondVertex);
void unionSack(DisjointSet *d, int firstVertex, int secondVertex);
void applyKruskalAlgorithm(Graph *g);
Vertex *getVertex();
Edge *getEdge();

Vertex *getVetex() {
    Vertex *new = (Vertex *)malloc(sizeof(Vertex));
    new->next = NULL;
    return new;
}

Edge *getEdge() {
    Edge *new = (Edge *)malloc(sizeof(Edge));
    new->next = NULL;
    return new;
}

Vertex *getVertexPointer(Graph *g, int vertexNumber) {
    Vertex *tempVertex = g->vertices->next;
    while (tempVertex->vertexNumber != vertexNumber) tempVertex = tempVertex->next;
    return tempVertex;
}

Graph *setGraph() {
    int countOfVertices, countOfEdges;

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

Graph *setMST(Graph *g) {
    Graph *MST = (Graph *)malloc(sizeof(Graph));
    ;
    MST->vertices = getVetex();
    MST->Edges = getEdge();
    MST->countOfVertices = g->countOfVertices;
    MST->countOfEdges = g->countOfVertices - 1;

    Vertex *tempVertex = MST->vertices;
    for (int i = 1; i <= MST->countOfVertices; i++) {
        tempVertex->next = getVetex();
        tempVertex = tempVertex->next;
        tempVertex->vertexNumber = i;
    }
    Edge *tempEdge = MST->Edges;
    for (int i = 0; i < MST->countOfEdges; i++) {
        tempEdge->next = getEdge();
        tempEdge = tempEdge->next;
        tempEdge->weight = NOT_CONNECT;
        tempEdge->firstVertex = NULL;
        tempEdge->secondVertex = NULL;
    }
    return MST;
}

DisjointSet *getDisjointSet(int countOfVertices) {
    DisjointSet *new = (DisjointSet *)malloc(sizeof(DisjointSet));
    new->root = (int *)malloc(sizeof(int) * countOfVertices + 1);
    new->rank = (int *)malloc(sizeof(int) * (countOfVertices + 1));
    for (int i = 1; i <= countOfVertices; i++) new->rank[i] = 1;
    return new;
}

int findSack(DisjointSet *d, int vertex) {
    if (d->root[vertex] == vertex) return vertex;
    return findSack(d, d->root[vertex]);
}

int isSameSack(DisjointSet *d, int firstVertex, int secondVertex) {
    int firstSack = findSack(d, firstVertex);
    int secondSack = findSack(d, secondVertex);

    if (firstSack == secondSack) return TRUE;
    return FALSE;
}

void unionSack(DisjointSet *d, int firstVertex, int secondVertex) {
    int firstSack = findSack(d, firstVertex);
    int secondSack = findSack(d, secondVertex);
    if (firstSack != secondSack) {
        if (d->rank[firstSack] < d->rank[secondSack])
            d->root[firstSack] = secondSack;
        else
            d->root[secondSack] = firstSack;
        if (d->rank[firstSack] == d->rank[secondSack]) {
            d->rank[firstSack]++;
        }
    }
}

Heap *getHeap(int countOfEdges) {
    Heap *new = (Heap *)malloc(sizeof(Heap));
    new->idx = 0;
    new->weightHeap = (int *)malloc(sizeof(int) * (countOfEdges + 1));
    return new;
}

void upHeap(int *H, int index) {
    if (index < 2 || H[index / 2] < H[index]) return;

    int tmp;
    tmp = H[index / 2];
    H[index / 2] = H[index];
    H[index] = tmp;
    upHeap(H, index / 2);
}

void downHeap(Heap *h, int index) {
    if (index * 2 > h->idx) return;

    int smaller = index * 2, tmp;
    if (index * 2 + 1 <= h->idx) {
        if (h->weightHeap[smaller] > h->weightHeap[index * 2 + 1]) smaller = index * 2 + 1;
    }
    if (h->weightHeap[index] < h->weightHeap[smaller]) return;
    tmp = h->weightHeap[index];
    h->weightHeap[index] = h->weightHeap[smaller];
    h->weightHeap[smaller] = tmp;
    downHeap(h, smaller);
}

int removeMin(Heap *h) {
    int min = h->weightHeap[1];
    h->weightHeap[1] = h->weightHeap[(h->idx)--];
    downHeap(h, 1);
    return min;
}

void insertEdges(Graph *g) {
    int firstVertex, secondVertex, weight;

    for (int i = 0; i < g->countOfEdges; i++) {
        scanf("%d %d %d", &firstVertex, &secondVertex, &weight);
        insertEdge(g, firstVertex, secondVertex, weight);
    }
}

void insertEdge(Graph *g, int firstVertex, int secondVertex, int weight) {
    Edge *tempEdge = g->Edges->next;
    while (tempEdge->weight != NOT_CONNECT) tempEdge = tempEdge->next;
    tempEdge->firstVertex = getVertexPointer(g, firstVertex);
    tempEdge->secondVertex = getVertexPointer(g, secondVertex);
    tempEdge->weight = weight;
}

void applyKruskalAlgorithm(Graph *g) {
    Heap *h = getHeap(g->countOfEdges);
    DisjointSet *d = getDisjointSet(g->countOfVertices);
    Graph *MST;
    int firstVertex, secondVertex, weight, totalWeight = 0;
    int countOfEdges = 0;

    defineEachVertex(d, g);
    insertAllEdges(h, g);
    MST = setMST(g);

    Edge *tempEdge;
    while (countOfEdges != g->countOfVertices - 1) {
        tempEdge = findEdgeWithWeight(g, removeMin(h));
        firstVertex = tempEdge->firstVertex->vertexNumber;
        secondVertex = tempEdge->secondVertex->vertexNumber;
        weight = tempEdge->weight;
        if (!isSameSack(d, firstVertex, secondVertex)) {
            insertEdge(MST, firstVertex, secondVertex, weight);
            unionSack(d, firstVertex, secondVertex);
            countOfEdges++;
            printf(" %d", weight);
            totalWeight += weight;
        }
    }
    printf("\n%d\n", totalWeight);
}

void insertAllEdges(Heap *h, Graph *g) {
    Edge *tempEdge = g->Edges;
    while (tempEdge->next != NULL) {
        tempEdge = tempEdge->next;
        h->weightHeap[++(h->idx)] = tempEdge->weight;
        upHeap(h->weightHeap, h->idx);
    }
}

void defineEachVertex(DisjointSet *s, Graph *g) {
    for (int i = 1; i <= g->countOfVertices; i++) s->root[i] = i;
}

Edge *findEdgeWithWeight(Graph *g, int weight) {
    Edge *tempEdge = g->Edges;

    while (tempEdge->next != NULL) {
        tempEdge = tempEdge->next;
        if (tempEdge->weight == weight) return tempEdge;
    }
    return NULL;
}

int main() {
    Graph *g;

    g = setGraph();
    insertEdges(g);
    // showGraph(g);
    applyKruskalAlgorithm(g);
}