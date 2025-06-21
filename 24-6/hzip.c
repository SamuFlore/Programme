#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 32

char Huffman_Code[MAXSIZE];//临时存放一个字符的霍夫曼编码，生成编码之后存到HCode数组中
char HCode[128][MAXSIZE];//128个可见字符的霍夫曼编码

struct cc
{
    char c;
    int cnt;
};

typedef struct huffman_node
{
    struct cc ccount;
    struct huffman_node *left, *right;
    struct huffman_node *next;
} Huffman;

int cmp(const void *a, const void *b)
{
    struct cc *p1 = (struct cc *)a;
    struct cc *p2 = (struct cc *)b;
    if (p1 -> cnt < p2 -> cnt)
    {
        return -1;
    }
    else if (p1 -> cnt > p2 -> cnt)
    {
        return 1;
    }
    else
    {
        if (p1 -> c < p2 -> c)
        {
            return -1;
        }
        else if (p1 -> c > p2 -> c)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

Huffman *head = NULL;

void insertNode(Huffman *node)
{
    Huffman *cur = head, *prev = NULL;
    for (; cur != NULL && node -> ccount.cnt > cur -> ccount.cnt; prev = cur, cur = cur -> next);
    if (cur -> ccount.cnt == node -> ccount.cnt)
    {
        node -> next = cur -> next;
        cur -> next = node;
    }
    else
    {
        node -> next = cur;
        prev -> next = node;
    }
}

void CreateTree(struct cc ccount[], int n)
{
    Huffman *q = NULL;
    for (int i = 0; i < n; i ++)//构建有序链表
    {
        Huffman *p = (Huffman *)malloc(sizeof(Huffman));
        p -> ccount = ccount[i];
        p -> left = NULL;
        p -> right = NULL;
        p -> next = NULL;
        if (head == NULL)
        {
            head = p;
            q = p;
        }
        else
        {
            q -> next = p;
            q = p;
        }
    }

    while (head -> next != NULL)//合并最小节点，生成霍夫曼树
    {
        Huffman *p = (Huffman *)malloc(sizeof(Huffman));
        p -> ccount.cnt = head -> ccount.cnt + head -> next -> ccount.cnt;//权重相加
        p -> left = head;
        p -> right = head -> next;
        p -> next = NULL;
        head = head -> next -> next;
        insertNode(p);
    }
}



void CreateCode(Huffman *node, char code, int level)//遍历霍夫曼树，生成编码，第一次传入根节点，
{
    if (level != 0)
    {
        Huffman_Code[level - 1] = code;
    }
    if (node -> left == NULL && node -> right == NULL)//叶节点
    {
        Huffman_Code[level] = '\0';
        strcpy(HCode[node -> ccount.c], Huffman_Code);
    }
    else
    {
        CreateCode(node -> left, '0', level + 1);
        CreateCode(node -> right, '1', level + 1);
    }
}

void Compress(FILE *in, FILE *out)
{
    unsigned char *pc, hc;
    int c = 0, i = 0;
    fseek(in, 0, SEEK_SET);
    do
    {
        c = fgetc(in);
        if (c == EOF)
        {
            c = 0;
        }
        for (pc = HCode[c]; *pc != '\0'; pc ++)
        {
            hc = (hc << 1) | (*pc - '0');
            i ++;
            if (i == 8)
            {
                fputc(hc, out);
            }
        }
        if (c == 0 && i != 0)
        {
            while (i ++ < 8)
            {
                hc = (hc << 1);
            }
            fputc(hc, out);
        }   
    } while (c);
}

int main(int argc, char *argv[])
{
    char c;
    FILE *in, *out;
    if (argc == 1)
    {
        printf("Usage: hzip.exe [-u] <filename>");
        return 1;
    }
    else if (argc == 3 && strcmp(argv[1], "-u") == 0)//解压缩
    {
        char *dot = strrchr(argv[2], '.');
        if (dot == NULL || strcmp(dot, ".hzip"))
        {
            printf("File extension error!\n");
            return 1;
        }
    }
    else if (argc == 2)//压缩
    {
        in = fopen(argv[1], "r");
        if (in == NULL)
        {
            printf("Error: Cannot open file %s\n", argv[1]);
            return 1;
        }
        char *dot = strrchr(argv[1], '.');
        if (dot == NULL || strcmp(dot, ".txt"))
        {
            printf("File extension error!\n");
            return 1;
        }
        struct cc ccount[128];
        while ((c = fgetc(in)) != EOF)
        {
            ccount[c].c = c;//第c位字符即c本身
            ccount[c].cnt ++;//次数加一
        }
        char *outname = (char *)malloc(strlen(argv[1]) + 5);
        strcpy(outname, argv[1]);
        strcpy(dot, ".hzip");
        out = fopen(outname, "w");
        CreateTree(ccount, 128);
        CreateCode(head, '\0', 0);
        Compress(in, out);
        fclose(in);
        fclose(out);
    }
    else if (argc == 3 && strcmp(argv[1], "-u") != 0)
    {
        printf("Usage: hzip.exe [-u] <filename>");
        return 1;
    }
    return 0;

}