#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_VERTICES 100

int matrix[MAX_VERTICES][MAX_VERTICES] = {0};
int numVertices;//边数

void displayMatrix()//打印邻接矩阵
{
    printf("Directed Adjacency Matrix:\n");
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

struct Node {
    int vertex;         //顶点
    struct Node* next;
};// 定义邻接表的节点结构

struct VertexNode {
    int vertex;         //顶点
    struct Node* head;  //与该顶点相邻的第一个节点的指针
};// 定义顶点表的节点结构

struct Graph
{
    int numVertices;//图中顶点的数量
    struct VertexNode *vertexArray;//顶点的数组
};// 定义邻接表

struct Stack// 栈的结构
{
    int top;
    int capacity;
    int *data;
};

enum NodeState {
    UNVISITED,
    VISITED,
    EXPLORED
};

struct Node *createNode(int vertex)// 创建新节点
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

struct Graph *createGraph(int numVertices)// 创建邻接表
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;

    graph->vertexArray = (struct VertexNode *)malloc(numVertices * sizeof(struct VertexNode));

    for (int i = 0; i < numVertices; i++)
    {
        graph->vertexArray[i].vertex = i;
        graph->vertexArray[i].head = NULL;
    }
    return graph;
}

void addEdgeGraph(struct Graph *graph, int src, int dest)// 添加边
{
    struct Node *newNode = createNode(dest);
    newNode->next = graph->vertexArray[src].head;
    graph->vertexArray[src].head = newNode;
}

void printGraph(struct Graph *graph)// 打印邻接表
{
    for (int i = 0; i < numVertices; i++)
    {
        struct Node *temp = graph->vertexArray[i].head;
        printf("VertexNode %d Adjacency Table:", i);
        while (temp)
        {
            printf(" -> %d", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }

}

void graphToMatrix(struct Graph *graph)//邻接表转邻接矩阵
{
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            matrix[i][j] = 0;
        }
    }

    for (int i = 0; i < numVertices; i++)
    {
        struct Node *current = (struct Node *)malloc(sizeof(struct Node *));
        current=graph->vertexArray[i].head;
        while (current != NULL)
        {
            matrix[i][current->vertex] = 1;
            current = current->next;
        }
    }
}

struct Graph* matrixToGraph()//邻接矩阵转邻接表
{
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    
    graph->vertexArray = (struct VertexNode*)malloc(numVertices * sizeof(struct VertexNode));
    
    for (int i = 0; i < numVertices; i++) {
        graph->vertexArray[i].vertex = i;
        graph->vertexArray[i].head = NULL;
        
        for (int j = 0; j < numVertices; j++) {
            if (matrix[i][j] == 1) {
                struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
                newNode->vertex = j;
                newNode->next = NULL;
                
                if (graph->vertexArray[i].head == NULL) {
                    graph->vertexArray[i].head = newNode;
                } else {
                    struct Node* current = graph->vertexArray[i].head;
                    while (current->next != NULL) {
                        current = current->next;
                    }
                    current->next = newNode;
                }
            }
        }
    }

    return graph;
}

// 辅助数组，用于标记已访问的顶点
int visited[MAX_VERTICES];       //是否访问过
int dfsNumber[MAX_VERTICES];     //DFS编码
int dfsCount = 0;                //DFS编码计数器

void initialize(){
    memset(dfsNumber,0,sizeof(dfsNumber));
    dfsCount=0;
}

void printDFSNumber(){
    printf("Depth-First Order:\n");
        for (int i = 0; i < numVertices; i++)
        {
            printf("Vertex %d: %d\n", i, dfsNumber[i]);
        }
        printf("Depth-First Number in order:\n");
        for (int i = 0; i <numVertices; i++)
        {
            printf("v%d ", dfsNumber[i]);
        }
}

void printBFSNumber(){
    printf("Breadth-First Order:\n");
        for (int i = 0; i < numVertices; i++)
        {
            printf("Vertex %d: %d\n", i, dfsNumber[i]);
        }
        printf("Breadth-First Number in order:\n");
        for (int i = 0; i < numVertices; i++)
        {
            printf("v%d ", dfsNumber[i]);
        }
}

void DFSGraph(struct Graph *graph, int vertex)// 深度优先搜索函数
{
    visited[vertex] = 1; // 标记当前顶点为已访问
    dfsNumber[vertex] = dfsCount++;

    struct Node *currentNode = graph->vertexArray[vertex].head;
    printf("Visiting vertex %d\n", vertex);

    while (currentNode != NULL)
    {
        int adjacentVertex = currentNode->vertex;
        if (!visited[adjacentVertex])
        {
            printf("Edge from %d to %d is a tree edge\n", vertex, adjacentVertex);
            DFSGraph(graph, adjacentVertex);
        }
        else
        {
            printf("Edge from %d to %d is a back edge\n", vertex, adjacentVertex);
        }
        currentNode = currentNode->next;
    }
}

void DFSTraversalGraph(struct Graph *graph)// 深度优先遍历整个图
{

    for (int i = 0; i < graph->numVertices; i++)
    {
        visited[i] = 0;
        dfsNumber[i] = -1;
    }

    for (int i = 0; i < graph->numVertices; i++)
    {
        if (!visited[i])
        {
            printf("Starting DFS from vertex %d\n", i);
            DFSGraph(graph, i);
        }
    }

}

struct Stack createStack(int capacity) {
    struct Stack stack;
    stack.capacity = capacity;
    stack.top = -1;
    stack.data = (int*)malloc(capacity * sizeof(int));
    return stack;
}

void push(struct Stack* stack, int item) {
    stack->data[++stack->top] = item;
}

int pop(struct Stack* stack) {
    return stack->data[stack->top--];
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

void DFSGraphNonRe(struct Graph* graph, int startVertex, int* visited, struct Stack* stack) {
    push(stack, startVertex);
    visited[startVertex] = EXPLORED;

    while (!isEmpty(stack)) {
        int currentVertex = stack->data[stack->top];

        int childFound = 0;
        struct Node* temp = graph->vertexArray[currentVertex].head;
        while (temp != NULL) {
            int adjVertex = temp->vertex;
            if (visited[adjVertex] == UNVISITED) {
                push(stack, adjVertex);
                visited[adjVertex] = EXPLORED;
                childFound = 1;
            }
            temp = temp->next;
        }

        if (!childFound) {
            stack->top--;
            visited[currentVertex] = VISITED;
            printf("Visited: %d\n", currentVertex);
            dfsNumber[currentVertex] = dfsCount++;
        }
    }
}

void DFSGraphTreeNonRe(struct Graph* graph) {
    int* visited = (int*)malloc(graph->numVertices * sizeof(int));
    for (int i = 0; i < graph->numVertices; i++) {
        visited[i] = UNVISITED;
    }

    struct Stack stack = createStack(graph->numVertices);
    
    
    for (int i = 0; i < graph->numVertices; i++) {
        if (visited[i] == UNVISITED) {
            
            printf("DFS Tree starting from vertex %d:\n", i);
            DFSGraphNonRe(graph, i, visited, &stack);
        }
    }
    
    free(visited);
}

void DFSMatrix(int node) {
    
    visited[node] = 1;
    dfsNumber[node] = dfsCount++;
    printf("Visiting node: %d\n", node);

    for (int i = 0; i < numVertices; i++) {
        if (matrix[node][i] && !visited[i]) {
            DFSMatrix(i);
        }
    }
}

void DFSMatrixNonRe(int startNode) {
    int stack[MAX_VERTICES];
    int top = -1;

    stack[++top] = startNode;

    while (top >= 0) {
        int node = stack[top--];

        if (!visited[node]) {
            visited[node] = 1;
            dfsNumber[node] = dfsCount++;
            printf("Visiting node: %d\n", node);

            for (int i = numVertices - 1; i >= 0; i--) {
                if (matrix[node][i] && !visited[i]) {
                    stack[++top] = i;
                }
            }
        }
    }
}

void BFSMatrix(int startNode) {
    int queue[MAX_VERTICES];
    int front = 0, rear = -1;

    queue[++rear] = startNode;
    visited[startNode] = 1;

    while (front <= rear) {
        int node = queue[front++];
        dfsNumber[node] = dfsCount++;
        printf("Visiting node: %d\n", node);

        for (int i = 0; i < numVertices; i++) {
            if (matrix[node][i] && !visited[i]) {
                queue[++rear] = i;
                visited[i] = 1;
            }
        }
    }
}

void BFSGraph(struct Graph* graph, int startVertex, int* visited) {
    int queue[graph->numVertices];
    int front = 0, rear = -1;

    queue[++rear] = startVertex;
    visited[startVertex] = 1;

    while (front <= rear) {
        int currentVertex = queue[front++];
        dfsNumber[currentVertex] = dfsCount++;
        printf("Visiting node: %d\n", currentVertex);

        struct Node* temp = graph->vertexArray[currentVertex].head;
        while (temp) {
            int adjVertex = temp->vertex;
            if (!visited[adjVertex]) {
                queue[++rear] = adjVertex;
                visited[adjVertex] = 1;
            }
            temp = temp->next;
        }
    }
}

int calculateInDegree(struct Graph* graph, int vertex) {
    int inDegree = 0;
    for (int i = 0; i < graph->numVertices; ++i) {
        struct Node* temp = graph->vertexArray[i].head;
        while (temp) {
            if (temp->vertex == vertex) {
                inDegree++;
            }
            temp = temp->next;
        }
    }
    return inDegree;
}

int calculateOutDegree(struct Graph* graph, int vertex) {
    int outDegree = 0;
    struct Node* temp = graph->vertexArray[vertex].head;
    while (temp) {
        outDegree++;
        temp = temp->next;
    }
    return outDegree;
}

int calculateDegree(struct Graph* graph, int vertex) {
    int inDegree = calculateInDegree(graph, vertex);
    int outDegree = calculateOutDegree(graph, vertex);
    return inDegree + outDegree;
}

int main() {
    int numEdges;
    int start, end;

    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);

    struct Graph *graph = createGraph(numVertices);

    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);

    int choose1;
    printf("1.Directed Adjacency Matrix 2.Directed Adjacency Graph\n");
    scanf("%d",&choose1);

    switch (choose1)
    {
    case 1:
        // 初始化邻接矩阵
        for (int i = 0; i < numVertices; i++)
        {
            for (int j = 0; j < numVertices; j++)
            {
                matrix[i][j] = 0;
            }
        }

        // 输入边信息
        for (int i = 0; i < numEdges; i++)
        {
            printf("Enter edge (start end, begin with 0): ");
            scanf("%d %d", &start, &end);
            if (start >= 0 && start < numVertices && end >= 0 && end < numVertices) // 对边的输入正确性检查
            {
                matrix[start][end] = 1;
            }
            else
            {
                printf("Invalid vertices\n");
                i--;
            }
        }

        // 显示邻接矩阵
        displayMatrix();
        break;
    case 2:
        
        printf("Enter edge (start end, begin with 0):\n");
        for (int i = 0; i < numEdges; i++)
        {
            int src, dest;
            scanf("%d %d", &src, &dest);
            if (src >= 0 && src < numVertices && dest >= 0 && dest < numVertices) // 对边的输入正确性检查
            {
                addEdgeGraph(graph, src, dest);
            }
            else
            {
                printf("Invalid vertices\n");
            }
            
        }

        printGraph(graph);
        break;
    }

    int choose2;
    printf("1.Matrix to Graph 2.Graph to Matrix\n");
    printf("3.DFSTraversalGraph 4.DFSGraphTreeNonRe 5.DFSMatrix 6.DFSMatrixNonRe 7.BFSGraph 8.BFSMatrix\n");
    printf("9.calculate InDegree OutDegree and Degree\n");
    scanf("%d",&choose2);

    switch (choose2)
    {
    case 1:
        struct Graph *graph1 = matrixToGraph();
        printGraph(graph1);
        break;
    case 2:
        graphToMatrix(graph);
        displayMatrix();
        break;

    case 3:
        initialize();
        DFSTraversalGraph(graph); // 执行深度优先搜索
        printDFSNumber();
        break;
    case 4:
        initialize();
        DFSGraphTreeNonRe(graph);
        printDFSNumber();
        break;
    case 5://时间复杂度为O(V^2)，其中V是节点数，因为我们需要遍历邻接矩阵中的每个元素，空间复杂度为O(V)。深度优先序列就是访问节点的顺序，生成森林是指如果图中有多个连通分量，每个连通分量都会生成一个DFS树。
        initialize();
        printf("Depth-First Traversal:\n");
        for (int i = 0; i < numVertices; i++)
        {
            if (!visited[i])
            {
                DFSMatrix(i);
            }
        }
        printDFSNumber();
        break;
    case 6:
        initialize();
        printf("Depth-First Traversal:\n");
        for (int i = 0; i < numVertices; i++)
        {
            if (!visited[i])
            {
                DFSMatrixNonRe(i);
            }
        }
        printDFSNumber();
        break;
    case 7://这个代码将邻接表的广度优先搜索算法实现为一个函数，其中使用了队列来存储待访问的节点。时间复杂度为O(V+E)，空间复杂度为O(V)。
        initialize();
        printf("Breadth-First Traversal:\n");
        for (int i = 0; i < numVertices; ++i)
        {
            if (!visited[i])
            {
                BFSGraph(graph, i, visited);
            }
        }

        printBFSNumber();
        break;
    case 8://这个代码使用了一个队列来实现广度优先搜索，将待访问的节点入队并在循环中进行处理，直到队列为空。时间复杂度为O(V^2)，空间复杂度为O(V)。
        initialize();
        printf("Breadth-First Traversal:\n");
        for (int i = 0; i < numVertices; i++)
        {
            if (!visited[i])
            {
                BFSMatrix(i);
            }
        }

        printBFSNumber();
        break;
    case 9:
        printf("Vertex\tIn-Degree\tOut-Degree\tDegree\n");
        for (int i = 0; i < numVertices; ++i)
        {
            int inDegree = calculateInDegree(graph, i);
            int outDegree = calculateOutDegree(graph, i);
            int degree = calculateDegree(graph, i);
            printf("%d\t%d\t\t%d\t\t%d\n", i, inDegree, outDegree, degree);
        }
    }
    return 0;
}
