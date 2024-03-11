#include <stdio.h>
#include <stdlib.h>
#define LEN 1024

int arr[LEN];
int id =0;

// BST节点结构
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// 创建新节点
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 插入节点
struct Node* insertNode(struct Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }

    if (value < root->data) {
        root->left = insertNode(root->left, value);
    } else if (value > root->data) {
        root->right = insertNode(root->right, value);
    }

    return root;
}

// 删除节点
struct Node* deleteNode(struct Node* root, int value) {
    if (root == NULL) {
        return root;
    }

    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    } else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        struct Node* temp = root->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }

        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

// 查找节点
struct Node* searchNode(struct Node* root, int value, int* comparisons) {
    if (root == NULL || root->data == value) {
        (*comparisons)++;
        return root;
    }

    (*comparisons)++;
    if (value < root->data) {
        return searchNode(root->left, value, comparisons);
    } else {
        return searchNode(root->right, value, comparisons);
    }
}

// 中序遍历BST（升序排序）
void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        //printf("%d ", root->data);
        arr[id++]=root->data;
        inorderTraversal(root->right);
    }
}


// 折半查找算法
int binarySearch(int arr[], int left, int right, int target, int* comparisons) {
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            (*comparisons)++;
            return mid;
        }

        (*comparisons)++;
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}

int main() {
    struct Node* root = NULL;
    FILE *inputFile = fopen("shuffled_numbers.txt", "r");
    int data;

    int comparisons1 = 0;
    int comparisons2 = 0;
    int successfulSearches = 0;
    int unsuccessfulSearches = 0;

    for(int i=0;i<LEN;i++){
        fscanf(inputFile,"%d",&data);
        root = insertNode(root, data);
    }

    //BST中序遍历
    inorderTraversal(root);

    // 删除节点
    int delete;
    printf("input node to delete:\n");
    scanf("%d",&delete);
    root = deleteNode(root, delete);

    // 查找节点
    for (int i = 0; i <= 2048; ++i) {
		if (i % 2) {//奇数
			successfulSearches++;
			struct Node* searchResult = searchNode(root, i, &comparisons1);
		}
        else {
			unsuccessfulSearches++;
			struct Node* searchResult = searchNode(root, i, &comparisons2);
		}
	}
    
    printf("BST查找成功的平均查找长度: %.2f\n", (float)comparisons1 / successfulSearches);
    printf("BST查找失败的平均查找长度: %.2f\n", (float)comparisons2 / unsuccessfulSearches);

    comparisons1 = 0;
    comparisons2 = 0;
    successfulSearches = 0;
    unsuccessfulSearches = 0;

    for (int i = 0; i <= 2048; ++i) {
		if (i % 2) {//奇数
			successfulSearches++;
			binarySearch(arr, 0, LEN - 1, i, &comparisons1);
		}
        else {
			unsuccessfulSearches++;
			binarySearch(arr, 0, LEN - 1, i, &comparisons2);
		}
	}

    printf("折半查找成功的平均查找长度: %.2f\n", (float)comparisons1 / successfulSearches);
    printf("折半查找失败的平均查找长度: %.2f\n", (float)comparisons2 / unsuccessfulSearches);
    return 0;
}
