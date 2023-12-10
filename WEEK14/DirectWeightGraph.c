#include <stdio.h>
#include <stdlib.h>

#define INFINITY 20000

typedef struct vertex {
    int vertexNumber;
    struct vertex *next;
} Vertex;

typedef struct edge {
    struct vertex *org;
    struct vertex *dst;
    struct edge *next;
    int weight;
} Edge;

typedef struct graph {
    struct vertex *vertices;
    struct edge *edges;
    int countOfVertices;
    int countOfEdges;
} Graph;

Vertex *getVertex() {
    Vertex *vertex = (Vertex *)malloc(sizeof(Vertex));
    vertex->next = NULL;
    return vertex;
}

Edge *getEdge() {
    Edge *edge = (Edge *)malloc(sizeof(Edge));
    edge->dst = NULL;
    edge->org = NULL;
    edge->next = NULL;
    return edge;
}

Vertex *getVertexPointer(Graph *g, int vertexNumber) {
    Vertex *tempVertex = g->vertices;
    while (tempVertex->next != NULL) {
        tempVertex = tempVertex->next;
        if (tempVertex->vertexNumber == vertexNumber) return tempVertex;
    }
    return NULL;
}

int *getDistance(int countOfVertices) {
    int *distance = (int *)malloc(sizeof(int) * (countOfVertices + 1));
    for (int i = 1; i <= countOfVertices; i++) distance[i] = INFINITY;
    return distance;
}

Graph *setGraph(int countOfVertices, int countOfEdges) {
    Graph *g = (Graph *)malloc(sizeof(Graph));
    g->vertices = getVertex();
    g->edges = getEdge();
    g->countOfVertices = countOfVertices;
    g->countOfEdges = countOfEdges;

    Vertex *tempVertex = g->vertices;
    for (int i = 1; i <= countOfVertices; i++) {
        tempVertex->next = getVertex();
        tempVertex = tempVertex->next;
        tempVertex->vertexNumber = i;
    }

    Edge *tempEdge = g->edges;
    for (int i = 0; i < countOfEdges; i++) {
        tempEdge->next = getEdge();
        tempEdge = tempEdge->next;
    }

    return g;
}

void insertDirectedEdge(Graph *g, int org, int dst, int weight, int index) {
    Edge *tempEdge = g->edges;
    for (int i = 0; i < index; i++) tempEdge = tempEdge->next;
    tempEdge->org = getVertexPointer(g, org);
    tempEdge->dst = getVertexPointer(g, dst);
    tempEdge->weight = weight;
}

Graph *buildGraph(int countOfVertices, int countOfEdges) {
    int org, dst, weight;
    Graph *g = setGraph(countOfVertices, countOfEdges);

    for (int i = 1; i <= countOfEdges; i++) {
        scanf("%d %d %d", &org, &dst, &weight);
        insertDirectedEdge(g, org, dst, weight, i);
    }
    return g;
}

int getMinimumDistance(int firstDistance, int secondDistance) {
    if (firstDistance < secondDistance) return firstDistance;
    return secondDistance;
}

void applyBellmanFordShortestPaths(Graph *g, int startVertex) {
    Vertex *origin, *destination;
    Edge *tempEdge;
    int *distance;

    distance = getDistance(g->countOfVertices);
    distance[startVertex] = 0;
    for (int i = 1; i < g->countOfVertices; i++) {
        tempEdge = g->edges;
        while (tempEdge->next != NULL) {
            tempEdge = tempEdge->next;
            origin = tempEdge->org;
            destination = tempEdge->dst;
            if (distance[origin->vertexNumber] != INFINITY)
                distance[destination->vertexNumber] = getMinimumDistance(distance[destination->vertexNumber], distance[origin->vertexNumber] + tempEdge->weight);
        }
    }

    for (int i = 1; i <= g->countOfVertices; i++) {
        if (distance[i] < INFINITY && i != startVertex) printf("%d %d\n", i, distance[i]);
    }
    free(distance);
}

void freeVertices(Vertex *vertex) {
    if (vertex->next != NULL) freeVertices(vertex->next);
    free(vertex);
}

void freeEdges(Edge *edge) {
    if (edge->next != NULL) freeEdges(edge->next);
    free(edge);
}

void freeGraph(Graph *g) {
    freeVertices(g->vertices);
    freeEdges(g->edges);
    free(g);
}

int main() {
    int countOfVertices, countOfEdges, startVertex;
    Graph *g;

    scanf("%d %d %d", &countOfVertices, &countOfEdges, &startVertex);

    g = buildGraph(countOfVertices, countOfEdges);

    applyBellmanFordShortestPaths(g, startVertex);

    freeGraph(g);
    return 0;
}