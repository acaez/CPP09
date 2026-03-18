#include <iostream>
#include <vector>
#include <cstdlib>
#include "Span.hpp"

int main(void)
{
    std::cout << "=== Subject test ===" << std::endl;
    Span sp = Span(5);
    sp.addNumber(6);
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);
    std::cout << sp.shortestSpan() << std::endl;
    std::cout << sp.longestSpan() << std::endl;

    std::cout << "=== Full span ===" << std::endl;
    try { sp.addNumber(42); }
    catch (const std::exception &e) { std::cout << "Exception: " << e.what() << std::endl; }

    std::cout << "=== Range fill (10000 numbers) ===" << std::endl;
    std::vector<int> big;
    for (int i = 0; i < 10000; i++)
        big.push_back(i);

    Span sp3(10000);
    sp3.addNumbers(big.begin(), big.end());
    std::cout << "Shortest: " << sp3.shortestSpan() << std::endl;
    std::cout << "Longest:  " << sp3.longestSpan() << std::endl;

    return 0;
}
