#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100

typedef struct Treenode
{
    int data;
    struct Treenode *left;
    struct Treenode *right;
} Treenode;

void pre_order(Treenode *node)//访问根节点->遍历左子树->遍历右子树
{
    if (node == NULL)
        return;
    printf("%d ", node -> data);
    pre_order(node -> left);
    pre_order(node -> right);
}

void middle_order(Treenode *node)//访问根节点在中间执行
{
    if (node == NULL)
        return;
    middle_order(node -> left);
    printf("%d ", node -> data);
    middle_order(node -> right);
}

void post_order(Treenode *node)//规律同上
{
    if (node == NULL)
        return;
    middle_order(node -> left);
    middle_order(node -> right);
    printf("%d ", node -> data);
}

void layer_order(Treenode *node)//层次遍历
{
    Treenode *nodequeue[MAXSIZE];
    Treenode *p;
    int head, tail;
    if (node != NULL)
    {
        nodequeue[0] = node;
        head = 0;
        tail = 1;
        while (head < tail)
        {
            p = nodequeue[head];
            head ++;//挨个输出node
            printf("%d ", p -> data);
            if (p -> left != NULL)
                nodequeue[tail ++] = p -> left;//把左子放到数组中
            if (p -> right != NULL)
                nodequeue[tail ++] = p -> right;
        } 
    }
}

Treenode *copyTree(Treenode *srcnode)//拷贝二叉树
{
    Treenode *cpy;
    if (srcnode == NULL)
        cpy == NULL;
    else
    {
        cpy = (Treenode *)malloc(sizeof(Treenode));
        cpy -> data = srcnode -> data;
        cpy -> left = copyTree(srcnode -> left);
        cpy -> right = copyTree(srcnode -> right);//前序遍历原二叉树，挨个复制到新的
    }
}

void deleteTree(Treenode *node)//删除二叉树
{
    if (node != NULL)
    {
        deleteTree(node -> left);
        deleteTree(node -> right);
        free(node);//后序遍历
        node = NULL;
    }
}

int max(x, y)
{
    if (x > y) return x;
    else return y;
}
int heightTree(Treenode *node)//计算二叉树高度
{
    if (node == NULL)
        return 0;
    else
        return 1 + max(heightTree(node -> left), heightTree(node -> right));//左子树高度与右子树高度最大值加上根节点
}

Treenode *initBST(Treenode *root, int data)//初始化二叉查找树
{
    Treenode *p;
    if (root == NULL)
    {
        p = (Treenode *)malloc(sizeof(Treenode));
        p -> data = data;
        p -> left = NULL;
        p -> right = NULL;
        return p;
    }
    else if (data < root -> data)//左子小于根
    {
        root -> left = initBST(root -> left, data);//
    }
    else//右子大于根
    {
        root -> right = initBST(root -> right, data);
    }
    return root;
}
//使用时，root初始化为NULL，for循环读入数据，每轮循环，root = initBST(root, data);

Treenode *insertBST(Treenode *node, int data)//将数据插入入口为node的二叉查找树中
{
    if (node == NULL)
    {
        node = (Treenode *)malloc(sizeof(Treenode));
        node -> data = data;
        node -> left = NULL;
        node -> right = NULL;
    }
    else if (data < node -> data)
    node -> left = insertBST(node -> left, data);//数据比本结点小，则将数据存在本结点的左子，下同理
    else if (data > node -> data)
    node -> right = insertBST(node -> right, data);
    else; //找到相同的元素
    //替换，或是别的操作
    return node;
}

Treenode *searchBST(Treenode *node, int key)//查找二叉查找树的一个结点，传入根节点，比较key，返回目标结点
{
    if (node != NULL)
    {
        if (key == node -> data)
            return node;
        if (key > node -> data)
            return searchBST(node -> right, key);
        else 
            return searchBST(node -> left, key);
    }
    return NULL;//未找到
}

