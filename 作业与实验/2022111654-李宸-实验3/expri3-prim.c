#include <stdio.h>
#include <limits.h>

#define INF INT_MAX

int n;//顶点数

// 函数用于找到最小权值的顶点
int minCost(int cost[], int mstSet[]) {
    int min = INF, min_index;

    for (int w = 0; w < n; w++) {
        if (!mstSet[w] && cost[w] < min) {
            min = cost[w];
            min_index = w;
        }
    }
    return min_index;
}

void primMST(int graph[n][n]) {
    int parent[n];  // 存储最小生成树的父节点
    int cost[n];     // 存储与最小生成树相连的最小权重边的权值
    int mstSet[n];  // 记录节点是否包含在最小生成树中

    // 初始化所有顶点的权值为无穷大，mstSet为false
    for (int i = 0; i < n; i++) {
        cost[i] = INF;
        mstSet[i] = 0;
    }

    // 将第一个顶点作为起始顶点
    cost[0] = 0;
    parent[0] = -1;

    // 循环V-1次的最小生成树
    for (int count = 0; count < n - 1; count++) {
        int u = minCost(cost, mstSet);
        mstSet[u] = 1;
        for (int v = 0; v < n; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < cost[v]) {
                parent[v] = u;
                cost[v] = graph[u][v];
            }
        }
    }

    // 打印最小生成树
    printf("边\t权重\n");
    for (int i = 1; i < n; i++) {
        printf("%d - %d\t%d\n", parent[i], i, graph[i][parent[i]]);
    }
}


int main() {
    FILE *file = fopen("graph.txt", "r");
    int start,end,weight;
    int edge;

    if (file == NULL) {
        printf("failed to open file!\n");
        return 1;
    }
    
    fscanf(file, "%d", &n);
    fscanf(file, "%d", &edge);

    int graph[n][n];

    // 初始化邻接矩阵
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }

    for (int i = 0; i < edge; i++) {
        fscanf(file, "%d %d %d", &start, &end, &weight);
        graph[start][end] = weight;
        graph[end][start] = weight;
    }

    primMST(graph);

    return 0;
}
