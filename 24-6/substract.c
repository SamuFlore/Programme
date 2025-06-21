#include <stdio.h>
#include <string.h>


int cmp(char num1[], char num2[])//0是num1 < num2，1是num1 > num2, 2是num1 == num2
{
    int len1 = strlen(num1), len2 = strlen(num2);
    if (len1 < len2)
    {
        return 0;
    }
    else if (len1 > len2)
    {
        return 1;
    }
    else
    {
        for (int i = 0; i < len1; i ++)
        {
            if (num1[i] < num2[i])
            {
                return 0;
            }
            else if (num1[i] > num2[i])
            {
                return 1;
            }
        }
        return 2;
    }
}

void remover(char *num)
{
    int i = 0;
    
    while (num[i] == '0' && num[i + 1] != '\0')
    {
        i ++;
    }
    memmove(num, num + i, strlen(num) - i + 1);
}

void substract(int number1[], int number2[], char num1[], char num2[])
{
    int len1 = strlen(num1), len2 = strlen(num2);
    for (int i = len1 - 1, j = len2 - 1, k = len1 - 1; i >= 0 && j >= 0; i --, j --, k --)
    {
        if (number1[i] < number2[j])
        {
            number1[i] = number1[i] + 10 - number2[j];
            number1[i - 1] --;
            int tmp = i;
            while (number1[tmp - 1] < 0)
            {
                number1[tmp - 1] += 10;
                number1[tmp - 2] --;
                tmp --;
            }
        }
        else
        {
            number1[i] = number1[i] - number2[j];
            if (number1[i - 1] < 0)
            {
                number1[i - 1] += 10;
                number1[i - 2] --;
            }
        }
        
    }
    

}

void tonum(char num[], int number[])
{
    int len = strlen(num);
    int i = 0;
    while (i < len)
    {
        number[i] = num[i] - '0';
        i ++;
    }
}

int main()
{
    char num1[20000], num2[20000];

    int number1[20000], number2[20000];

    scanf("%s%s", num1, num2);
    remover(num1);
    remover(num2);
    
    int flag = cmp(num1, num2);
    
    tonum(num1, number1);
    tonum(num2, number2);

    int x = 0, cnt = 0;
    if (flag == 0)//num1 < num2
    {
        substract(number2, number1, num2, num1);
        printf("-");
        for (; x < strlen(num2); x ++)
        {
            if (number2[x] == 0)
            {
                cnt ++;
            }
            else
            {
                break;
            }
        }
        // if (x > 0)
        // {
        //     x --;
        // }
        for (; cnt < strlen(num2); cnt ++)
        {
            printf("%d", number2[cnt]);
        }
           
    }
    
    else if (flag == 1)
    {
        substract(number1, number2, num1, num2);
        
        for (; x < strlen(num1); x ++)
        {
            if (number1[x] == 0)
            {
                cnt ++;
            }
            else
            {
                break;
            }
        }
        // if (x > 0)
        // {
        //     x --;
        // }
        for (; cnt < strlen(num1); cnt ++)
        {
            printf("%d", number1[cnt]);
        }
    }
    else
    {
        printf("0");
    }
    return 0;
}
