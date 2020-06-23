﻿#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

int main()
{
    int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    char date[11];
    printf("Enter the date (xx.yy.zzzz): ");
    gets_s(date);
    
    int day, month, year;
    day = atoi(strtok(date, "."));
    month = atoi(strtok(0, "."));
    year = atoi(strtok(0, "."));

    if (year % 4 == 0) days[1]++; // високосный год
    int monthQNum = month % 3; // номер месяца в квартале
    if (monthQNum == 0) monthQNum = 3; // если 0, значит 3й месяц квартала
    printf(" QNum: %d \n", monthQNum);

    int daysLeft = days[month - 1] - day; // кол-во дней до конца месяца
    for (int i = month - 1; i < month + (2 - monthQNum); i++) // добавляем дни оставшихся месяцев
        daysLeft += days[i];

    printf(" Days left: %d", daysLeft);

    printf("\n");
    system("pause");
    return 0;
}
