#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARACTERS 256

// 结点表示哈夫曼树的结构
struct Node {
    char character;
    char* huffmanCode;
    int frequency;
    struct Node* left;
    struct Node* right;
};

// 创建新的哈夫曼树结点
struct Node* newNode(char character, int frequency) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->character = character;
    node->frequency = frequency;
    node->left = node->right = NULL;
    return node;
}

// 优先队列用于构建哈夫曼树
struct PriorityQueue {
    struct Node** nodes;
    int size;
};

// 初始化优先队列
struct PriorityQueue* initPriorityQueue() {
    struct PriorityQueue* pq = (struct PriorityQueue*)malloc(sizeof(struct PriorityQueue));
    pq->nodes = (struct Node**)malloc(sizeof(struct Node*) * MAX_CHARACTERS);
    pq->size = 0;
    return pq;
}

// 向优先队列插入结点
void insert(struct PriorityQueue* pq, struct Node* node) {
    int i = pq->size++;
    while (i > 0 && node->frequency < pq->nodes[(i - 1) / 2]->frequency) {
        pq->nodes[i] = pq->nodes[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    pq->nodes[i] = node;
}

// 从优先队列中取出最小频率的结点
struct Node* extractMin(struct PriorityQueue* pq) {
    struct Node* minNode = pq->nodes[0];
    pq->nodes[0] = pq->nodes[--pq->size];
    int i = 0;
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;
        if (left < pq->size && pq->nodes[left]->frequency < pq->nodes[i]->frequency) {
            smallest = left;
        }
        if (right < pq->size && pq->nodes[right]->frequency < pq->nodes[smallest]->frequency) {
            smallest = right;
        }
        if (smallest != i) {
            struct Node* temp = pq->nodes[i];
            pq->nodes[i] = pq->nodes[smallest];
            pq->nodes[smallest] = temp;
            i = smallest;
        } else {
            break;
        }
    }
    return minNode;
}

// 构造哈夫曼树
struct Node* buildHuffmanTree(int frequency[MAX_CHARACTERS]) {
    struct PriorityQueue* pq = initPriorityQueue();

    for (int i = 0; i < MAX_CHARACTERS; i++) {
        if (frequency[i] > 0) {
            insert(pq, newNode((char)i, frequency[i]));
        }
    }

    while (pq->size > 1) {
        struct Node* left = extractMin(pq);
        struct Node* right = extractMin(pq);
        struct Node* mergedNode = newNode('\0', left->frequency + right->frequency);
        mergedNode->left = left;
        mergedNode->right = right;
        insert(pq, mergedNode);
    }

    struct Node* root = extractMin(pq);
    free(pq->nodes);
    free(pq);

    return root;
}

// 生成字符编码
void generateHuffmanCodes(struct Node* root, int code[], int top) {
    static char huffmanCodes[MAX_CHARACTERS][MAX_CHARACTERS];
    
    if (root->left) {
        code[top] = 0;
        generateHuffmanCodes(root->left, code, top + 1);
    }

    if (root->right) {
        code[top] = 1;
        generateHuffmanCodes(root->right, code, top + 1);
    }

    if (!root->left && !root->right) {
        printf("字符 '%c' 的哈夫曼编码: ", root->character);
        for (int i = 0; i < top; i++) {
            printf("%d", code[i]);
            huffmanCodes[root->character][i] = code[i] + '0';
        }
        huffmanCodes[root->character][top] = '\0';
        printf("\n");
    }
}

// 在哈夫曼树中查找字符的哈夫曼编码
void findHuffmanCode(struct Node* root, char character, char* codeBuffer) {
    int top = 0;
    while (1) {
        if (root->left) {
            codeBuffer[top++] = '0';
            root = root->left;
        } else if (root->right) {
            codeBuffer[top++] = '1';
            root = root->right;
        }

        if (!root->left && !root->right) {
            codeBuffer[top] = '\0';
            return;
        }
    }
}

int main() {
    // 打开文本文件
    FILE* inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("无法打开输入文件\n");
        return 1;
    }
    // 打开目标文本文件以便写入哈夫曼编码
    FILE* outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        printf("无法创建输出文件\n");
        fclose(inputFile);
        return 1;
    }
    

    int frequency[MAX_CHARACTERS] = {0};
    char c;
    while ((c = fgetc(inputFile)) != EOF) {
        frequency[c]++;
    }
    fclose(inputFile);

    // 构建哈夫曼树
    struct Node* root = buildHuffmanTree(frequency);

    int code[MAX_CHARACTERS];
    int top = 0;

    // 生成字符编码
    generateHuffmanCodes(root, code, top);

    inputFile = fopen("input.txt", "r");
    char c1;
    char huffmanCodeBuffer[MAX_CHARACTERS]; // 缓冲区用于存储哈夫曼编码

    while ((c = fgetc(inputFile)) != EOF) {
    findHuffmanCode(root, c, huffmanCodeBuffer);
    fprintf(outputFile, "%s", huffmanCodeBuffer);
    }
    
    // 关闭文件
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
