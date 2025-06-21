#include <stdio.h>
#define Hash_Table_Size 999983//大质数
#define MAXLEN 100

typedef struct HashNode
{
    char word[MAXLEN];
    int len;
    struct HashNode *next;
} HashNode;

HashNode *hashTable[Hash_Table_Size];//哈希表

// 使用djb2哈希算法
unsigned int hash(char *word)
{
    unsigned int hash = 5381;
    int c;
    while ((c = *word++)) 
    {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash % Hash_Table_Size;
}

//插入到哈希表
void insert(char word[])
{
    unsigned int hashValue = hash(word);
    HashNode *newNode = allocHashNode();//分配空间
    newNode -> len = strlen(word);
    strcpy(newNode->word, word);
    newNode -> next = hashTable[hashValue];//冲突采用链地址法解决
    hashTable[hashValue] = newNode;
}

//查找
int search(char word[])
{
    unsigned int hashValue = hash(word);
    HashNode *cur = hashTable[hashValue];
    while (cur != NULL)
    {
        int target = strlen(word);
        if (cur -> len == target && memcmp(cur->word, word, target) == 0)
        {
            return 1;
        }
        cur = cur -> next;
    }
    return 0;//未找到
}