#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define max2(a,b) ((a)>(b)?(a):(b))
#define MAXLEN 35//单词最大长度
#define Hash_Table_Size 999983//哈希表最大长度
#define POOL_SIZE 500000//内存池大小

/*
    以下是计算最小编辑距离，请调用editdistDP函数进行计算。
*/
int **Dp, MaxDP=3300;								//for dynamic programming
int min3(int a, int b, int c)
{
    int min = a < b ? a : b;
    return min < c ? min : c;
}
int error2(char *s)
{
    fprintf(stderr,"%s\n",s); 
    exit(-1); 
}

int editdistDP(const char *str1, const char *str2) {
    int len1 = strlen(str1), len2 = strlen(str2);
    int *prev = malloc((len2+1)*sizeof(int));
    int *curr = malloc((len2+1)*sizeof(int));
    
    for(int j=0; j<=len2; j++) prev[j] = j;
    
    for(int i=1; i<=len1; i++) {
        curr[0] = i;
        for(int j=1; j<=len2; j++) {
            if(str1[i-1] == str2[j-1]) {
                curr[j] = prev[j-1];
            } else {
                curr[j] = 1 + min3(prev[j], curr[j-1], prev[j-1]);
            }
        }
        // 交换指针
        int *tmp = prev;
        prev = curr;
        curr = tmp;
    }
    
    int result = prev[len2];
    free(prev); free(curr);
    return result;
}

//字典
typedef struct HashNode
{
    char word[MAXLEN];
    int len;
    struct HashNode *next;
} HashNode;

HashNode *hashTable[Hash_Table_Size];//字典的哈希表

//双词
typedef struct bigram
{
    char word1[100];
    char word2[100];
    int dist;
    struct bigram *next;
} Bigram;

Bigram *bigramTable[Hash_Table_Size];//in.txt的双词表
Bigram wrongList[Hash_Table_Size];//错词表
int wrongCount = 0;//错词计数
Bigram *bigramPool = NULL;//双词内存池
HashNode *hashPool = NULL;//哈希表内存池
int hashPoolIndex = 0;
int bigramPoolIndex = 0;



void initPool()
{
    bigramPool = (Bigram *)malloc(sizeof(Bigram) * POOL_SIZE);
    hashPool = (HashNode *)malloc(sizeof(HashNode) * POOL_SIZE);
    
}

Bigram *allocBigram()
{
    return &bigramPool[bigramPoolIndex ++];
}

HashNode *allocHashNode()
{
    return &hashPool[hashPoolIndex ++];
}


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
//插入到字典哈希表
void insert(char word[])
{
    unsigned int hashValue = hash(word);
    HashNode *newNode = allocHashNode();
    newNode -> len = strlen(word);
    strcpy(newNode->word, word);
    newNode -> next = hashTable[hashValue];
    hashTable[hashValue] = newNode;
}
//插入到双词表
void insert2(char word1[], char word2[])
{
    unsigned int hashValue = hash(word1);
    Bigram *newNode = allocBigram();
    strcpy(newNode->word1, word1);
    strcpy(newNode->word2, word2);
    newNode -> dist = 100000;
    newNode -> next = bigramTable[hashValue];
    bigramTable[hashValue] = newNode;
}
//查找单词
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
    return 0;//未找到，拼写错误
}
//查找bigram第一个词
Bigram *search2(char word[])
{
    return bigramTable[hash(word)];
}

//字符分类
int type(int ch)
{
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
    {
        return 1;
    }
    else if (ch == ' ' || ch == '\t')
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

//读词
int getWord(FILE *in, char word[])
{
    int ch, cnt = 0, isBigram = 1;
    while ((ch = fgetc(in)) != EOF && (type(ch) == 0 || type(ch) == -1))
    {
        if (type(ch) == -1)
        {
            isBigram = 0;
        }
    }
    if (ch == EOF) return ch;
    do
    {
        word[cnt] = ch | 0x20;
        cnt ++;

    } while ((ch = fgetc(in)) != EOF && type(ch) == 1);
    if (ch != EOF) ungetc(ch, in);
    word[cnt] = '\0';
    return isBigram;
}

int cmp(const void *a, const void *b)
{
    Bigram *p1 = *(Bigram **)a;
    Bigram *p2 = *(Bigram **)b;
    return strcmp(p1 -> word2, p2 -> word2);
}


int main()
{
    initPool();
    FILE *content, *dict;
    content = fopen("in.txt", "r");
    dict = fopen("dict.txt", "r");
    setvbuf(content, NULL, _IOFBF, 4096 * 16); // 64KB缓冲区
    setvbuf(dict, NULL, _IOFBF, 4096 * 16);
    //以下读取字典
    char word[MAXLEN];
    while (fscanf(dict, "%s", word) != EOF)
    {
        insert(word);
    }
    //以下读取in.txt
    char word1[MAXLEN], word2[MAXLEN];
    char *cur = word1, *next = word2;
    int result;
    result = getWord(content, cur);
    while ((result = getWord(content, next)) != EOF)
    {
        if (result == 1)//可以构成双词
        {
            int is1inDict = search(cur);
            int is2inDict = search(next);
            if (is1inDict && is2inDict)//双词都在dict中
            {
                insert2(cur, next);
            }
            else if (is1inDict && !is2inDict)//word1在dict中，word2不在dict中
            {
                int isFind = 0;
                for (int i = 0; i < wrongCount; i ++)
                {
                    if (strcmp(wrongList[i].word1, cur) == 0 && strcmp(wrongList[i].word2, next) == 0)
                    {
                        isFind = 1;
                        break;
                    }
                }
                if (!isFind)
                {
                    strcpy(wrongList[wrongCount].word1, cur);
                    strcpy(wrongList[wrongCount].word2, next);
                    wrongCount ++;
                }
            }
            char *temp = cur;
            cur = next;
            next = temp;
        }
        else//不可，即word2是一个分句的第一个词
        {
            char *temp = cur;
            cur = next;
            next = temp;
            continue;
        }
    }
    for (int i = 0; i < wrongCount; i ++)
    {
        printf("%s: %s -> ", wrongList[i].word1, wrongList[i].word2);
        Bigram *rightBigram = search2(wrongList[i].word1);
        if (rightBigram == NULL)
        {
            printf("No suggestion\n");
        }
        else
        {
            int minDist = 1000000;
            Bigram *list[100000];
            int index = 0;
            for (Bigram *p = rightBigram; p != NULL; p = p -> next)
            {
                int dist = editdistDP(wrongList[i].word2, p -> word2);
                wrongList[i].dist = dist;
                if (dist < minDist)
                {
                    minDist = dist;
                    index = 0;
                    list[index] = p;
                    index ++;
                }
                else if (dist == minDist)
                {
                    int isFind = 0;
                    for (int j = 0; j < index; j ++)
                    {
                        if (strcmp(list[j] -> word2, p -> word2) == 0)
                        {
                            isFind = 1;
                            break;
                        }
                    }
                    if (!isFind)
                    {
                        list[index] = p;
                        index ++;
                    } 
                }
            }
            qsort(list, index, sizeof(Bigram *), cmp);
            for (int j = 0; j < index; j ++)
            {
                printf("%s", list[j] -> word2);
                if (j != index - 1)
                {
                    printf(",");
                }
            }
            printf("\n"); 
        }
    }
    return 0;
}
