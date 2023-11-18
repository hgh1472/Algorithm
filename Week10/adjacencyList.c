#include <stdio.h>
#include <stdlib.h>


typedef struct incidenceList {
    struct incidenceList *next;
    int edgeIndex;
} IncidenceList;

typedef struct vertex {
    int data;
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
}Graph;

IncidenceList *makeIncidenceList() {
    IncidenceList *new = (IncidenceList *)malloc(sizeof(IncidenceList));
    new->next = NULL;
    return new;
}

Graph *createGraph() {
    Graph *g = (Graph *)malloc(sizeof(Graph));
    g->edges = (Edge *)malloc(sizeof(Edge) * 22);
    g->vertices = (Vertex *)malloc(sizeof(Vertex) * 7);
    for (int i = 1; i <= 6; i++) {
        g->vertices[i].data = i; // 각 정점의 data값. 이 문제에서는 인덱스와 같다.
        g->vertices[i].incidence = makeIncidenceList();
    }
    return g;
}

// Edge의 양 끝점을 구분하기 쉽게 start, end를 오름차순으로 정렬
void sortAscending(int *a, int *b) {
    int tmp;
    if (*a > *b) {
        tmp = *a;
        *a = *b;
        *b = tmp;
    }
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

int hasVertex(int start, int end) {
    if (start < 1)
        return 0;
    if (end > 6)
        return 0;
    return 1;
}
void insertEdge(Graph *g, int start, int end, int weight) {
    sortAscending(&start, &end); // Edge를 구분하기 쉽게 시작점과 끝점을 오름차순으로 정렬
    if (!hasVertex(start, end)) {
        printf("-1\n");
        return;
    }
    int index = calculateEdgeIndex(start, end);
    g->edges[index].start = start;
    g->edges[index].end = end;
    g->edges[index].weight = weight;
    IncidenceList *new = makeIncidenceList();
    
    // Vertex가 가지는 IncidenceList에 해당 Edge를 추가한다.
    new->edgeIndex = index;
    new->next = g->vertices[start].incidence->next;
    g->vertices[start].incidence->next = new;
}

void printEdge(Graph *g, int number) {
    if (number >= 7) {
        printf("-1\n");
        return;
    }
    for (int i = 1; i <= 21; i++) {
        // start나 end가 해당하는 Vertex랑 일치하고 존재할 경우(weight != 0) 출력한다.
        if (g->edges[i].start == number && g->edges[i].weight != 0)
            printf(" %d %d", g->edges[i].end, g->edges[i].weight);
        else if (g->edges[i].end == number && g->edges[i].weight != 0)
            printf(" %d %d", g->edges[i].start, g->edges[i].weight);
    }
    printf("\n");
}

//문제 상황에 맞게 세팅한다.
void setGrpah(Graph *g) {
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
    
    setGrpah(g);
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