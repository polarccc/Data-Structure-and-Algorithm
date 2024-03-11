//Dijkstra算法是解决带权有向图或无向图的单源最短路径问题的一种算法。它的思想是从源节点开始，依次找到到其他节点的最短路径，直到找到目标节点或者所有节点都被遍历过。

//具体实现时，Dijkstra算法维护一个集合S，表示已经找到了最短路径的节点集合，以及一个数组dist，表示源节点到各个节点的最短距离。初始时，集合S为空，dist数组中除了源节点的距离为0之外，其余节点的距离都初始化为无穷大。然后，从源节点开始，依次找到距离源节点最近的节点，并将其加入集合S中，然后更新与该节点相邻的未加入集合S的节点的距离值，如果更新后的距离值比原来的距离值更小，则更新dist数组中的值。重复以上过程，直到所有节点都被加入集合S中，或者找到目标节点为止。

//以下是Dijkstra算法的C语言实现，假设图的节点编号从0开始，邻接矩阵表示图的边权重：

//```c
#include <stdio.h>
#include <limits.h>

#define V 5

void printSolution(int dist[]) {
    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t %d\n", i, dist[i]);
}

int minDistance(int dist[], int sptSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (sptSet[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}


void dijkstra(int graph[V][V], int src) {
    int dist[V]; // 存储源节点到各个节点的最短距离
    int sptSet[V]; // 存储已经找到最短路径的节点集合

    // 初始化dist数组和sptSet数组
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
    }

    dist[src] = 0; // 源节点到自己的距离为0

    // 找到到达各个节点的最短路径
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet); // 从未加入sptSet集合的节点中找到距离最近的节点
        sptSet[u] = 1; // 将该节点加入sptSet集合

        // 更新与该节点相邻的节点的距离值
        for (int v = 0; v < V; v++) {
            if (graph[u][v] && sptSet[v] == 0 && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printSolution(dist); // 打印结果
}

int main() {
    int graph[V][V] = {
        {0, 4, 0, 0, 7},
        {4, 0, 8, 0, 6},
        {0, 8, 0, 7, 0},
        {0, 0, 7, 0, 9},
        {7, 6, 0, 9, 0}
    };

    dijkstra(graph, 0);

    return 0;
}
//```

//在这个示例中，我们通过邻接矩阵表示图的权重，然后使用Dijkstra算法来找到源节点0到各个节点的最短距离，并打印出结果。