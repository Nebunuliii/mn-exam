#include "../util.h"

int main()
{
	matrix A = { {1, 1, 1},
				 {1, 2, 3},	
				 {1, 4, 9} };
	printm(inverseOf(A));

	A = { {1, 2, 1, 3, 4},
		  {2, 1, 5, 9, 8},
		  {5 ,0, 6, 4, 3}, 
		  {2, 5, 8, 9, 8},
		  {7, 3, 4, 2, 7} };
	matrix B = { {11}, {25}, {18}, {32}, {23} };
	printm(linearEquation(A, B));

	return 0;
}