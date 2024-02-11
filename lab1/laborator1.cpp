#include "../util.h"

int main()
{
	//Ex1
	std::cout << std::pow((PI / 4), 5) - std::sqrt(2) + log(5) - std::log10(21) + std::pow(2, 11) << '\n';
	
	//Ex2
	complex z1 = { 2, 5 };
	complex z2 = { -3, 1 };
	printc(sumOf(z1, z2));
	printc(productOf(z1, z2));
	printc(divisionOf(z1, z2));
	printc(powc(z1, 7));

	//Ex3
	std::cout << "Introduceti un x:\n";
	double x;
	std::cin >> x;
	std::cout << 2 * std::sin(PI * x) - std::sqrt((std::pow(x, 3) + 1) / 5) << '\n';

	//Ex1
	matrix a = { {1, 2}, 
				 {3, 4} };
	matrix b = { {5, 6}, {7, 9} };
	matrix c = concatCollums(a, b);
	printm(c);

	//Ex3
	std::cout << sumOfElements(a) << '\n';

	//Ex last
	printm(productOf({ {1, 2, 3}, {4, 5, 6} }, { {1, 2}, {3, 4}, {5, 6} }));

	return 0;
}