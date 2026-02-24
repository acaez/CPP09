#include "Functions.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
	std::srand(std::time(NULL));
	std::cout << "=== Testing with generate() ===" << std::endl;
	for (int i = 0; i < 5; i++)
    {
		Base* ptr = generate();
		std::cout << "Object " << i + 1 << ": ";
		std::cout << "identify(ptr) = ";
		identify(ptr);
		std::cout << "           identify(ref) = ";
		identify(*ptr);
		delete ptr;
		std::cout << std::endl;
	}
	std::cout << "=== Testing with known types ===" << std::endl;
	Base* a = new A();
	Base* b = new B();
	Base* c = new C();
	std::cout << "A pointer: ";
	identify(a);
	std::cout << "A reference: ";
	identify(*a);
	std::cout << std::endl;
	std::cout << "B pointer: ";
	identify(b);
	std::cout << "B reference: ";
	identify(*b);
	std::cout << std::endl;
	std::cout << "C pointer: ";
	identify(c);
	std::cout << "C reference: ";
	identify(*c);
	delete a;
	delete b;
	delete c;
	return 0;
}
