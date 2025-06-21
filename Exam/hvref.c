#include <stdio.h>
#include <string.h>

int main()
{
    char context[11000];
    char ref[110][50];
    int cnt = 0;
    fgets(context, 10000, stdin);
    int len = strlen(context);
    for (int i = 0; i < len; i ++)
    {
        if (context[i] == '(')
        {
            char tmp[50] = {0};
            int num = 0;
            i ++;
            while (context[i] != ')')
            {
                tmp[num] = context[i];
                i ++;
                num ++;
            }
            int flag = 0;
            for (int j = 0; j < cnt; j ++)
            {
                if (strcmp(tmp, ref[j]) == 0)
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
            {
                strcpy(ref[cnt], tmp);
                cnt ++;
            }
        }
    }
    for (int i = 0; i < cnt; i ++)
    {
        char name[40] = {0};
        int year = 0;
        sscanf(ref[i], "%s%d", name, &year);
        int len = strlen(name);
        name[len - 1] = '\0';
        printf("%s %d\n", name, year);
    }
    return 0;
}