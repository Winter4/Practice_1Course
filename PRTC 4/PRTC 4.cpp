#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

struct matrix { // матрица
	int rows;
	int cols;
	float** values;
};

float** AllocMemoryForMatrix(int rows, int cols) // выделение памяти под матрицу
{
	float** matrix = new float* [rows];
	for (int i = 0; i < rows; i++)
		matrix[i] = new float[cols];

	return matrix;
}

void EnterMatrixSize(int* rows, int* cols, char matrixName) // ввод размеров матрицы
{
	do {
		printf(" Enter the size of matrix '%c': ", matrixName);
		scanf("%i%i", rows, cols);
	} while (*rows < 1 && *cols < 1);
}

void FreeMatrixMemory(matrix* M) // очистка памяти матрицы
{
	for (int i = 0; i < M->rows; i++)
		delete[] M->values[i];
	delete[] M->values;
}

void RandomMatrixValues(matrix* M) // рандом значений матрицы
{
	for (int i = 0; i < M->rows; i++)
		for (int j = 0; j < M->cols; j++)
			M->values[i][j] = -10.0 + 20.0 * rand() / RAND_MAX;
}

void PrintMatrix(matrix M) // печать матрицы
{
	for (int i = 0; i < M.rows; i++) {
		for (int j = 0; j < M.cols; j++)
			printf("%8.1f", M.values[i][j]);
		printf("\n");
	}
}

void MakeMatrixesMultiplyable(matrix* matrix1, matrix* matrix2) // сделать матрицы умножаемыми
{
	int newRows2 = matrix2->rows, newCols1 = matrix1->cols; // будущие новые размеры матриц
	if (matrix1->cols != matrix2->rows)  // подгоняем размеры матриц
		if (matrix1->cols > matrix2->rows)
			do {
				newRows2++;
			} while (newRows2 != matrix1->cols);
		else 
			do {
				newCols1++;
			} while (newCols1 != matrix2->rows);

	//----------------------------------------------------------------------------------------------

	matrix matrix1_new;					// создаём дублёр 1й матрицы
	matrix1_new.rows = matrix1->rows;
	matrix1_new.cols = newCols1;
	matrix1_new.values = AllocMemoryForMatrix(matrix1_new.rows, matrix1_new.cols);

	for (int i = 0; i < matrix1_new.rows; i++) // приводим новую матрицу к единицам
		for (int j = 0; j < matrix1_new.cols; j++)
			matrix1_new.values[i][j] = 1;

	for (int i = 0; i < matrix1->rows; i++) // сохраняем значения из старой матрицы
		for (int j = 0; j < matrix1->cols; j++)
			matrix1_new.values[i][j] = matrix1->values[i][j];

	FreeMatrixMemory(matrix1); // перевыделяем память под исходную матрицу
	matrix1->values = AllocMemoryForMatrix(matrix1_new.rows, matrix1_new.cols);
	matrix1->rows = matrix1_new.rows;
	matrix1->cols = matrix1_new.cols;

	for (int i = 0; i < matrix1->rows; i++) // переносим сохраненные значения в исходную матрицу 
		for (int j = 0; j < matrix1->cols; j++)
			matrix1->values[i][j] = matrix1_new.values[i][j];

	FreeMatrixMemory(&matrix1_new);

	// ------------------------------------------------------------

	matrix matrix2_new;					// создаём дублёр 2й матрицы
	matrix2_new.rows = newRows2;
	matrix2_new.cols = matrix2->cols;
	matrix2_new.values = AllocMemoryForMatrix(matrix2_new.rows, matrix2_new.cols);

	for (int i = 0; i < matrix2_new.rows; i++) // приводим новую матрицу к единицам
		for (int j = 0; j < matrix2_new.cols; j++)
			matrix2_new.values[i][j] = 1;

	for (int i = 0; i < matrix2->rows; i++) // сохраняем значения из старой матрицы
		for (int j = 0; j < matrix2->cols; j++)
			matrix2_new.values[i][j] = matrix2->values[i][j];

	FreeMatrixMemory(matrix2);	// перевыделяем память под исходную матрицу
	matrix2->values = AllocMemoryForMatrix(matrix2_new.rows, matrix2_new.cols);
	matrix2->rows = matrix2_new.rows;
	matrix2->cols = matrix2_new.cols;

	for (int i = 0; i < matrix2->rows; i++) // переносим сохраненные значения в исходную матрицу 
		for (int j = 0; j < matrix2->cols; j++)
			matrix2->values[i][j] = matrix2_new.values[i][j];

	FreeMatrixMemory(&matrix2_new);
}

matrix MultiplyTwoMatrixes(matrix matrix1, matrix matrix2)
{
	matrix M = {};
	M.rows = matrix1.rows;
	M.cols = matrix2.cols;

	M.values = AllocMemoryForMatrix(M.rows, M.cols);

	for (int i = 0; i < M.rows; i++)
		for (int j = 0; j < M.cols; j++) {
			M.values[i][j] = 0;
			for (int k = 0; k < M.rows; k++)
				M.values[i][j] += matrix1.values[i][k] * matrix2.values[k][j];
		}

	return M;
}

matrix* MultiplyMatrixByFloat(matrix* M, float k) 
{
	for (int i = 0; i < M->rows; i++)
		for (int j = 0; j < M->cols; j++)
			M->values[i][j] *= k;

	return M;
}

void MakeMatrixesAddableDeductable(matrix* matrix1, matrix* matrix2)
{
	int newRows1 = matrix1->rows, newCols1 = matrix1->cols, newRows2 = matrix2->rows, newCols2 = matrix2->cols; // будущие новые размеры матриц
	if (matrix1->rows != matrix2->rows)	// увеличиваем строки
		if (matrix1->rows > matrix2->rows)
			do {
				newRows2++;
			} while (newRows2 != matrix1->rows);
		else
			do {
				newRows1++;
			} while (newRows1 != matrix2->rows);

	if (matrix1->cols != matrix2->cols)	// увеличиваем столбцы
		if (matrix1->cols > matrix2->cols)
			do {
				newCols2++;
			} while (newCols2 != matrix1->cols);
		else
			do {
				newCols1++;
			} while (newCols1 != matrix2->cols);

	//----------------------------------------------------------------------------------------------------

	matrix matrix1_new;					// создаём дублёр 1й матрицы
	matrix1_new.rows = newRows1;
	matrix1_new.cols = newCols1;
	matrix1_new.values = AllocMemoryForMatrix(matrix1_new.rows, matrix1_new.cols);

	for (int i = 0; i < matrix1_new.rows; i++) // приводим новую матрицу к единицам
		for (int j = 0; j < matrix1_new.cols; j++)
			matrix1_new.values[i][j] = 1;

	for (int i = 0; i < matrix1->rows; i++) // сохраняем значения из старой матрицы
		for (int j = 0; j < matrix1->cols; j++)
			matrix1_new.values[i][j] = matrix1->values[i][j];

	FreeMatrixMemory(matrix1); // перевыделяем память под исходную матрицу
	matrix1->values = AllocMemoryForMatrix(matrix1_new.rows, matrix1_new.cols);
	matrix1->rows = matrix1_new.rows;
	matrix1->cols = matrix1_new.cols;

	for (int i = 0; i < matrix1->rows; i++) // переносим сохраненные значения в исходную матрицу 
		for (int j = 0; j < matrix1->cols; j++)
			matrix1->values[i][j] = matrix1_new.values[i][j];

	FreeMatrixMemory(&matrix1_new);

	// ---------------------------------------------------------------------

	matrix matrix2_new;					// создаём дублёр 2й матрицы
	matrix2_new.rows = newRows2;
	matrix2_new.cols = newCols2;
	matrix2_new.values = AllocMemoryForMatrix(matrix2_new.rows, matrix2_new.cols);

	for (int i = 0; i < matrix2_new.rows; i++) // приводим матрицу к единицам
		for (int j = 0; j < matrix2_new.cols; j++)
			matrix2_new.values[i][j] = 1;

	for (int i = 0; i < matrix2->rows; i++) // переносим значения из старой матрицы
		for (int j = 0; j < matrix2->cols; j++)
			matrix2_new.values[i][j] = matrix2->values[i][j];

	FreeMatrixMemory(matrix2);	// перевыделяем память под исходную матрицу
	matrix2->values = AllocMemoryForMatrix(matrix2_new.rows, matrix2_new.cols);
	matrix2->rows = matrix2_new.rows;
	matrix2->cols = matrix2_new.cols;

	for (int i = 0; i < matrix2->rows; i++) // переносим сохраненные значения в исходную матрицу 
		for (int j = 0; j < matrix2->cols; j++)
			matrix2->values[i][j] = matrix2_new.values[i][j];

	FreeMatrixMemory(&matrix2_new);
}

matrix AddTwoMatrixes(matrix matrix1, matrix matrix2)
{
	for (int i = 0; i < matrix1.rows; i++)
		for (int j = 0; j < matrix1.cols; j++)
			matrix1.values[i][j] += matrix2.values[i][j];

	return matrix1;
}

matrix DeductTwoMatrixes(matrix matrix1, matrix matrix2)
{
	for (int i = 0; i < matrix1.rows; i++)
		for (int j = 0; j < matrix1.cols; j++)
			matrix1.values[i][j] -= matrix2.values[i][j];

	return matrix1;
}

int main()
{
	matrix matrixA, matrixB, matrixC, matrixAplsB, matrixCA; // объявление матриц

	EnterMatrixSize(&matrixA.rows, &matrixA.cols, 'A'); // ввод размеров матриц
	EnterMatrixSize(&matrixB.rows, &matrixB.cols, 'B');
	EnterMatrixSize(&matrixC.rows, &matrixC.cols, 'C');

	matrixA.values = AllocMemoryForMatrix(matrixA.rows, matrixA.cols), // выделение памяти под матрицы
	matrixB.values = AllocMemoryForMatrix(matrixB.rows, matrixB.cols),
	matrixC.values = AllocMemoryForMatrix(matrixC.rows, matrixC.cols);

	RandomMatrixValues(&matrixA); // рандомим элементы матриц
	RandomMatrixValues(&matrixB);
	RandomMatrixValues(&matrixC);

	printf("\nMatrix A: \n");
	PrintMatrix(matrixA); // выводим матрицы на экран
	printf("\nMatrix B: \n");
	PrintMatrix(matrixB);
	printf("\nMatrix C: \n");
	PrintMatrix(matrixC);

	matrix matrix2A; // создаём 2А
	matrix2A.rows = matrixA.rows;
	matrix2A.cols = matrixA.cols;
	matrix2A.values = AllocMemoryForMatrix(matrix2A.rows, matrix2A.cols);

	for (int i = 0; i < matrixA.rows; i++) // копируем матрицу А
		for (int j = 0; j < matrixA.cols; j++)
			matrix2A.values[i][j] = matrixA.values[i][j];

	MultiplyMatrixByFloat(&matrix2A, 2.0); // 2A
	printf("\nMatrix 2A: \n");
	PrintMatrix(matrix2A);

	MultiplyMatrixByFloat(&matrixB, 3.0); // 3B
	printf("\nMatrix 3B: \n");
	PrintMatrix(matrixB);

	if (matrix2A.rows != matrixB.rows || matrix2A.cols != matrixB.cols) {
		MakeMatrixesAddableDeductable(&matrix2A, &matrixB); // prepare for 2A + 3B
		printf("\n Matrixes 2A & 3B are now addable. \n");

		printf("\nMatrix 2A: \n");
		PrintMatrix(matrix2A);
		printf("\nMatrix 3B: \n");
		PrintMatrix(matrixB);
	}

	matrixAplsB = AddTwoMatrixes(matrix2A, matrixB); // 2A + 3B;
	printf("\nMatrix 2A + 3B: \n");
	PrintMatrix(matrixAplsB);

	if (matrixC.cols != matrixA.rows) {
		MakeMatrixesMultiplyable(&matrixC, &matrixA); // prepare for CA
		printf("\n Matrixes C & A are now multiplyable. \n");

		printf("\nMatrix new C: \n");
		PrintMatrix(matrixC);
		printf("\nMatrix new A: \n");
		PrintMatrix(matrixA);
	}

	matrixCA = MultiplyTwoMatrixes(matrixC, matrixA); // CA;
	printf("\nMatrix CA: \n");
	PrintMatrix(matrixCA);
	
	if (matrixAplsB.rows != matrixCA.rows || matrixAplsB.cols != matrixCA.cols) {
		MakeMatrixesAddableDeductable(&matrixAplsB, &matrixCA); // prepare for 2A + 3B - CA
		printf("\n Matrixes 2A + 3B & CA are now deductable \n");

		printf("\nMatrix  new 2A + 3B: \n");
		PrintMatrix(matrixAplsB);
		printf("\nMatrix new CA: \n");
		PrintMatrix(matrixCA);
	}

	printf("\nMatrix 2A + 3B - CA: \n");
	PrintMatrix(DeductTwoMatrixes(matrixAplsB, matrixCA));

	FreeMatrixMemory(&matrixA); // удаляем матрицы
	FreeMatrixMemory(&matrixB);
	FreeMatrixMemory(&matrixC);

	printf("\n\n");
	system("pause");
	return 0;
}
