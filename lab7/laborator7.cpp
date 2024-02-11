#include "../util.h"

int main()
{
	matrix A = { {7, -2, 0},
				 {-2, 6, -2},
				 {0, -2, 5} };

	printv(eigenvaluesOf(A));

	return 0;
}