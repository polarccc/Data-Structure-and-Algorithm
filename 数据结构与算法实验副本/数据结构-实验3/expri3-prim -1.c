#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 10
#define INF 9999

int graph[MAX_VERTICES][MAX_VERTICES];

void primMST() {
    int selected[MAX_VERTICES];
    int minWeight[MAX_VERTICES];
    int parent[MAX_VERTICES];
    
    for (int i = 0; i < MAX_VERTICES; i++) {
        minWeight[i] = INF;
        selected[i] = false;
    }
    
    minWeight[0] = 0;
    parent[0] = -1;
    
    for (int count = 0; count < MAX_VERTICES - 1; count++) {
        int minIndex, min;
        min = INF;
        
        for (int v = 0; v < MAX_VERTICES; v++) {
            if (selected[v] == false && minWeight[v] < min) {
                min = minWeight[v];
                minIndex = v;
            }
        }
        
        int u = minIndex;
        selected[u] = true;
        
        for (int v = 0; v < MAX_VERTICES; v++) {
            if (graph[u][v] && selected[v] == false && graph[u][v] < minWeight[v]) {
                parent[v] = u;
                minWeight[v] = graph[u][v];
            }
        }
    }
    
    printf("Minimum Spanning Tree:\n");
    printf("Edge \tWeight\n");
    for (int i = 1; i < MAX_VERTICES; i++) {
        printf("%d - %d \t%d\n", parent[i], i, graph[i][parent[i]]);
    }
}

int main() {
    
    FILE *file = fopen("graph.txt", "r");
    int start,end,weight;
    int q,edge;

    if (file == NULL) {
        printf("failed to open file!\n");
        return 1;
    }
    
    fscanf(file, "%d", &q);
    fscanf(file, "%d", &edge);

    //int graph[V][V];

    // 初始化邻接矩阵
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            graph[i][j] = 0;
        }
    }

    for (int i = 0; i < edge; i++) {
        fscanf(file, "%d %d %d", &start, &end, &weight);
        graph[start][end] = weight;
        graph[end][start] = weight;
    }
    
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            printf("%d ",graph[i][j]) ;
        }
        printf("\n");
    }
    
/*
    // 初始化图
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            graph[i][j] = 0;
        }
    }
    
    // 添加边
    graph[0][1] = 2;
    graph[1][0] = 2;
    graph[0][3] = 6;
    graph[3][0] = 6;
    graph[1][2] = 3;
    graph[2][1] = 3;
    graph[1][3] = 8;
    graph[3][1] = 8;
    graph[1][4] = 5;
    graph[4][1] = 5;
    graph[2][4] = 7;
    graph[4][2] = 7;
    graph[3][4] = 9;
    graph[4][3] = 9;
    graph[5][7] = 2;
    graph[7][5] = 2;
    graph[6][9] = 7;
    graph[9][6] = 7;
    graph[7][8] = 3;
    graph[8][7] = 3;
    graph[2][9] = 5;
    graph[9][2] = 5;
    graph[8][3] = 4;
    graph[3][8] = 4;
    graph[5][8] = 7;
    graph[8][5] = 7;
*/
    //primMST();
    
    return 0;
}
