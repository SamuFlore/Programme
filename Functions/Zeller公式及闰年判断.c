#include <stdio.h>

int isLeapYear(int year)//闰年判断, 1为闰年, 0为平年
{
    return (year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0);
}

int getMonthDays(int year,int month)//获取某个月的天数
{
    switch(month)
    {
        case 1:case 3:case 5:case 7:case 8:case 10:case 12:
        {
            return 31;
            break;
        }
        case 4:case 6:case 9:case 11:
        {
            return 30;
            break;
        }
        case 2:
        {
            if (isLeapYear(year))
            {
                return 29;
                break;
            }
            else
            {
                return 28;
                break;
            }
        }
    }
}

int zeller(int year, int month, int day)//Zeller公式
{
	int c, yoc, w;
    if (month < 3)
    {
        month += 12;
        year -= 1;
    }
    c = year / 100;
    yoc = year % 100;
    w = (c/4 - 2*c + yoc + yoc/4 + (26*(month + 1)/10) + day - 1) % 7;
    w = w < 0 ? w + 7 : w;
	return w;
}