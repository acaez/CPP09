#include "RPN.hpp"

#include <iostream>
#include <sstream>

RPN::RPN() {}

RPN::RPN(const RPN &other) : _stack(other._stack) {}

RPN &RPN::operator=(const RPN &other)
{
	if (this != &other)
		_stack = other._stack;
	return *this;
}

RPN::~RPN() {}

bool	RPN::_isOperator(char c) const
{
	return c == '+' || c == '-' || c == '*' || c == '/';
}

bool	RPN::_applyOperator(char op)
{
	if (_stack.size() < 2)
		return false;
	int b = _stack.top(); _stack.pop();
	int a = _stack.top(); _stack.pop();
	if (op == '/' && b == 0)
	{
		std::cerr << "Error: division by zero." << std::endl;
		return false;
	}
	switch (op)
	{
		case '+': _stack.push(a + b); break;
		case '-': _stack.push(a - b); break;
		case '*': _stack.push(a * b); break;
		case '/': _stack.push(a / b); break;
	}
	return true;
}


bool	RPN::evaluate(const std::string &expression)
{
	std::istringstream ss(expression);
	std::string token;

	while (ss >> token)
	{
		if (token.size() == 1 && _isOperator(token[0]))
		{
			if (!_applyOperator(token[0]))
			{
				std::cerr << "Error" << std::endl;
				return false;
			}
		}
		else if (token.size() == 1 && token[0] >= '0' && token[0] <= '9')
		{
			_stack.push(token[0] - '0');
		}
		else
		{
			std::cerr << "Error" << std::endl;
			return false;
		}
	}
	if (_stack.size() != 1)
	{
		std::cerr << "Error" << std::endl;
		return false;
	}
	std::cout << _stack.top() << std::endl;
	return true;
}
