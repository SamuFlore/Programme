#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NHASH 3001
#define MULT 37

char dictionary[3501][21];

unsigned int hash(char *str)
{
    unsigned int h = 0;
    char *p;
    for (p = str; *p != '\0'; p ++)
    {
        h = MULT * h + *p;
    }
    return h % NHASH;
}

typedef struct words
{
    char word[21];
    struct words *next;
} Words;

Words *hash_table[NHASH];

void insertWords(char word[])
{
    unsigned int hashValue = hash(word);
    Words *p = hash_table[hashValue];
    while (p != NULL && strcmp(p->word, word) != 0)
    {
        p = p -> next;
    }
    if (p == NULL)
    {
        Words *newWord = (Words *)malloc(sizeof(Words));
        strcpy(newWord -> word, word);
        newWord -> next = hash_table[hashValue];
        hash_table[hashValue] = newWord;
    }
}

void findWords(char word[])
{
    int cnt = 0;
    unsigned int hashValue = hash(word);
    Words *p = hash_table[hashValue];
    while (p != NULL && strcmp(p->word, word) != 0)
    {
        p = p -> next;
        cnt ++;
    }
    if (p == NULL)
    {
        printf("0 %d\n", cnt);
    }
    else
    {
        printf("1 %d\n", cnt + 1);
    }
}

void bsearch2(char dictionary[][21], char word[], int start, int end)
{
    int low = start, high = end, mid;
    int cnt = 0;
    while (low <= high)
    {
        mid = (low + high) / 2;
        cnt ++;
        if (strcmp(word, dictionary[mid]) == 0)
        {
            printf("1 %d\n", cnt);
            return ;
        }
        if (strcmp(word, dictionary[mid]) < 0)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    printf("0 %d\n", cnt);
    return ;
}

int main()
{
    FILE *dict;
    dict = fopen("dictionary3000.txt", "r");
    char w[25];
    int index = 0;
    char last = 'a';
    int alphabet[26] = {0};
    while (fscanf(dict, "%s", w) != EOF)
    {
        if (w[0] != last)
        {
            alphabet[last - 'a'] = index;
            last = w[0];
        }
        insertWords(w);
        strcpy(dictionary[index], w);
        index ++;
    }
    alphabet[25] = index;
    // for (int i = 0; i < 26; i ++)
    // {
    //     printf("%c %d\n", 'a' + i, alphabet[i]);
    // }
    char word[25];
    int mode;
    char order[50];
    // printf("%s", dictionary[3356]);
    gets(order);
    sscanf(order, "%s %d", word, &mode);
    if (mode == 1)
    {
        int i = 0;
        for (; strcmp(word, dictionary[i]) > 0; i ++);
        if (strcmp(word, dictionary[i]) == 0)
        {
            printf("1 %d\n", i + 1);
        }
        else
        {
            printf("0 %d\n", i + 1);
        }
    }
    else if (mode == 2)
    {  
        bsearch2(dictionary, word, 0, index - 1);
    }
    else if (mode == 3)
    {
        if (word[0] == 'a')
        {
            bsearch2(dictionary, word, 0, alphabet[0] - 1);
        }
        else if (word[0] == 'y')
        {
            int start = 3351;
            int end = alphabet['y' - 'a'] - 1;
            bsearch2(dictionary, word, start, end);
        }
        else
        {
            int start = alphabet[word[0] - 'a' - 1];
            int end = alphabet[word[0] - 'a'] - 1;
            // printf("%d %d\n", start, end);
            bsearch2(dictionary, word, start, end);
        }
    }
    else if (mode == 4)
    {
        findWords(word);
    }
    return 0;
}