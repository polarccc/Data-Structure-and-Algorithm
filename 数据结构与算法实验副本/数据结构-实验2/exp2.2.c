#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 256

// 结构体用于存储字符和其频率
typedef struct {
    char character;
    int frequency;
} CharFrequency;

// 结构体表示哈夫曼树的节点
typedef struct TreeNode {
    char character;
    int frequency;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// 函数用于查找字符在字符频率数组中的位置
int findCharacterIndex(CharFrequency *freqArray, int size, char character) {
    for (int i = 0; i < size; i++) {
        if (freqArray[i].character == character) {
            return i;
        }
    }
    return -1;
}

// 函数用于构建哈夫曼树
TreeNode *buildHuffmanTree(CharFrequency *freqArray, int size) {
    // 创建节点数组，每个字符对应一个节点
    TreeNode *nodes[size];
    for (int i = 0; i < size; i++) {
        nodes[i] = (TreeNode *)malloc(sizeof(TreeNode));
        nodes[i]->character = freqArray[i].character;
        nodes[i]->frequency = freqArray[i].frequency;
        nodes[i]->left = NULL;
        nodes[i]->right = NULL;
    }

    // 构建哈夫曼树
    while (size > 1) {
        // 找到两个频率最低的节点
        int min1 = 0, min2 = 1;
        if (nodes[min1]->frequency > nodes[min2]->frequency) {
            int temp = min1;
            min1 = min2;
            min2 = temp;
        }

        for (int i = 2; i < size; i++) {
            if (nodes[i]->frequency < nodes[min1]->frequency) {
                min2 = min1;
                min1 = i;
            } else if (nodes[i]->frequency < nodes[min2]->frequency) {
                min2 = i;
            }
        }

        // 创建一个新节点，合并两个最小频率的节点
        TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
        newNode->character = '\0';
        newNode->frequency = nodes[min1]->frequency + nodes[min2]->frequency;
        newNode->left = nodes[min1];
        newNode->right = nodes[min2];

        // 将新节点插入节点数组中
        nodes[min1] = newNode;
        nodes[min2] = nodes[size - 1];
        size--;
    }

    return nodes[0]; // 返回根节点
}

// 函数用于生成字符的哈夫曼编码
void generateHuffmanCodes(TreeNode *root, char *prefix, int depth) {
    if (root == NULL) {
        return;
    }

    if (root->character != '\0') {
        prefix[depth] = '\0';
        printf("字符: %c, 频率: %d, 编码: %s\n", root->character, root->frequency, prefix);
    }

    prefix[depth] = '0';
    generateHuffmanCodes(root->left, prefix, depth + 1);

    prefix[depth] = '1';
    generateHuffmanCodes(root->right, prefix, depth + 1);
}

int main() {
    // 打开待处理的文本文件
    FILE *inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("无法打开文件\n");
        return 1;
    }

    CharFrequency freqArray[MAX_SIZE]; // 假设字符集大小为MAX_SIZE

    // 初始化字符频率数组
    for (int i = 0; i < MAX_SIZE; i++) {
        freqArray[i].character = (char)i;
        freqArray[i].frequency = 0;
    }

    // 逐字符读取文件并统计频率
    char currentChar ;
    while ((currentChar = fgetc(inputFile)) != EOF) {
        int index = findCharacterIndex(freqArray, MAX_SIZE, currentChar);
        printf("%c",currentChar);
        printf("777777\n");
        if (index != -1) {
            freqArray[index].frequency++;
            printf("6666666");
            printf("%d",freqArray[index].frequency);
        }
    }

    // 构建哈夫曼树
    TreeNode *huffmanTree = buildHuffmanTree(freqArray, MAX_SIZE);

    char prefix[MAX_SIZE]; // 存储字符的哈夫曼编码前缀
    generateHuffmanCodes(huffmanTree, prefix, 0);

    // 关闭输入文件
    fclose(inputFile);

    // 打开输出文件
    FILE *outputFile = fopen("output.huffman", "wb");
    if (outputFile == NULL) {
        printf("无法创建输出文件\n");
        return 1;
    }

    // 重新打开待处理的文本文件
    inputFile = fopen("input.txt", "r");

    // 逐字符读取原始文件并写入哈夫曼编码文件
    while ((currentChar = fgetc(inputFile)) != EOF) {
        int index = findCharacterIndex(freqArray, MAX_SIZE, currentChar);
        if (index != -1) {
            fprintf(outputFile, "%s", prefix); // 写入哈夫曼编码
        }
    }

    // 关闭文件
    fclose(inputFile);
    fclose(outputFile);

    // 计算压缩率
    inputFile = fopen("input.txt", "r");
    outputFile = fopen("output.huffman", "rb");

    fseek(inputFile, 0L, SEEK_END);
    fseek(outputFile, 0L, SEEK_END);

    long originalSize = ftell(inputFile);
    long compressedSize = ftell(outputFile);

    double compressionRatio = (double)compressedSize / originalSize;
    printf("压缩率: %.2f%%\n", compressionRatio * 100);

    // 关闭文件
    fclose(inputFile);
    fclose(outputFile);

    // 译码并与原文件进行比较
    inputFile = fopen("input.txt", "r");
    outputFile = fopen("output_decoded.txt", "w");

    TreeNode *currentNode = huffmanTree;
    while ((currentChar = fgetc(outputFile)) != EOF) {
        if (currentChar == '0') {
            currentNode = currentNode->left;
        } else if (currentChar == '1') {
            currentNode = currentNode->right;
        }

        if (currentNode->left == NULL && currentNode->right == NULL) {
            fprintf(outputFile, "%c", currentNode->character);
            currentNode = huffmanTree; // 重置为根节点
        }
    }

    // 关闭文件
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
