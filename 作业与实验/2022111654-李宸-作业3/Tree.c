#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    char data;
    struct TreeNode *left;
    struct TreeNode *right;
}Node;

typedef struct QueueNode
{
    Node *node;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue
{
    QueueNode *front;
    QueueNode *rear;
} Queue;

struct Queue *createQueue()
{
    struct Queue *queue = (struct Queue *)malloc(sizeof(struct Queue));// 为队列分配内存空间
    queue->front = queue->rear = NULL;// 初始时，前端和后端都为空
    return queue;
}

void enqueue(Queue *queue, Node *node)// 入队操作
{
    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
    newNode->node = node;
    newNode->next = NULL;
    if (queue->rear == NULL)
    {
        queue->front = newNode;
        queue->rear = newNode;
    }
    else
    {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

Node *dequeue(Queue *queue)// 出队操作
{
    if (queue->front == NULL)
    {
        return NULL;
    }
    Node *node = queue->front->node;
    QueueNode *temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL)
    {
        queue->rear = NULL;
    }
    free(temp);
    return node;
}

int getSize(struct Queue* queue) {
    int size = 0;
    struct QueueNode* current = queue->front;
    
    while (current != NULL) {
        size++;
        current = current->next;
    }
    
    return size;
}

struct StackNode {
    struct TreeNode* node;
    struct StackNode* next;
};

struct Stack
{
    struct StackNode *top;
};// 栈结构

struct Stack *createStack()
{
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    stack->top = NULL;
    return stack;
}// 初始化栈

void push(struct Stack *stack, struct TreeNode *node)
{
    struct StackNode *newNode = (struct StackNode *)malloc(sizeof(struct StackNode));
    newNode->node = node;
    newNode->next = stack->top;
    stack->top = newNode;
}// 入栈

struct TreeNode *pop(struct Stack *stack)
{
    if (stack->top == NULL)
    {
        return NULL;
    }

    struct TreeNode *node = stack->top->node;
    struct StackNode *temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
    return node;
}// 出栈

Node *createNode(char data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node *buildTree()
{
    char data;
    scanf(" %c", &data); // 读入节点数据
    if (data == '#')
    {
        return NULL;
    }
    else
    {
        Node *root = createNode(data);
        printf("Enter left child of %c: ", data);
        root->left = buildTree();
        printf("Enter right child of %c: ", data);
        root->right = buildTree();
        return root;
    }
}

void displayTree(Node *root)
{
    if (root == NULL)
    {
        printf("# ");
        return;
    }
    printf("%c ", root->data);
    displayTree(root->left);
    displayTree(root->right);
}

void saveTreeToFile(Node *root, FILE *file)
{
    if (root == NULL)
    {
        fprintf(file, "# ");
    }
    else
    {
        fprintf(file, "%c ", root->data);
        saveTreeToFile(root->left, file);
        saveTreeToFile(root->right, file);
    }
}

void preorderRecursive(Node *root)//递归先序遍历
{
    if (root == NULL)
    {
        return;
    }
    printf("%c ", root->data);
    preorderRecursive(root->left);
    preorderRecursive(root->right);
}

void inorderRecursive(Node *root)//递归中序遍历
{
    if (root == NULL)
    {
        return;
    }
    inorderRecursive(root->left);
    printf("%c ", root->data);
    inorderRecursive(root->right);
}

void postorderRecursive(Node *root)//递归后序遍历
{
    if (root == NULL)
    {
        return;
    }
    postorderRecursive(root->left);
    postorderRecursive(root->right);
    printf("%c ", root->data);
}

void levelOrderTraversal(Node *root)//层序遍历
{
    if (root == NULL)
    {
        return;
    }

    struct Queue *queue = createQueue();
    enqueue(queue, root);

    while (queue->front != NULL)
    {
        struct TreeNode *current = dequeue(queue);
        printf("%c ", current->data);

        if (current->left != NULL)
        {
            enqueue(queue, current->left);
        }

        if (current->right != NULL)
        {
            enqueue(queue, current->right);
        }
    }

    free(queue);
}

void preorderTraversal(Node *root)//非递归先序遍历
{
    if (root == NULL)
    {
        return;
    }

    struct Stack *stack = createStack();
    struct TreeNode *current = root;

    while (current != NULL || stack->top != NULL)
    {
        while (current != NULL)
        {
            printf("%c ", current->data);
            push(stack, current);
            current = current->left;
        }

        if (stack->top != NULL)
        {
            current = pop(stack);
            current = current->right;
        }
    }
    free(stack);
}

void inorderTraversal(Node *root)//非递归中序遍历
{
    if (root == NULL)
    {
        return;
    }

    struct Stack *stack = createStack();
    struct TreeNode *current = root;

    while (current != NULL || stack->top != NULL)
    {
        while (current != NULL)
        {
            push(stack, current);
            current = current->left;
        }

        if (stack->top != NULL)
        {
            current = pop(stack);
            printf("%c ", current->data);
            current = current->right;
        }
    }

    free(stack);
}

void postorderTraversal(Node *root)//非递归后序遍历
{
    if (root == NULL)
    {
        return;
    }

    struct Stack *stack1 = createStack();
    struct Stack *stack2 = createStack();

    push(stack1, root);

    while (stack1->top != NULL)
    {
        struct TreeNode *current = pop(stack1);
        push(stack2, current);

        if (current->left != NULL)
        {
            push(stack1, current->left);
        }

        if (current->right != NULL)
        {
            push(stack1, current->right);
        }
    }

    while (stack2->top != NULL)
    {
        printf("%c ", pop(stack2)->data);
    }

    free(stack1);
    free(stack2);
}

int isCompleteBinaryTree(Node *root)
{
    if (root == NULL) {
        return 1; // 空树是完全二叉树
    }
    
    Queue* queue = createQueue(); 
    int flag = 0; // 表示是否遇到过空节点
    
    enqueue(queue, root);

    while (queue->front <= queue->rear)
    {
        Node *current = dequeue(queue);
        if (current != NULL)
        {
            // 如果之前遇到过空节点，则不是完全二叉树
            if (flag)
            {
                return 0;
            }
            enqueue(queue, current->left);
            enqueue(queue, current->right);
        }
        else
        {
            flag = 1;
        }
        if(queue->front == queue->rear){
            break;
        }
    }

    return 1; // 如果成功遍历完所有节点，那么是完全二叉树
}

int getWidth(Node *root)
{
    if (root == NULL)
    {
        return 0;
    }

    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;

    enqueue(queue, root);
    int maxWidth = 0;

    while (queue->front <= queue->rear)
    {
        int size = getSize(queue);
        maxWidth = (size > maxWidth) ? size : maxWidth;

        for (int i = 0; i < size; i++)
        {
            Node *current = dequeue(queue);
            if (current->left)
            {
                enqueue(queue, current->left);
            }
            if (current->right)
            {
                enqueue(queue, current->right);
            }
        }
        if(queue->front == queue->rear){
            break;
        }
    }

    return maxWidth;
}

void menu(){
    printf("1.Preorder Traversal(Recursive)\n2.Inorder Traversal(Recursive)\n3.Postorder Traversal(Recursive)\n4.levelOrderTraversal\n5.Preorder Traversal(Non-Recursive)\n6.Inorder Traversal(Non-Recursive)\n7.Postorder Traversal(Non-Recursive)\n8.Judge complete tree\n9.Width\n");
}

int main()
{
    Node *root ;
    printf("Enter nodes of binary tree (use # for empty nodes):\n");
    root = buildTree();

    printf("Binary Tree in Preorder Traversal: ");
    displayTree(root);

    FILE *file = fopen("binary_tree.txt", "w");
    if (file == NULL)
    {
        printf("\nError opening file to save the binary tree.\n");
    }
    else
    {
        printf("\nBinary Tree saved to 'binary_tree.txt'.\n");
        saveTreeToFile(root, file);
        fclose(file);
    }
    menu();
    int choose;
    printf("Input your choice:\n");
    scanf("%d", &choose);
    switch (choose)
    {
    case 1:
        printf("Binary Tree in Preorder Traversal(Recursive):\n ");
        preorderRecursive(root);
        break;
    case 2:
        printf("Binary Tree in Inorder Traversal(Recursive):\n");
        inorderRecursive(root);
        break;
    case 3:
        printf("Binary Tree in Postorder Traversal(Recursive):\n");
        postorderRecursive(root);
        break;
    case 4:
        printf("Binary Tree in levelOrderTraversal:\n");
        levelOrderTraversal(root);
        break;
    case 5:
        printf("Binary Tree in Preorder Traversal(Non-Recursive):\n ");
        preorderTraversal(root);
        break;
    case 6:        
        printf("Binary Tree in Inorder Traversal(Non-Recursive):\n ");
        inorderTraversal(root);
        break;
    case 7:       
        printf("Binary Tree in Postorder Traversal(Non-Recursive):\n ");
        postorderTraversal(root);
        break;
    case 8:
        if(isCompleteBinaryTree(root)){
            printf("Binary Tree is complete\n");
        }
        else{
            printf("Binary Tree is not complete\n");
        }
        break;
    case 9:
        printf("the width of binary tree is %d",getWidth(root));
        break;
    }
    return 0;
}
