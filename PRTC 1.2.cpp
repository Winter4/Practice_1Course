#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

float denominator(float x, int n)
{
	if (n == 1) return x; // x^1 = x
	else return powf(x, n) + denominator(x, n - 1); // нынешний икс в степени + предыдущий икс в степени
}

float sum(float x, int n)
{
	if (n == 0) return 1; //  x^0 = 1;   1 / 1 = 1
	else return 1 / denominator(x, n) + sum(x, n - 1); // нынешняя дробь + предыдущая дробь с меншим кол-вом иксов
}

int main()
{
	int n;
	float x;

	printf(" Enter x: ");
	scanf("%f", &x);

	printf(" Enter n: ");
	scanf("%d", &n);

/*	float sum = 0;
	for (int i = 1; i <= n; i++) { // кол-во дробей
		float denominator = 0;
		for (int j = 1; j <= i; j++) // количество членов в знаменателе
			denominator += powf(x, j);

		sum += 1 / denominator;
	}
*/

	printf("Sum: %f", sum(x, n));

	printf("\n");
	system("pause");
	return 0;
}
