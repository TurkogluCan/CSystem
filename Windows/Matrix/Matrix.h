#ifndef MATRIX_H_
#define MATRIX_H_

#include "stddef.h"

/* SYMBOLIC CONSTANTS */
#define TRUE	1
#define FALSE	0

/* TYPE DECLARATIONS */

typedef int DATATYPE;
typedef int BOOL;


typedef	struct tagMATRIX 
{
	DATATYPE *pArray;
	size_t    rowSize;
	size_t    colSize;

}MATRIX, *HMATRIX;


/* FUNCTION PROTOTYPES */

HMATRIX CreateMatrix(size_t rowSize, size_t colSize);
void	CloseMatrix(HMATRIX hMatrix);
BOOL	SetElem(HMATRIX hMatrix, size_t row, size_t col, int val);
int		GetElem(HMATRIX hMatrix, size_t row, size_t col);
void	DispMatrix(HMATRIX hMatrix);







#endif // MATRIX_H_
