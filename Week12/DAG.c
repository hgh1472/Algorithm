#include <stdio.h>
#include <stdlib.h>

typedef struct incidenceList {
    struct incidenceList *next;
    int edgeIndex;
} IncidenceList;

typedef struct vertex {
    char data;
    int isVisited;
    int inDegree;
    struct incidenceList *outEdges;
    struct incidenceList *inEdges;
} Vertex;

typedef struct edge {
    int weight;
    int origin;
    int destination;
} Edge;

typedef struct graph {
    struct vertex *vertices;
    struct edge *edges;
} Graph;

int q_size;

typedef struct queue {
    int *queue;
    int front;
    int rear;
} Queue;

Graph g;
Queue q;
int countOfVertices;
int countOfEdges;
int topOrder[100];

IncidenceList *makeIncidenceList() {
    IncidenceList *new = (IncidenceList *)malloc(sizeof(IncidenceList));
    new->next = NULL;
    return new;
}

void initializeGraph() {
    g.edges = (Edge *)malloc(sizeof(Edge) * 1000);
    g.vertices = (Vertex *)malloc(sizeof(Vertex) * 100);
}

void insertVertex(char key, int index) {
    g.vertices[index].data = key;
    g.vertices[index].outEdges = makeIncidenceList();
    g.vertices[index].inEdges = makeIncidenceList();
    g.vertices[index].inDegree = 0;
}

int getIndex(char vertexName) {
    for (int i = 0; i < countOfVertices; i++) {
        if (g.vertices[i].data == vertexName) return i;
    }
}

void addFirst(IncidenceList *edge, int i) {
    IncidenceList *new = makeIncidenceList();
    new->edgeIndex = i;
    new->next = edge->next;
    edge->next = new;
}

void insertDirectedEdge(char outVertex, char inVertex, int index) {
    int indexOfOutVertex = getIndex(outVertex);
    int indexOfInVertex = getIndex(inVertex);
    g.edges[index].origin = indexOfOutVertex;
    g.edges[index].destination = indexOfInVertex;
    addFirst(g.vertices[indexOfOutVertex].outEdges, index);
    addFirst(g.vertices[indexOfInVertex].inEdges, index);
    g.vertices[indexOfInVertex].inDegree++;
}

void buildGraph() {
    char key, outVertex, inVertex;

    initializeGraph();
    scanf("%d", &countOfVertices);
    getchar();
    for (int i = 0; i < countOfVertices; i++) {
        scanf("%c", &key);
        getchar();
        insertVertex(key, i);
    }

    scanf("%d", &countOfEdges);
    getchar();
    for (int i = 0; i < countOfEdges; i++) {
        scanf("%c %c", &outVertex, &inVertex);
        getchar();
        insertDirectedEdge(outVertex, inVertex, i);
    }
    for (int i = 0; i < countOfVertices; i++) {
    }
}

void initQueue() {
    q.front = 0;
    q.rear = 0;
    q.queue = (int *)malloc(sizeof(int) * 100);
}

void enqueue(int vertex) {
    q.front = (q.front + 1) % 100;
    q.queue[q.front] = vertex;
}

int isEmpty() { return q.front == q.rear; }

int dequeue() {
    q.rear = (q.rear + 1) % 100;
    int vertex = q.queue[q.rear];
    return vertex;
}

void topologicalSort() {
    int in[100], t, u, w;
    IncidenceList *temp;

    initQueue();
    for (int i = 0; i < countOfVertices; i++) {
        in[i] = g.vertices[i].inDegree;
        if (in[i] == 0) enqueue(i);
    }
    t = 1;
    while (!isEmpty()) {
        u = dequeue();
        topOrder[t++] = u;
        temp = g.vertices[u].outEdges;
        while (temp->next != NULL) {
            temp = temp->next;
            w = g.edges[temp->edgeIndex].destination;
            in[w]--;
            if (in[w] == 0) enqueue(w);
        }
    }
    if (t <= countOfVertices)
        topOrder[0] = 0;
    else
        topOrder[0] = 1;
}

int main() {
    buildGraph();

    topologicalSort();
    if (topOrder[0] == 0)
        printf("0\n");
    else {
        for (int i = 1; i <= countOfVertices; i++) printf("%c ", g.vertices[topOrder[i]].data);
        printf("\n");
    }
    return 0;
}