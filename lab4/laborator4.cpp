#include "../util.h"

int main()
{
	vector x = { 1., 2., 3., 4., 5., 6., 7., 8., 9., 10. };
	vector y = { 9., 8., 5., 8., 4., 6., 2., 3., 5., 1. };
	vector xp = { 1.25, 5.63, 9.8, 4.24, 7.31 };

	printv(interpolation(x, y, xp));

	return 0;
}