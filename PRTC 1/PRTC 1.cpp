#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

int main()
{
	int n;
	float x;

	printf(" Enter x: ");
	scanf("%f", &x);

	printf(" Enter n: ");
	scanf("%d", &n);

	float sum = 0;
	for (int i = 1; i <= n; i++) { // кол-во дробей
		float denom = 0;
		for (int j = 1; j <= i; j++) // количество членов в знаменателе
			denom += powf(x, j);
		
		sum += 1 / denom;
	}

	printf("Sum: %f", sum);

	printf("\n");
	system("pause");
	return 0;
}
