#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "math.h"

#define Pi 3.1415926535

int main()
{
	printf("\t |    x  ");
	printf(" |   arctg x ");
	printf(" |    sum  ");
	printf(" |  k  |");
	printf("\n\t _________________________________________\n");

	// рекуррентная формула:
	// -x^2 * (k - 0.5)
	// ----------------
	// k + 0.5

	float sum, tmp, pw; // pw - степень
	int k;

	for (float x = Pi / -4.0; x <= Pi / 4.0; x += Pi / 20.0)
	{
		k = 0;
		sum = tmp = 0;
		do {
			pw = 2 * k + 1;
			tmp = (pow(-1.0, k) * (powf(x, pw) / pw));
			sum += tmp;
			k++;
		} while (fabs(tmp) > powf(10, -6.0));

		printf("\t | %6.3f | ", x);
		printf("\t%6.3f | ", atan(x));
		printf("%8.3f | ", sum);
		printf("%3d |\n", k);
	}

	printf("\n\n");
	system("pause");
	return 0;
}