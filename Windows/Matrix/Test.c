#include "stdio.h"
#include "stdlib.h"
#include "Matrix.h"


int main(void)
{
	HMATRIX hMatrix;

	if ((hMatrix = CreateMatrix(5, 5)) == NULL)
	{
		fprintf(stderr, "can not create matrix\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < hMatrix->rowSize; i++)
		for (int j = 0; j < hMatrix->colSize; j++)
			if ((SetElem(hMatrix, i, j, j)) == FALSE)
			{
				fprintf(stderr, "can not set element\n");
				exit(EXIT_FAILURE);
			}
				
	

	DispMatrix(hMatrix);

	CloseMatrix(hMatrix);

	return 0;
}
