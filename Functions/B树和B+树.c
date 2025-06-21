#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define M 3 // B树的阶
#define MAX_KEYS (M - 1) // 每个节点最多键数

typedef struct node 
{
    int keynum;//本结点关键字个数
    int key[MAX_KEYS + 1];//每行最多M - 1个key，多加的一个用来保存整个树最大的key值，这里用INT_MAX来表示
    struct node *ptr[MAX_KEYS + 2];//M + 1个指针指向子树
} BNode;

//查找B树
int searchBTree(BNode *root, int k)
{
    int i, n;
    BNode *p = root;
    while (p != NULL)
    {
        n = p -> keynum;//该结点键个数
        p -> key[n + 1] = INT_MAX;
        i = 1;
        while (k > p -> key[i]) i ++;//遍历比待查找元素小的键值，循环结束后，i标记大于等于待查找元素的第一个元素
        if (p -> key[i] == k) return p -> key[i];//找到，返回之
        else p = p -> ptr[i - 1];//可知待查找元素在i指向元素和上一元素之间，则去找两元素之间的子树
    }
    return -1;//未找到
}

// 创建新节点
BNode* createNode() {
    BNode* newNode = (BNode*)malloc(sizeof(BNode));
    newNode->keynum = 0;
    for (int i = 0; i < MAX_KEYS + 1; i++) newNode->key[i] = 0;
    for (int i = 0; i < MAX_KEYS + 2; i++) newNode->ptr[i] = NULL;
    return newNode;
}

// 分裂子节点（核心操作）
void splitChild(BNode* parent, int childIndex) {
    BNode* child = parent->ptr[childIndex];
    BNode* newNode = createNode();

    // 确定分裂位置（中间键索引）
    int splitPos = (child->keynum - 1) / 2;

    // 新节点获取右半部分键
    newNode->keynum = child->keynum - splitPos - 1;
    for (int i = 0; i < newNode->keynum; i++) {
        newNode->key[i + 1] = child->key[splitPos + 1 + i];
    }

    // 复制子指针（如果不是叶子节点）
    if (child->ptr[0] != NULL) {
        for (int i = 0; i <= newNode->keynum; i++) {
            newNode->ptr[i] = child->ptr[splitPos + 1 + i];
        }
    }

    // 调整原节点的键数量
    child->keynum = splitPos;

    // 父节点插入中间键
    for (int i = parent->keynum; i >= childIndex + 1; i--) {
        parent->key[i + 1] = parent->key[i];
    }
    parent->key[childIndex + 1] = child->key[splitPos + 1];

    // 调整父节点的子指针
    for (int i = parent->keynum + 1; i >= childIndex + 1; i--) {
        parent->ptr[i + 1] = parent->ptr[i];
    }
    parent->ptr[childIndex + 1] = newNode;
    parent->keynum++;
}

// 插入非满节点
void insertNonFull(BNode* node, int key) {
    int i = node->keynum;

    // 叶子节点直接插入
    if (node->ptr[0] == NULL) {
        while (i >= 1 && key < node->key[i]) {
            node->key[i + 1] = node->key[i];
            i--;
        }
        node->key[i + 1] = key;
        node->keynum++;
    }
    // 内部节点递归插入
    else {
        while (i >= 1 && key < node->key[i]) i--;
        i++;
        if (node->ptr[i]->keynum == MAX_KEYS) {
            splitChild(node, i - 1);
            if (key > node->key[i]) i++;
        }
        insertNonFull(node->ptr[i], key);
    }
}

// 插入入口函数
BNode* insert(BNode* root, int key) {
    // 根节点已满需要分裂
    if (root->keynum == MAX_KEYS) {
        BNode* newRoot = createNode();
        newRoot->ptr[0] = root;
        splitChild(newRoot, 0);
        insertNonFull(newRoot, key);
        return newRoot;
    } else {
        insertNonFull(root, key);
        return root;
    }
}

// 辅助打印函数（中序遍历）
void printTree(BNode* node, int level) {
    if (node) {
        for (int i = 0; i < level; i++) printf("  ");
        printf("Lv%d Keys: [", level);
        for (int i = 1; i <= node->keynum; i++) {
            printf("%d", node->key[i]);
            if (i != node->keynum) printf(", ");
        }
        printf("]\n");

        if (node->ptr[0] != NULL) {
            for (int i = 0; i <= node->keynum; i++) {
                printTree(node->ptr[i], level + 1);
            }
        }
    }
}

// 测试用例
int main() {
    BNode* root = createNode();
    int testKeys[] = {10, 20, 5, 6, 12, 30, 7, 8};
    
    for (int i = 0; i < sizeof(testKeys)/sizeof(int); i++) {
        root = insert(root, testKeys[i]);
        printf("After insert %d:\n", testKeys[i]);
        printTree(root, 0);
        printf("------------------------\n");
    }
    
    return 0;
}