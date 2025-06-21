#include <stdio.h>



int main()
{
    int chessboard[19][19];

    for (int i = 0; i < 19; i ++)
    {
        for (int j = 0; j < 19; j ++)
        {
            scanf("%d", &chessboard[i][j]);
        }
    }

    int flag = 0;
    for (int i = 0; i < 19; i ++)
    {
        for (int j = 0; j < 19; j ++)
        {
            if (chessboard[i][j] == 1)
            {
                if (j > 0 && j < 15 && chessboard[i][j+1] == 1 && chessboard[i][j+2] == 1 && chessboard[i][j+3] == 1)//横排4个
                {
                    if ((chessboard[i][j-1] == 0 && chessboard[i][j+4] == 0) || (chessboard[i][j-1] == 2 && chessboard[i][j+4] == 0) || (chessboard[i][j-1] == 0 && chessboard[i][j+4] == 2))
                    {
                        printf("1:%d,%d\n", i+1, j+1);
                        flag = 1;
                        break;
                    }
                }
                else if (j == 0 && chessboard[i][j+1] == 1 && chessboard[i][j+2] == 1 && chessboard[i][j+3] == 1 && chessboard[i][j+4] == 0)
                {
                    printf("1:%d,%d\n", i+1, j+1);
                    flag = 1;
                    break;
                }
                else if (j == 15 && chessboard[i][j+1] == 1 && chessboard[i][j+2] == 1 && chessboard[i][j+3] == 1 && chessboard[i][j-1] == 0)
                {
                    printf("1:%d,%d\n", i+1, j+1);
                    flag = 1;
                    break;
                }
                
                
                if (i > 0 && i < 15 && chessboard[i+1][j] == 1 && chessboard[i+2][j] == 1 && chessboard[i+3][j] == 1)//竖排4个
                {
                    if ((chessboard[i-1][j] == 0 && chessboard[i+4][j] == 0) || (chessboard[i-1][j] == 2 && chessboard[i+4][j] == 0) || (chessboard[i-1][j] == 0 && chessboard[i+4][j] == 2))
                    {
                        printf("1:%d,%d\n", i+1, j+1);
                        flag = 1;
                        break;
                    }
                }
                else if (i == 0 && chessboard[i+1][j] == 1 && chessboard[i+2][j] == 1 && chessboard[i+3][j] == 1 && chessboard[i+4][j] == 0)
                {
                    printf("1:%d,%d\n", i+1, j+1);
                    flag = 1;
                    break;
                }
                else if (i == 15 && chessboard[i+1][j] == 1 && chessboard[i+2][j] == 1 && chessboard[i+3][j] == 1 && chessboard[i-1][j] == 0)
                {
                    printf("1:%d,%d\n", i+1, j+1);
                    flag = 1;
                    break;
                }

                if (j > 0 && j < 15 && i > 0 && i < 15 && chessboard[i+1][j+1] == 1 && chessboard[i+2][j+2] == 1 && chessboard[i+3][j+3] == 1)//右下4个
                {
                    if ((chessboard[i-1][j-1] == 0 && chessboard[i+4][j+4] == 0) || (chessboard[i-1][j-1] == 2 && chessboard[i+4][j+4] == 0) || (chessboard[i-1][j-1] == 0 && chessboard[i+4][j+4] == 2))
                    {
                        printf("1:%d,%d\n", i+1, j+1);
                        flag = 1;
                        break;
                    }
                }
                else if (((j == 0 && i > 0 && i < 15) || (i == 0 && j > 0 && j < 15) || (i == 0 && j == 0)) && chessboard[i+1][j+1] == 1 && chessboard[i+2][j+2] == 1 && chessboard[i+3][j+3] == 1 && chessboard[i+4][j+4] == 0)
                {
                    printf("1:%d,%d\n", i+1, j+1);
                    flag = 1;
                    break;
                }
                else if (((j == 15 && i > 0 && i < 15) || (i == 15 && j > 0 && j < 15) || (i == 15 && j == 15)) && chessboard[i+1][j+1] == 1 && chessboard[i+2][j+2] == 1 && chessboard[i+3][j+3] == 1 && chessboard[i-1][j-1] == 0)
                {
                    printf("1:%d,%d\n", i+1, j+1);
                    flag = 1;
                    break;
                }

                if (j > 3 && j < 18 && i > 0 && i < 15 && chessboard[i+1][j-1] == 1 && chessboard[i+2][j-2] == 1 && chessboard[i+3][j-3] == 1)//左下4个
                {
                    if ((chessboard[i-1][j+1] == 0 && chessboard[i+4][j-4] == 0) || (chessboard[i-1][j+1] == 2 && chessboard[i+4][j-4] == 0) || (chessboard[i-1][j+1] == 0 && chessboard[i+4][j-4] == 2))
                    {
                        printf("1:%d,%d\n", i+1, j+1);
                        flag = 1;
                        break;
                    }
                }
                else if (((j == 18 && i > 0 && i < 15) || (i == 0 && j > 3 && j < 18) || (i == 0 && j == 18)) && chessboard[i+1][j-1] == 1 && chessboard[i+2][j-2] == 1 && chessboard[i+3][j-3] == 1 && chessboard[i+4][j-4] == 0)
                {
                    printf("1:%d,%d\n", i+1, j+1);
                    flag = 1;
                    break;
                }
                else if (((j == 3 && i > 0 && i < 15) || (i == 15 && j > 3 && j < 18) || (i == 15 && j == 3)) && chessboard[i+1][j-1] == 1 && chessboard[i+2][j-2] == 1 && chessboard[i+3][j-3] == 1 && chessboard[i-1][j+1] == 0)
                {
                    printf("1:%d,%d\n", i+1, j+1);
                    flag = 1;
                    break;
                }

            }

            else if (chessboard[i][j] == 2)
            {
                if (j > 0 && j < 15 && chessboard[i][j+1] == 2 && chessboard[i][j+2] == 2 && chessboard[i][j+3] == 2)//横排4个
                {
                    if ((chessboard[i][j-1] == 0 && chessboard[i][j+4] == 0) || (chessboard[i][j-1] == 1 && chessboard[i][j+4] == 0) || (chessboard[i][j-1] == 0 && chessboard[i][j+4] == 1))
                    {
                        printf("2:%d,%d\n", i+1, j+1);
                        flag = 1;
                        break;
                    }
                }
                else if (j == 0 && chessboard[i][j+1] == 2 && chessboard[i][j+2] == 2 && chessboard[i][j+3] == 2 && chessboard[i][j+4] == 0)
                {
                    printf("2:%d,%d\n", i+1, j+1);
                    flag = 1;
                    break;
                }
                else if (j == 15 && chessboard[i][j+1] == 2 && chessboard[i][j+2] == 2 && chessboard[i][j+3] == 2 && chessboard[i][j-1] == 0)
                {
                    printf("2:%d,%d\n", i+1, j+1);
                    flag = 1;
                    break;
                }


                if (i > 0 && i < 15 && chessboard[i+1][j] == 2 && chessboard[i+2][j] == 2 && chessboard[i+3][j] == 2)//竖排4个
                {
                    if ((chessboard[i-1][j] == 0 && chessboard[i+4][j] == 0) || (chessboard[i-1][j] == 1 && chessboard[i+4][j] == 0) || (chessboard[i-1][j] == 0 && chessboard[i+4][j] == 1))
                    {
                        printf("2:%d,%d\n", i+1, j+1);
                        flag = 1;
                        break;
                    }
                }
                else if (i == 0 && chessboard[i+1][j] == 2 && chessboard[i+2][j] == 2 && chessboard[i+3][j] == 2 && chessboard[i+4][j] == 0)
                {
                    printf("2:%d,%d\n", i+1, j+1);
                    flag = 1;
                    break;
                }
                else if (i == 15 && chessboard[i+1][j] == 2 && chessboard[i+2][j] == 2 && chessboard[i+3][j] == 2 && chessboard[i-1][j] == 0)
                {
                    printf("2:%d,%d\n", i+1, j+1);
                    flag = 1;
                    break;
                }


                if (j > 0 && j < 15 && i > 0 && i < 15 && chessboard[i+1][j+1] == 2 && chessboard[i+2][j+2] == 2 && chessboard[i+3][j+3] == 2)//右下4个
                {
                    if ((chessboard[i-1][j-1] == 0 && chessboard[i+4][j+4] == 0) || (chessboard[i-1][j-1] == 1 && chessboard[i+4][j+4] == 0) || (chessboard[i-1][j-1] == 0 && chessboard[i+4][j+4] == 1))
                    {
                        printf("2:%d,%d\n", i+1, j+1);
                        flag = 1;
                        break;
                    }
                }
                else if (((j == 0 && i > 0 && i < 15) || (i == 0 && j > 0 && j < 15) || (i == 0 && j == 0)) && chessboard[i+1][j+1] == 2 && chessboard[i+2][j+2] == 2 && chessboard[i+3][j+3] == 2 && chessboard[i+4][j+4] == 0)
                {
                    printf("2:%d,%d\n", i+1, j+1);
                    flag = 1;
                    break;
                }
                else if (((j == 15 && i > 0 && i < 15) || (i == 15 && j > 0 && j < 15) || (i == 15 && j == 15)) && chessboard[i+1][j+1] == 2 && chessboard[i+2][j+2] == 2 && chessboard[i+3][j+3] == 2 && chessboard[i-1][j-1] == 0)
                {
                    printf("2:%d,%d\n", i+1, j+1);
                    flag = 1;
                    break;
                }


                if (j > 3 && j < 18 && i > 0 && i < 15 && chessboard[i+1][j-1] == 2 && chessboard[i+2][j-2] == 2 && chessboard[i+3][j-3] == 2)//左下4个
                {
                    if ((chessboard[i-1][j+1] == 0 && chessboard[i+4][j-4] == 0) || (chessboard[i-1][j+1] == 1 && chessboard[i+4][j-4] == 0) || (chessboard[i-1][j+1] == 0 && chessboard[i+4][j-4] == 1))
                    {
                        printf("2:%d,%d\n", i+1, j+1);
                        flag = 1;
                        break;
                    }
                }
                else if (((j == 18 && i > 0 && i < 15) || (i == 0 && j > 3 && j < 18) || (i == 0 && j == 18)) && chessboard[i+1][j-1] == 2 && chessboard[i+2][j-2] == 2 && chessboard[i+3][j-3] == 2 && chessboard[i+4][j-4] == 0)
                {
                    printf("2:%d,%d\n", i+1, j+1);
                    flag = 1;
                    break;
                }
                else if (((j == 3 && i > 0 && i < 15) || (i == 15 && j > 3 && j < 18) || (i == 15 && j == 3)) && chessboard[i+1][j-1] == 2 && chessboard[i+2][j-2] == 2 && chessboard[i+3][j-3] == 2 && chessboard[i-1][j+1] == 0)
                {
                    printf("2:%d,%d\n", i+1, j+1);
                    flag = 1;
                    break;
                }
            }

        }
    }

    if (!flag)
    {
        printf("No\n");
    }
    return 0;
}