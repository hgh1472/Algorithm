#include <stdio.h>
#include <stdlib.h>

#define VISITED 1
#define FRESH 0
#define NOT_CONNECTED 0

// BFS를 위한 Level 구조체이다.
typedef struct level {
    int vertex;
    struct level *next;
}Level;

typedef struct vertex {
    int data;
    int isVisited;
}Vertex;

typedef struct edge {
    int start;
    int end;
    int weight;
}Edge;

typedef struct graph {
    struct vertex *vertices;
    struct edge *edges;
    int **adjacencyMatrix;
}Graph;

void sortAscending(int *a, int *b) {
    int tmp;
    if (*a > *b) {
        tmp = *a;
        *a = *b;
        *b = tmp;
    }
}

Graph *createGraph(int countOfVertices, int countOfEdges) {
    Graph *g = (Graph *)malloc(sizeof(Graph));
    // 인덱스에 바로 접근하기 편리하게 countOfVertices에 + 1 한 값으로 할당한다.
    g->vertices = (Vertex *)malloc(sizeof(Vertex) * (countOfVertices + 1));
    for (int i = 1; i <= countOfVertices; i++)
        g->vertices[i].data = i;
    
    g->edges = (Edge *)malloc(sizeof(Edge) * countOfEdges);

    //2차원 배열인 adhjacencyMatrix 할당.
    g->adjacencyMatrix = (int **)malloc(sizeof(int *) * countOfVertices + 1);
    for (int i = 0; i < countOfVertices + 1; i++)
        g->adjacencyMatrix[i] = (int *)malloc(sizeof(int) * countOfVertices + 1);
    return g;
}

//Graph g의 Edge배열에 생성된 Edge가 들어갈 자리를 찾는다.
int findInsertIndex(Graph *g) {
    int i = 0;
    while (g->edges[i].start != 0) {
        i++;
    }
    // 연결되지 않음을 나타내는 NOT_CONNECTED = 1 이므로, 인덱스는 1 이상으로 한다.
    return i + 1;
}

void insertEdge(Graph *g, int start, int end, int weight) {
    int index = findInsertIndex(g);

    sortAscending(&start, &end); // Edge를 구분하기 쉽게 시작점과 끝점을 오름차순으로 정렬
    g->edges[index].start = start;
    g->edges[index].end = end;
    g->edges[index].weight = weight;

    g->adjacencyMatrix[start][end] = index;
    g->adjacencyMatrix[end][start] = index;
}

Level *getNextVertex(int vertex) {
    Level *next = (Level *)malloc(sizeof(Level));
    next->vertex = vertex;
    next->next = NULL;
    return next;
}

void freeLevel(Level **level, int countOfVertices) {
    for (int i = 0; i < countOfVertices; i++)
        free(level[i]);
    free(level);
}

int isFreshAndConnected(Graph *g, int fixedVertex, int vertex) {
    return g->adjacencyMatrix[fixedVertex][vertex] != NOT_CONNECTED && g->vertices[vertex].isVisited == FRESH;
}

void BFS(int startVertex, int countOfVertices, Graph *g) {
    int i = 0;
    Level *temp;
    Level *nextTemp;
    
    // 모든 Vertex들이 하나씩 연결되어 있다고 가정했을 때, 최대 Vertex수 만큼의 레벨을 가진다.
    Level **level = (Level **)malloc(sizeof(Level *) * countOfVertices);
    level[i] = (Level *)malloc(sizeof(Level));
    level[i]->next = getNextVertex(startVertex);
    g->vertices[startVertex].isVisited = VISITED;
    while (level[i]->next != NULL) { // 다음 레벨이 존재하는 한 계속 탐색한다.
        temp = level[i];
        level[i + 1] = (Level *)malloc(sizeof(Level));
        nextTemp = level[i + 1];
        while (temp->next != NULL) { // 해당 레벨의 존재하는 Vertex만큼 반복
            temp = temp->next;
            printf("%d\n", temp->vertex);
            for (int i = 1; i <= countOfVertices; i++) { // 연결된 Vertex를 찾는다.
                if (isFreshAndConnected(g, temp->vertex, i)) { 
                    nextTemp->next = getNextVertex(i);
                    g->vertices[i].isVisited = VISITED;
                    nextTemp = nextTemp->next;
                }
            }
        }
        i++;
    }
    freeLevel(level, countOfVertices);
}

void freeGraph(Graph *g, int countOfVertices) {
    for (int i = 0; i < countOfVertices + 1; i++)
        free(g->adjacencyMatrix[i]);
    free(g->adjacencyMatrix);
    free(g->edges);
    free(g->vertices);
    free(g);
}

int main() {
    int countOfVertices, countOfEdges, startVertex;
    int firstVertexOfEdge, secondVertexOfEdge;
    Graph *g;

    scanf("%d %d %d", &countOfVertices, &countOfEdges, &startVertex);
    g = createGraph(countOfVertices,countOfEdges);

    for (int i = 0; i < countOfEdges; i++) {
        scanf("%d %d", &firstVertexOfEdge, &secondVertexOfEdge);
        insertEdge(g, firstVertexOfEdge, secondVertexOfEdge, 1);
    }
    BFS(startVertex, countOfVertices, g);
    freeGraph(g, countOfVertices);
    return 0;
}

/*
8 12 4 ↦ n = 8, m = 12, s = 4
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

4
1
2
7
3
6
5
8
    for (int i = 1; i <= countOfVertices; i++) {
        for (int j = 1; j <= countOfVertices; j++)
            printf("%-2d ", g->adjacencyMatrix[i][j]);
        printf("\n");
    }
*/