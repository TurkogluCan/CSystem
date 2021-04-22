#include "stdio.h"
#include "stdlib.h"
#include "Matrix.h"



HMATRIX CreateMatrix(size_t rowSize, size_t colSize)
{
	HMATRIX hMatrix;																					/* Pointer struct yaratildigi icin alan tahsis edilmeli */
																										/* Normal struct yaratilsa malloc'a gerek yoktu */
	if ((hMatrix = (HMATRIX)malloc(sizeof(MATRIX))) == NULL)
		return NULL;

	if ((hMatrix->pArray = (DATATYPE *)malloc(rowSize * colSize * sizeof(DATATYPE))) == NULL)
	{
		free(hMatrix);
		return NULL;
	}

	hMatrix->rowSize = rowSize;
	hMatrix->colSize = colSize;


	return hMatrix;
}


void CloseMatrix(HMATRIX hMatrix)
{
	free(hMatrix->pArray);
	free(hMatrix);
}


BOOL SetElem(HMATRIX hMatrix, size_t row, size_t col, int val)
{
	if (hMatrix->rowSize <= row || hMatrix->colSize <= col)
		return FALSE;

	hMatrix->pArray[row * hMatrix->colSize + col] = val;
	
	return TRUE;
}


int GetElem(HMATRIX hMatrix, size_t row, size_t col)
{
	return hMatrix->pArray[row * hMatrix->colSize + col];
}


void DispMatrix(HMATRIX hMatrix)
{
	size_t i, j;

	for (i = 0; i < hMatrix->rowSize; i++) {
		for (j = 0; j < hMatrix->colSize; j++) 	
			printf("%d " , GetElem(hMatrix, i, j));
		printf("\n");
	}
}










/*
	c1	c2	c3	c4
r1	w	w	w	w
r2	w	w	w	w
r3	w	w	w	w

	c1	c2	c3	c4
r1	a	a+1	a+2	 a+3
r2	a+4	a+5	a+6	 a+7
r3	a+8	a+9	a+10 a+11

	Burada uygun indexe eleman yazdirabilmek icin; 
		Yazilacak olan satir numarasi sutun sayisi ile carpilir ve
		yazilacak olan sutun numarasi hesaba eklenir. Boylece cakisma 
		engellenmis olur.

	ORN:
	r = 1;
	c = 1;
	csize = 4;
	-------------> idx = 5
	r = 2;
	c = 1;
	csize = 4;
	-------------> idx = 9
	r = 1;
	c = 2;
	csize = 4;
	-------------> idx = 6

*/




