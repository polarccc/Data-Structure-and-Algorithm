#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 256

int id=0;//用于表示HuffmanCode数组的下标

// 结构体用于存储字符和其频率
typedef struct {
    char character;
    int frequency;
} CharFrequency;

// 结构体表示哈夫曼树的节点
typedef struct TreeNode {
    char character;
    int frequency;
    char code[MAX_SIZE];
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

//存储字符及对应的哈夫曼编码
typedef struct HuffmanCode {
    char character;
    char code[MAX_SIZE];
}HuffmanCode;

//判断是否在字符集中出现过
int isInCharacterSet(char character, CharFrequency charset[], int charsetSize) {
    for (int i = 0; i < charsetSize; i++) {
        if (charset[i].character == character) {
            return 1;
        }
    }
    return 0;
}

// 用于查找字符在字符频率数组中的位置
int findCharacterIndex(CharFrequency *freqArray, int size, char character) {
    for (int i = 0; i < size; i++) {
        if (freqArray[i].character == character) {
            return i;
        }
    }
    return -1;
}

// 构建哈夫曼树
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
void generateHuffmanCodes(TreeNode *root, char *prefix, int depth,HuffmanCode huffmanCodes[]) {
    if (root == NULL) {
        return;
    }

    if (root->character != '\0') {
        prefix[depth] = '\0';
        printf("字符: %c, 频率: %d, 编码: %s\n", root->character, root->frequency, prefix);
        
        huffmanCodes[id].character=root->character;
        strcpy(huffmanCodes[id].code,prefix);
        id++;
    }
    if (root->left != NULL){
        prefix[depth] = '0';
    generateHuffmanCodes(root->left, prefix, depth +1, huffmanCodes);
    }
        
    if (root->right != NULL){
        prefix[depth] = '1';
    generateHuffmanCodes(root->right, prefix, depth +1, huffmanCodes);
    }
}

int main() {
    // 打开待处理的文本文件
    FILE *inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("无法打开文件\n");
        return 1;
    }

    // 初始化字符集和字符频率统计数组
    CharFrequency charset[MAX_SIZE]; // 使用ASCII字符集
    int charsetSize = 0;
    
    // 逐字符读取文件并统计频率
    char c;
    while ((c = fgetc(inputFile)) != EOF) {
        if (!isInCharacterSet(c, charset, charsetSize)) {
            charset[charsetSize].character = c;
            charset[charsetSize].frequency = 1;
            charsetSize++;
        } else {
            // 统计字符的频率
            for (int i = 0; i < charsetSize; i++) {
                if (charset[i].character == c) {
                    charset[i].frequency++;
                    break;
                }
            }
        }
    }
    
    // 关闭文件
    fclose(inputFile);

    //建立哈夫曼编码数组，存储字符和对应的编码
    HuffmanCode huffmanCodes[charsetSize];

    // 构建哈夫曼树
    TreeNode *huffmanTree = buildHuffmanTree(charset, charsetSize);

    char prefix[charsetSize]; // 存储字符的哈夫曼编码前缀
    generateHuffmanCodes(huffmanTree, prefix, 0, huffmanCodes);
    
    // 关闭输入文件
    fclose(inputFile);

    // 打开输出文件
    FILE *outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        printf("无法创建输出文件\n");
        return 1;
    }

    // 重新打开待处理的文本文件
    inputFile = fopen("input.txt", "r");
    char currentChar;

    // 逐字符读取原始文件并写入哈夫曼编码文件
    while ((currentChar = fgetc(inputFile)) != EOF) {
        for (int i = 0; i < charsetSize; i++) {
            if (huffmanCodes[i].character == currentChar) {
                fprintf(outputFile,"%s",huffmanCodes[i].code);
            }
    }
    }
    // 关闭文件
    fclose(inputFile);
    fclose(outputFile);
    
    //转换二进制字符
    FILE *textFile = fopen("output.txt", "r");
    FILE *binaryFile = fopen("output.bin", "wb");

    if (textFile == NULL || binaryFile == NULL) {
        perror("无法打开文件");
        return 1;
    }

    int currentChar2;
    char binaryString[9];  // 存储二进制编码的字符串，加上 '\0' 结尾
    int count = 0;

    while ((currentChar2 = fgetc(textFile)) != EOF) {
        if (currentChar2 == '0' || currentChar2 == '1') {
            binaryString[count] = currentChar2;
            count++;

            // 如果已经读取了8个字符，将其转换并写入二进制文件
            if (count == 8) {
                binaryString[count] = '\0';
                unsigned char byte = (unsigned char)strtol(binaryString, NULL, 2);
                fwrite(&byte, 1, 1, binaryFile);
                count = 0;
            }
        }
    }

    // 关闭文件
    fclose(textFile);
    fclose(binaryFile);

    // 计算压缩率
    inputFile = fopen("input.txt", "r");
    outputFile = fopen("output.bin", "rb");

    fseek(inputFile, 0L, SEEK_END);
    fseek(outputFile, 0L, SEEK_END);

    long originalSize = ftell(inputFile);
    long compressedSize = ftell(outputFile);

    double compressionRatio = (double)compressedSize / originalSize;
    printf("\n压缩率: %.2f%%\n", compressionRatio * 100);

    // 关闭文件
    fclose(inputFile);
    fclose(outputFile);
    
    // 解码部分
    inputFile = fopen("output.txt", "r");
    outputFile = fopen("output_decoded.txt", "w");

    TreeNode *currentNode = huffmanTree;
    char currentChar3;
    printf("After Decode:");
    while ((currentChar3 = fgetc(inputFile)) != EOF) {
        if (currentChar3 == '0') {
            currentNode = currentNode->left;
        } else if (currentChar3 == '1') {
            currentNode = currentNode->right;
        }

        if (currentNode->left == NULL && currentNode->right == NULL) {
            printf("%c",currentNode->character);
            fprintf(outputFile, "%c", currentNode->character);
            currentNode = huffmanTree; // 重置为根节点
        }
    }

    // 关闭文件
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}


