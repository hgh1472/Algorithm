#include <stdio.h>
#include <stdlib.h>

#define NOT_EXIST 0

typedef struct vertex {
    int data;
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

int hasVertex(int start, int end) {
    if (start < 1)
        return 0;
    if (end > 6)
        return 0;
    return 1;
}

Graph *createGraph() {
    Graph *g = (Graph *)malloc(sizeof(Graph));
    g->vertices = (Vertex *)malloc(sizeof(Vertex) * 7);
    g->edges = (Edge *)malloc(sizeof(Edge)* 22);
    
    //2차원 배열인 adhjacencyMatrix 할당.
    g->adjacencyMatrix = (int **)malloc(sizeof(int *) * 7);
    for (int i = 0; i < 7; i++)
        g->adjacencyMatrix[i] = (int *)malloc(sizeof(int) * 7);
    return g;
}

// start Vertex와 end Vertex에 따른 Edge배열의 몇번째 인덱스에 들어가야하는지 계산한다.
int calculateEdgeIndex(int start, int end) {
    if (start == 1)
        return end;
    if (start == 2)
        return 5 + end;
    if (start == 3)
        return 9 + end;
    if (start == 4)
        return 12 + end;
    if (start == 5)
        return 14 + end;
    return 21;
}

void insertEdge(Graph *g, int start, int end, int weight) {
    sortAscending(&start, &end); // Edge를 구분하기 쉽게 시작점과 끝점을 오름차순으로 정렬
    if (!hasVertex(start, end)) { // 해당 Vertex가 없는 Vertex라면
        printf("-1\n");
        return;
    }
    int index = calculateEdgeIndex(start, end);
    g->edges[index].start = start;
    g->edges[index].end = end;
    g->edges[index].weight = weight;

    // 삭제 조건인 경우 AdjacencyMatrix에 반영.
    if (weight == 0)
        index = 0;

    g->adjacencyMatrix[start][end] = index;
    g->adjacencyMatrix[end][start] = index;
}

void printEdge(Graph *g, int number) {
    int index;

    if (number >= 7) {
        printf("-1\n");
        return;
    }
    for (int i = 1; i <= 6; i++) {
        if (g->adjacencyMatrix[number][i] != NOT_EXIST) {
            index = g->adjacencyMatrix[number][i];
            if (g->edges[index].start == number)
                printf(" %d %d", g->edges[index].end, g->edges[index].weight);
            else if (g->edges[index].end == number)
                printf(" %d %d", g->edges[index].start, g->edges[index].weight);
        }
    }
    printf("\n");
}

//문제 상황에 맞게 세팅한다.
void setGraph(Graph *g) {
    insertEdge(g, 1, 2, 1);
    insertEdge(g, 1, 3, 1);
    insertEdge(g, 1, 4, 1);
    insertEdge(g, 1, 6, 2);
    insertEdge(g, 2, 3, 1);
    insertEdge(g, 3, 5, 4);
    insertEdge(g, 5, 5, 4);
    insertEdge(g, 5, 6, 3);
}

int main() {
    Graph *g = createGraph();
    char command;
    int number, start, end, weight;
    
    setGraph(g);
    while (1) {
        scanf("%c", &command);
        if (command == 'q')
            return 0;
        switch (command)
        {
        case 'a':
            scanf("%d", &number);
            printEdge(g, number);
            break;
        case 'm' :
            scanf("%d %d %d", &start, &end, &weight);
            insertEdge(g, start, end , weight);
        default:
            break;
        getchar();
        }
    }
    return 0;
}