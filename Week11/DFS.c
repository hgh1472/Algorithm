#include <stdio.h>
#include <stdlib.h>

#define NOT_EXIST 0
#define VISITED 1
#define FRESH 0

typedef struct incidenceList {
    struct incidenceList *next;
    int edgeIndex;
} IncidenceList;

typedef struct vertex {
    int data;
    int isVisited;
    struct incidenceList *incidence;
} Vertex;

typedef struct edge {
    int weight;
    int start;
    int end;
} Edge;

typedef struct graph {
    struct vertex *vertices;
    struct edge *edges;
} Graph;

// Edge의 양 끝점을 구분하기 쉽게 start, end를 오름차순으로 정렬
void sortAscending(int *a, int *b) {
    int tmp;
    if (*a > *b) {
        tmp = *a;
        *a = *b;
        *b = tmp;
    }
}

IncidenceList *makeIncidenceList() {
    IncidenceList *new = (IncidenceList *)malloc(sizeof(IncidenceList));
    new->next = NULL;
    return new;
}

Graph *createGraph(int vertices, int edges) {
    Graph *g = (Graph *)malloc(sizeof(Graph));
    g->vertices = (Vertex *)malloc(sizeof(Vertex) * (vertices + 1));  // 인덱스와 data값을 일치시키기 위해 +1을 한다.
    g->edges = (Edge *)malloc(sizeof(Edge) * (edges));
    for (int i = 1; i <= vertices; i++) {
        g->vertices[i].data = i;
        g->vertices[i].incidence = makeIncidenceList();
        g->vertices[i].isVisited = FRESH;
    }
    return g;
}

// 탐색을 초기화할 때 사용한다. 이 문제에서는 사용 X
void setGraphFresh(Graph *g, int countOfVertices) {
    for (int i = 1; i <= countOfVertices; i++) g->vertices[i].isVisited = FRESH;
}

// Graph g의 Edge배열에 생성된 Edge가 들어갈 자리를 찾는다.
int findInsertIndex(Graph *g) {
    int i = 0;
    while (g->edges[i].start != 0) {
        i++;
    }
    return i;
}

// Edge의 한 부분의 vertex가 주어졌을 때 반대편 vertex를 반환하는 함수
int getOppositeVertex(Edge edge, int vertex) {
    if (edge.start == vertex) return edge.end;
    return edge.start;
}

/*
fixedVertex는 하나의 IncidenceList를 삽입할 때, 시작점의 Vertex를 말한다.
insertedVertex는 하나의 IncidenceList를 삽입할 때, 시작점의 Vertex의 관점에서 연결되어 있는 Vertex 말한다.
*/
void insertIncidenceList(Graph *g, int fixedVertex, int insertedVertex, int index) {
    IncidenceList *vertexIncidence = makeIncidenceList();
    IncidenceList *temp = g->vertices[fixedVertex].incidence;

    vertexIncidence->edgeIndex = index;
    // 오름차순으로 삽입
    while (temp->next != NULL) {
        if (insertedVertex < getOppositeVertex(g->edges[temp->next->edgeIndex], fixedVertex)) break;
        temp = temp->next;
    }
    vertexIncidence->next = temp->next;
    temp->next = vertexIncidence;
}

void insertEdge(Graph *g, int first, int second, int weight) {
    sortAscending(&first, &second);  // Edge를 구분하기 쉽게 시작점과 끝점을 오름차순으로 정렬
    int index = findInsertIndex(g);
    g->edges[index].start = first;
    g->edges[index].end = second;
    g->edges[index].weight = weight;

    // 한 Edge의 두 정점에 Incidence를 삽입한다.
    insertIncidenceList(g, first, second, index);
    insertIncidenceList(g, second, first, index);
}

void DFS(int vertexNumber, Graph *g) {
    g->vertices[vertexNumber].isVisited = VISITED;
    printf("%d\n", g->vertices[vertexNumber].data);
    IncidenceList *temp = g->vertices[vertexNumber].incidence;
    while (temp->next != NULL) {
        temp = temp->next;
        int oppositeVertex = getOppositeVertex(g->edges[temp->edgeIndex], vertexNumber);
        if (g->vertices[oppositeVertex].isVisited == FRESH) DFS(oppositeVertex, g);
    }
}

int main() {
    int countOfVertices, countOfEdges, startVertex;
    int firstVertexOfEdge, secondVertexOfEdge;
    Graph *g;

    scanf("%d %d %d", &countOfVertices, &countOfEdges, &startVertex);
    g = createGraph(countOfVertices, countOfEdges);

    for (int i = 0; i < countOfEdges; i++) {
        scanf("%d %d", &firstVertexOfEdge, &secondVertexOfEdge);
        insertEdge(g, firstVertexOfEdge, secondVertexOfEdge, 1);
    }
    DFS(startVertex, g);
    return 0;
}

/*
    IncidenceList *temp;
        for (int i = 1; i <= countOfVertices; i++) {
            printf("vertex : %d ->", i);
            temp = g->vertices[i].incidence;
            while (temp->next != NULL) {
                temp = temp->next;
                printf("%d, ",getOppositeVertex(g->edges[temp->edgeIndex], i));
            }
            printf("\n");
        }

◦ 인접 정점의 조사 순서
- 정점 u의 인접 정점(or 부착 간선)들을 번호가 작은 정점부터 조사한다. (즉, 아래 DFS 의사 코드의 for 문(☚)에서 인접 정점들을 번호가 작은 정점부터 큰
순서대로 조사하라. 조사 순서에 따라 방문 결과가 달라질 수 있음에 유의할 것)
DFS(u) {
    u 방문;
    for (u의 인접 정점들 w에 대해서) {
        if (w를 아직 방문하지 않았으면)
            DFS(w);
    }
}

8 12 7 ↦ n = 8, m = 12, s = 7
1 2
2 4
4 7
3 6
6 1
7 6
7 8
1 3
2 7
1 4
2 5
7 5

7
2
1
3
6
4
5
8
*/