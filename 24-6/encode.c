#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct KeyCircle
{
    char data;
    struct KeyCircle *next;
} KC;

KC *generateList(char arr[])//生成环
{
    KC *list = NULL, *cur = NULL, *tail = NULL;
    for (int i = 0; i < 95; i ++)
    {
        tail = (KC *)malloc(sizeof(KC));
        tail -> data = arr[i];
        tail -> next = NULL;

        if (list == NULL)
        {
            list = tail;
            cur = tail;
        }
        else
        {
            cur -> next = tail;
        }
        cur = tail;
    }
    tail -> next = list;
    return list;
}

KC *deleteNode(KC *prev, KC *node)//删除节点
{
    if (prev -> next == node -> next)//只剩两个
    {
        free(node);
        prev -> next = prev;
        return prev;
    }
    else
    {
        prev -> next = node -> next;
        free(node);
        return prev -> next;
    }
}

KC *move(KC *prev,KC *node)
{
    int i = (int)node -> data;
    node = deleteNode(prev, node);
    if (prev == node)
    {
        return node;
    }
    else
    {
        for (int j = 0; j < i - 1; j ++)
        {
            node = node -> next;
            prev = prev -> next;
        }
        return prev;
    }
}

int main()
{
    FILE *in, *out;
    in = fopen("in.txt", "r");
    out = fopen("in_crpyt.txt", "w");
    char input[32] = {0};
    char key[100];
    int ascii[95] = {0};
    gets(input);
    
    int str_len = strlen(input);
    for (int i = 0; i < str_len; i ++)
    {
        ascii[input[i] - ' '] ++;
    }
    int cnt = 0;
    for (int i = 0; i < str_len; i ++)
    {
        if (ascii[input[i] - ' '] == 1)
        {
            key[cnt] = input[i];
            cnt ++;
        }
        else if (ascii[input[i] - ' '] > 1)
        {
            key[cnt] = input[i];
            cnt ++;
            ascii[input[i] - ' '] = -1;
        }
    }
    
    for (int i = cnt, j = 32; i < 95; i ++, j ++)
    {
        if (ascii[j - ' '] == 0)
        {
            key[i] = j;
        }
        else
        {
            i --;
        }
    }
    
    KC *cur = generateList(key);
    KC *prev = cur;
    const char head = cur -> data;
    while (prev -> next!= cur)
    {
        // printf("%c ", prev -> data);
        prev = prev -> next;
    }
    // printf("%c ", prev -> data);
    // printf("\n");
    int cnt_key = 0;
    char code[100];
    while (cur -> next != cur)
    {
        prev = move(prev, cur);
        cur = prev -> next;
        // printf("%c ", cur -> data);
        code[cnt_key] = cur -> data;
        cnt_key ++;
    }
    code[cnt_key] = head;
    
    KC *crypt = generateList(code);
    KC *crypt_prev = crypt;

    char code2[100];
    while (crypt -> next != crypt_prev)
    {
        code2[crypt -> data - ' '] = crypt -> next -> data;
        crypt = crypt -> next;
    }
    code2[crypt -> data - ' '] = crypt_prev -> data;

    char ch;
    while ((ch = fgetc(in)) != EOF)
    {
        if (ch < 32 || ch > 126)
        {
            fputc(ch, out);
        }
        else
        {
            fputc(code2[ch - ' '], out);
        }
    }

    fclose(in);
    fclose(out);
    return 0;
}