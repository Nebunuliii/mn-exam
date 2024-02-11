#include "../util.h"

int main()
{
	auto func1 = [](double x)
		{
			return std::sin(x);
		};

	auto func2 = [](double x)
		{
			return 1 / (1 + x);
		};

	double i1 = integral(0, PI, func1);
	double i2 = integral(0, 2, func2);

	std::cout << i1 << "\n";
	std::cout << i2 << "\n";

	std::cout << "err1:" << "\n" << std::abs(((i1 - 2) / 2) * 100) << '\n';
	std::cout << "err2:" << "\n" << std::abs(((i2 - 1.0986) / 1.0986) * 100) << '\n';

	return 0;
}