#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// 定义字符频率统计的数据结构
struct CharFrequency {
    char character;
    int frequency;
};

// 定义哈夫曼树节点结构
struct HuffmanNode {
    char character;
    int frequency;
    struct HuffmanNode* left;
    struct HuffmanNode* right;
};

// 哈夫曼编码表的数据结构
struct HuffmanCode {
    char character;
    char* code;
};

// 检查字符是否在字符集中
bool isInCharacterSet(char character, struct CharFrequency charset[], int charsetSize) {
    for (int i = 0; i < charsetSize; i++) {
        if (charset[i].character == character) {
            return true;
        }
    }
    return false;
}

// 创建一个新的哈夫曼树节点
struct HuffmanNode* newNode(char character, int frequency) {
    struct HuffmanNode* node = (struct HuffmanNode*)malloc(sizeof(struct HuffmanNode));
    node->character = character;
    node->frequency = frequency;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// 构建哈夫曼树
struct HuffmanNode* buildHuffmanTree(struct CharFrequency charset[], int charsetSize) {
    // 创建初始节点列表
    struct HuffmanNode* nodes[charsetSize];
    for (int i = 0; i < charsetSize; i++) {
        nodes[i] = newNode(charset[i].character, charset[i].frequency);
    }

    // 构建哈夫曼树
    while (charsetSize > 1) {
        // 找到两个频率最低的节点
        int min1 = 0;
        int min2 = 1;
        for (int i = 2; i < charsetSize; i++) {
            if (nodes[i]->frequency < nodes[min1]->frequency) {
                min2 = min1;
                min1 = i;
            } else if (nodes[i]->frequency < nodes[min2]->frequency) {
                min2 = i;
            }
        }

        // 创建一个新节点，作为两个最低频率节点的父节点
        struct HuffmanNode* newNode = malloc(sizeof(struct HuffmanNode));
        newNode->character = '\0'; // 内部节点没有字符
        newNode->frequency = nodes[min1]->frequency + nodes[min2]->frequency;
        newNode->left = nodes[min1];
        newNode->right = nodes[min2];

        // 将新节点添加到节点列表中
        nodes[min1] = newNode;
        nodes[min2] = nodes[charsetSize - 1];
        charsetSize--;
    }

    // 返回根节点
    return nodes[0];
}

// 生成哈夫曼编码表
void generateHuffmanCodes(struct HuffmanNode* root, char code[], int top, struct HuffmanCode huffmanCodes[], int* huffmanCodesSize) {
    // 如果是叶子节点，将字符和编码添加到哈夫曼编码表
    if (root->left == NULL && root->right == NULL) {
        huffmanCodes[*huffmanCodesSize].character = root->character;
        huffmanCodes[*huffmanCodesSize].code = strdup(code);
        (*huffmanCodesSize)++;
    }

    // 遍历左子树，并在编码末尾添加'0'
    if (root->left != NULL) {
        code[top] = '0';
        generateHuffmanCodes(root->left, code, top + 1, huffmanCodes, huffmanCodesSize);
    }

    // 遍历右子树，并在编码末尾添加'1'
    if (root->right != NULL) {
        code[top] = '1';
        generateHuffmanCodes(root->right, code, top + 1, huffmanCodes, huffmanCodesSize);
    }
}

// 函数：将原始文本文件中的字符替代为哈夫曼编码并保存到目标文件
void encodeAndSaveFile(FILE* sourceFile, FILE* targetFile, struct HuffmanCode huffmanCodes[], int huffmanCodesSize) {
    char c;
    while ((c = fgetc(sourceFile)) != EOF) {
        // 查找字符的哈夫曼编码
        for (int i = 0; i < huffmanCodesSize; i++) {
            if (huffmanCodes[i].character == c) {
                printf("%s\n",huffmanCodes[i].code);
                break;
            }
        }
    
    /*
    // 定义一个缓冲区来存储编码后的数据
    char buffer[1024];
    int bufferIndex = 0;

    int c;
    while ((c = fgetc(sourceFile)) != EOF) {
        // 查找字符的哈夫曼编码
        char* code = NULL;
        for (int i = 0; i < huffmanCodesSize; i++) {
            if (huffmanCodes[i].character == (char)c) {
                code = huffmanCodes[i].code;
                printf("\nsuccess\n");
                printf("%s",code);
                break;
            }
        }

        // 将哈夫曼编码添加到缓冲区中
        if (code != NULL) {
            int codeLength = strlen(code);
            for (int i = 0; i < codeLength; i++) {
                buffer[bufferIndex++] = code[i];
                if (bufferIndex == sizeof(buffer)) {
                    // 缓冲区已满，将数据写入目标文件
                    puts(buffer);
                    printf("456");
                    fwrite(buffer, sizeof(char), bufferIndex, targetFile);
                    bufferIndex = 0; // 重置缓冲区索引
                }
            }
        }
    }

    // 将剩余数据写入目标文件
    if (bufferIndex > 0) {
        fwrite(buffer, sizeof(char), bufferIndex, targetFile);
    }
    */
}
}

int main(){
    FILE* file;
    char filename[100];
    
    // 提示用户输入文件名
    printf("请输入文件名：");
    scanf("%s", filename);
    
    // 尝试打开文件
    file = fopen(filename, "r");
    
    // 检查文件是否成功打开
    if (file == NULL) {
        printf("无法打开文件。\n");
        return 1; // 退出程序
    }

    // 初始化字符集和字符频率统计数组
    struct CharFrequency charset[256]; // 假设使用ASCII字符集
    int charsetSize = 0;
    
    // 逐字符读取文件并统计频率
    int c;
    while ((c = fgetc(file)) != EOF) {
        if (!isInCharacterSet(c, charset, charsetSize)) {
            charset[charsetSize].character = (char)c;
            charset[charsetSize].frequency = 1;
            charsetSize++;
        } else {
            // 增加字符的频率
            for (int i = 0; i < charsetSize; i++) {
                if (charset[i].character == c) {
                    charset[i].frequency++;
                    break;
                }
            }
        }
    }

    // 关闭文件
    fclose(file);

    // 构建哈夫曼树
    struct HuffmanNode* huffmanTree = buildHuffmanTree(charset, charsetSize);

    // 生成哈夫曼编码表
    struct HuffmanCode huffmanCodes[256]; // 假设使用ASCII字符集
    int huffmanCodesSize = 0;
    char code[256];
    int top = 0;
    generateHuffmanCodes(huffmanTree, code, top, huffmanCodes, &huffmanCodesSize);

    // 打印字符频率和哈夫曼编码
    printf("字符频率统计和哈夫曼编码表：\n");
    for (int i = 0; i < charsetSize; i++) {
        printf("字符 '%c' 出现 %d 次，哈夫曼编码：%s\n", charset[i].character, charset[i].frequency, huffmanCodes[i].code);
    }

    // 释放内存
    for (int i = 0; i < huffmanCodesSize; i++) {
        free(huffmanCodes[i].code);
    }

    // 打开原始文本文件和目标文本文件
    FILE* sourceFile = fopen(filename, "r");
    FILE* targetFile = fopen("encoded_output.txt", "w");

    // 检查文件是否成功打开
    if (sourceFile == NULL || targetFile == NULL) {
        printf("无法打开文件。\n");
        return 1; // 退出程序
    }

    // 使用哈夫曼编码替代字符并保存到目标文件
    encodeAndSaveFile(sourceFile, targetFile, huffmanCodes, huffmanCodesSize);

    // 关闭文件
    fclose(sourceFile);
    fclose(targetFile);

    // 释放内存
    //for (int i = 0; i < huffmanCodesSize; i++) {
    //    free(huffmanCodes[i].code);
    //}

    printf("文本文件已成功编码并保存到 encoded_output.txt 中。\n");

    return 0;
}
