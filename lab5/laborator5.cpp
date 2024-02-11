#include "../util.h"

int main()
{
	auto func1 = [](double x)
		{
			return 2 + 3 * x + std::pow(x, 2);
		};

	auto func2 = [](double x)
		{
			return 1 + 5 * x + 2 * std::pow(x, 2) + 4 * std::pow(x, 3);
		};

	std::cout << derivative(2., 0.1, func1) << '\n';
	std::cout << derivative(2., 0.00001, func1) << '\n';

	std::cout << derivative2(3., 0.2, func2) << '\n';
	std::cout << derivative2(3., 0.000002, func2) << '\n';

	return 0;
}