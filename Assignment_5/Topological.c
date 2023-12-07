#include <stdio.h>
#include <stdlib.h>

#define NOT_VISITED 0
#define VISITED 1

typedef struct incidenceList {
    struct incidenceList *next;
    struct edge *edge;
} IncidenceList;

typedef struct vertex {
    int vertexNumber;
    int isVisited;
    struct incidenceList *outEdges;
    struct incidenceList *inEdges;
    struct vertex *next;
} Vertex;

typedef struct edge {
    struct vertex *origin;
    struct vertex *destination;
    struct edge *next;
} Edge;

typedef struct graph {
    struct vertex *vertices;
    struct edge *edges;
    int countOfVertices;
    int countOfEdges;
} Graph;

typedef struct stack {
    // 스택은 vertex 포인터 배열을 가진다.
    Vertex **stack;
    int top;
} Stack;

IncidenceList *getIncidenceList() {
    IncidenceList *new = (IncidenceList *)malloc(sizeof(IncidenceList));
    new->edge = NULL;
    new->next = NULL;
    return new;
}

Vertex *getVertex() {
    Vertex *new = (Vertex *)malloc(sizeof(Vertex));

    new->next = NULL;
    // 생성된 vertex의 inEdges와 outEdges는 헤드 노드를 가진다.
    new->inEdges = getIncidenceList();
    new->outEdges = getIncidenceList();
    new->isVisited = NOT_VISITED;
    return new;
}

Edge *getEdge() {
    Edge *new = (Edge *)malloc(sizeof(Edge));
    new->destination = NULL;
    new->origin = NULL;
    new->next = NULL;
    return new;
}

// vertexNumber가 주어졌을 때, 그래프의 해당 vertex의 포인터를 반환한다.
Vertex *getVertexPointer(Graph *g, int vertex) {
    Vertex *tempVertex = g->vertices;
    while (tempVertex->next != NULL) {
        tempVertex = tempVertex->next;
        if (tempVertex->vertexNumber == vertex) return tempVertex;
    }
    return NULL;
}

// 한 Edge와 Edge의 한 부분의 Vertex가 주어졌을 때, 반대편 Vertex를 반환한다.
Vertex *getOppositeVertex(Edge *edge, Vertex *vertex) {
    if (edge->origin == vertex) return edge->destination;
    return edge->origin;
}

void freeIncidenceList(IncidenceList *incidenceList) {
    if (incidenceList->next != NULL) freeIncidenceList(incidenceList->next);
    free(incidenceList);
}

void freeVertices(Vertex *vertex) {
    if (vertex->next != NULL) freeVertices(vertex->next);
    freeIncidenceList(vertex->inEdges);
    freeIncidenceList(vertex->outEdges);
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

void freeStack(Stack *s) {
    free(s->stack);
    free(s);
}

int isEmptyEdge(Edge *edge) { return edge->origin == NULL; }

int isEmptyStack(Stack *s) { return s->top == -1; }

int isVisitedVertex(Vertex *vertex) { return vertex->isVisited == VISITED; }

// 스택의 top에 있는 값을 반환한다.
Vertex *getTopVertex(Stack *s) { return s->stack[s->top]; }

Stack *getStack(int countOfVertices) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->stack = (Vertex **)malloc(sizeof(Vertex *) * countOfVertices);
    s->top = -1;
    return s;
}

void push(Stack *s, Vertex *vertex) {
    s->top = s->top + 1;
    s->stack[s->top] = vertex;
}

Vertex *pop(Stack *s) {
    Vertex *temp = s->stack[s->top];
    s->top = s->top - 1;
    return temp;
}

Graph *setGraph() {
    int countOfVertices, countOfEdges;

    scanf("%d %d", &countOfVertices, &countOfEdges);

    Graph *new = (Graph *)malloc(sizeof(Graph));
    // 그래프의 첫 vertex, edge는 헤드이다. (실제 vertex가 아닌 헤드노드의 역할)
    new->vertices = getVertex();
    new->edges = getEdge();
    new->countOfVertices = countOfVertices;
    new->countOfEdges = countOfEdges;

    Vertex *tempVertex = new->vertices;
    for (int i = 1; i <= countOfVertices; i++) {
        // vertex를 countOfVertices만큼 생성한다.
        tempVertex->next = getVertex();
        tempVertex = tempVertex->next;
        tempVertex->vertexNumber = i;
    }
    Edge *tempEdge = new->edges;
    for (int i = 0; i < countOfEdges; i++) {
        // edge를 countOfEdges만큼 생선한다.
        tempEdge->next = getEdge();
        tempEdge = tempEdge->next;
    }
    return new;
}

void insertDirectedEdge(Graph *g, int origin, int destination) {
    Edge *tempEdge = g->edges->next;
    // 비어있는 공간을 찾은 후, 해당 공간에 Edge에 대한 정보를 주입한다.
    while (!isEmptyEdge(tempEdge)) tempEdge = tempEdge->next;
    Vertex *originVertex = getVertexPointer(g, origin);
    Vertex *destinationVertex = getVertexPointer(g, destination);
    tempEdge->origin = originVertex;
    tempEdge->destination = destinationVertex;

    // origin의 outEdges에 반영한다.
    IncidenceList *tempIncidenceList = originVertex->outEdges;
    while (tempIncidenceList->next != NULL) tempIncidenceList = tempIncidenceList->next;
    tempIncidenceList->next = getIncidenceList();
    tempIncidenceList = tempIncidenceList->next;
    tempIncidenceList->edge = tempEdge;

    // destination의 inEdges에 반영한다.
    tempIncidenceList = destinationVertex->inEdges;
    while (tempIncidenceList->next != NULL) tempIncidenceList = tempIncidenceList->next;
    tempIncidenceList->next = getIncidenceList();
    tempIncidenceList = tempIncidenceList->next;
    tempIncidenceList->edge = tempEdge;
}

Graph *buildGraph() {
    int origin, destination;

    // 정점의 개수와 간선의 개수에 맞춰 그래프 생성.
    Graph *g = setGraph();

    for (int i = 0; i < g->countOfEdges; i++) {
        scanf("%d %d", &origin, &destination);
        insertDirectedEdge(g, origin, destination);
    }
    return g;
}

void topologicalSortDFS(Stack *s, Vertex *vertex) {
    IncidenceList *tempIncidenceList;
    Vertex *oppositeVertex;

    /*
    방문되지 않은 vertex라면 해당 vertex를 대상으로 DFS를 수행한다.
    호출은 Stack을 통해 진행.
    진출하는 간선이 없으면 출력한다.
    -> 위상순서의 역순으로 출력된다.
    비싸이클 그래프이므로 방문 여부만 확인한다.
    */
    if (!isVisitedVertex(vertex)) {
        push(s, vertex);
        vertex->isVisited = VISITED;
        while (!isEmptyStack(s)) {
            // topVertex를 대상으로 DFS를 수행한다.
            vertex = getTopVertex(s);
            tempIncidenceList = vertex->outEdges;
            while (tempIncidenceList->next != NULL) {
                tempIncidenceList = tempIncidenceList->next;
                oppositeVertex = getOppositeVertex(tempIncidenceList->edge, vertex);
                /*
                vertex와 연결된 노드 중에 방문하지 않은 노드가 있다면,
                해당 노드를 Stack에 삽입 후, 해당 노드의 outEdges를 탐색한다.
                */
                if (!isVisitedVertex(oppositeVertex)) {
                    push(s, oppositeVertex);
                    // oppositeVertex에 대해서 outEdges를 탐색하기 위해 vertex를 oppositeVertex로 초기화.
                    vertex = oppositeVertex;
                    vertex->isVisited = VISITED;
                    // vertex의 outEdges를 살피기 위해 초기화.
                    tempIncidenceList = vertex->outEdges;
                }
            }
            /*
            만약 outEdges가 없다면, 끝점에 도달한 것 이므로 출력한다.
            Stack에 값이 남아있다면 이 과정이 반복된다.
            Stack에 들어있는 값은 재귀 호출로 구현되었을 때, 쌓여있는 시스템 스택과 같다.
            즉, pop은 하나의 시스템 스택의 종료를 뜻한다.
            */
            vertex = pop(s);
            printf("%d\n", vertex->vertexNumber);
        }
    }
}

void topologicalSort(Graph *g) {
    Vertex *tempVertex = g->vertices;

    // 스택을 생성한다.
    Stack *s = getStack(g->countOfVertices);

    while (tempVertex->next != NULL) {  // 모든 vertex에 대해 topologicalSortDFS를 수행한다.
        tempVertex = tempVertex->next;
        if (tempVertex->isVisited == NOT_VISITED) {
            topologicalSortDFS(s, tempVertex);
        }
    }
    freeStack(s);
}

int main() {
    // 정점의 개수와 간선의 개수를 입력받은 후, 간선을 삽입한다.
    Graph *g = buildGraph();

    topologicalSort(g);

    freeGraph(g);
	system("leaks a.out");
    return 0;
}
