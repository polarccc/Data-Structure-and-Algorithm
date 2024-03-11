#include <stdio.h>
#include <stdlib.h>

int V;//顶点数
int E;//边数

// 定义边的结构体
struct Edge {
    int src, dest, weight;
};

// 定义并查集的结构体
struct Subset {
    int parent; //父节点
    int rank;   //高度
};

// 查找操作，用于查找节点所属的集合
int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

// 合并操作，用于将两个集合合并为一个集合
void Union(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
    if (subsets[xroot].rank < subsets[yroot].rank) {
        subsets[xroot].parent = yroot;
    } else if (subsets[xroot].rank > subsets[yroot].rank) {
        subsets[yroot].parent = xroot;
    } else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// 按照边的权重进行升序排序
int cmp(const void* a, const void* b) {
    struct Edge* edge1 = (struct Edge*)a;
    struct Edge* edge2 = (struct Edge*)b;
    return edge1->weight - edge2->weight;
}

// Kruskal算法，用于构建加权连通图的最小生成树
void Kruskal(struct Edge edges[]) {
    //初始化
    struct Subset* subsets = (struct Subset*)malloc(V * sizeof(struct Subset));
    for (int i = 0; i < V; i++) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    struct Edge result[V];
    int e = 0, i = 0;
    while (e < V - 1 && i < E) {
        struct Edge next_edge = edges[i++];
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);
        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

    printf("mst edge:\n");
    for (i = 0; i < e; i++) {
        printf("%d - %d  weight: %d\n", result[i].src, result[i].dest, result[i].weight);
    }
}

int main() {

    FILE *file = fopen("graph.txt", "r");
    
    if (file == NULL) {
        printf("failed to open file!\n");
        return 1;
    }


    fscanf(file, "%d", &V);
    fscanf(file, "%d", &E);
    struct Edge edges[E];

    for (int i = 0; i < E; i++)
    {
        fscanf(file, "%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight);
    }

    qsort(edges, E, sizeof(edges[0]), cmp);

    Kruskal(edges);

    return 0;
}
