#include <iostream>
#include <string>
#include "Array.hpp"

template <typename T>

void	printArray(Array<T> const &arr)
{
	for (unsigned int i = 0; i < arr.size(); i++)
		std::cout << "[" << i << "] = " << arr[i] << std::endl;
}

int	main(void)
{
	std::cout << "=== Empty array ===" << std::endl;
	Array<int>	empty;
	std::cout << "size = " << empty.size() << std::endl;

	std::cout << "\n=== int array (n=5, default init) ===" << std::endl;
	Array<int>	ints(5);
	std::cout << "size = " << ints.size() << std::endl;
	printArray(ints);  // Doit afficher des 0 (initialisation par défaut)

	std::cout << "\n=== Fill and access ===" << std::endl;
	for (unsigned int i = 0; i < ints.size(); i++)
		ints[i] = (int)(i * 10);
	printArray(ints);

	std::cout << "\n=== Deep copy (copy constructor) ===" << std::endl;
	Array<int>	copy(ints);
	copy[0] = 999;
	std::cout << "original[0] = " << ints[0] << " (must be 0, not 999)" << std::endl;
	std::cout << "copy[0]     = " << copy[0] << std::endl;

	std::cout << "\n=== Deep copy (operator=) ===" << std::endl;
	Array<int>	assigned;
	assigned = ints;
	assigned[1] = 777;
	std::cout << "original[1] = " << ints[1] << " (must be 10, not 777)" << std::endl;
	std::cout << "assigned[1] = " << assigned[1] << std::endl;

	std::cout << "\n=== Out of bounds exception ===" << std::endl;
	try
	{
		std::cout << ints[42] << std::endl;
	}
	catch (std::exception const &e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n=== Empty array access ===" << std::endl;
	try
	{
		std::cout << empty[0] << std::endl;
	}
	catch (std::exception const &e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n=== string array ===" << std::endl;
	Array<std::string>	strs(3);
	strs[0] = "hello";
	strs[1] = "world";
	strs[2] = "42";
	printArray(strs);

	return 0;
}
