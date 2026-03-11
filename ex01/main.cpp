#include <iostream>
#include <string>
#include "Iter.hpp"

template <typename T>
void	print(T const &x)
{
	std::cout << x << " ";
}

void	increment(int &x)
{
	x++;
}

class Awesome
{
public:
	Awesome(int n) : _n(n) {}
	int	getN() const { return _n; }
	void	increment()   { _n++; }

private:
	int _n;
};

std::ostream &operator<<(std::ostream &o, Awesome const &a)
{
	return o << "Awesome(" << a.getN() << ")";
}

void	incrementAwesome(Awesome &a)
{
	a.increment();
}

int	main(void)
{
	std::cout << "=== int array (print) ===" << std::endl;
	int	ints[] = {1, 2, 3, 4, 5};
	::iter(ints, 5, print<int>);
	std::cout << std::endl;

	std::cout << "=== int array (increment then print) ===" << std::endl;
	::iter(ints, 5, increment);
	::iter(ints, 5, print<int>);
	std::cout << std::endl;

	std::cout << "=== const int array (print) ===" << std::endl;
	int const	cints[] = {10, 20, 30};
	::iter(cints, 3, print<int>);
	std::cout << std::endl;

	std::cout << "=== string array (print) ===" << std::endl;
	std::string	strs[] = {"hello", "world", "42"};
	::iter(strs, 3, print<std::string>);
	std::cout << std::endl;

	std::cout << "=== Awesome array (increment then print) ===" << std::endl;
	Awesome	awesomes[] = {Awesome(1), Awesome(2), Awesome(3)};
	::iter(awesomes, 3, incrementAwesome);
	::iter(awesomes, 3, print<Awesome>);
	std::cout << std::endl;

	return 0;
}
