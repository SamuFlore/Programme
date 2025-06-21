#include <stdio.h>
#include <string.h>
#include <ctype.h>

// void reverse(char *str)
// {
//     int len = strlen(str);
//     char *start = str;
//     char *end = str + len - 1;
//     while (start < end)
//     {
//         char temp = *start;
//         *start = *end;
//         *end = temp;
//         start ++;
//         end --;
//     }
// }

int main()
{
    FILE *in, *out;
    in = fopen("encrypt.txt", "r");
    out = fopen("output.txt", "w");

    char key[60];
    scanf("%s", key);
    int len = strlen(key);
    int alphabet[26] = {0};
    char origin[10000], encrypted[10000], list[10000];
    for (int i = 0; i < len; i ++)
    {
        alphabet[key[i] - 'a'] ++;
    }
    int cnt = 0;
    for (int i = 0; i < len; i ++)
    {
        if (alphabet[key[i] - 'a'] == 1)
        {
            list[cnt] = key[i];
            cnt ++;
        }
        else if (alphabet[key[i] - 'a'] > 1)
        {
            list[cnt] = key[i];
            cnt ++;
            alphabet[key[i] - 'a'] = 0;
        }
    }
    for (int i = cnt, j = 25; i < 26; i ++, j --)
    {
        if (strchr(list, 'a' + j) == NULL)
        {
            list[i] = 'a' + j;
        }
        else
        {
            i --;
        }
    }
    list[26] = '\0';


    fgets(origin, 10000, in);
    int len_o = strlen(origin);
    
    for (int i = 0; i < len_o; i ++)
    {
        if (islower(origin[i]))
        {
            encrypted[i] = list[origin[i] - 'a'];
        }
        else
        {
            encrypted[i] = origin[i];
        }
    }
    fputs(encrypted, out);

    fclose(in);
    fclose(out);

    return 0;
    
    
}