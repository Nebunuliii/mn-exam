#include "../util.h"

int main()
{
	auto func1 = [](const double& x)
		{
			return std::log(x) + x;
		};

	auto func2 = [](const double& x)
		{
			return std::sin(x) - std::log(x);
		};

	auto func3 = [](const double& x)
		{
			return std::log(x) - std::exp(-x);
		};

	std::cout << nonlinearEquation(0.05, 2., func1) << '\n';
	std::cout << nonlinearEquation(1., PI, func2) << '\n';
	std::cout << nonlinearEquation(1., 4., func3) << '\n';

	return 0;
}