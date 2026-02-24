#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter& other)
{
	(void)other;
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other)
{
	(void)other;
	return *this;
}

ScalarConverter::~ScalarConverter() {}

static bool isCharLiteral(const std::string& literal)
{
	if (literal.length() == 1 && !std::isdigit(literal[0]))
		return true;
	return false;
}

static bool isIntLiteral(const std::string& literal)
{
	if (literal.empty())
		return false;

	size_t i = 0;
	if (literal[0] == '+' || literal[0] == '-')
		i++;
	if (i == literal.length())
		return false;
	for (; i < literal.length(); i++)
    {
		if (!std::isdigit(literal[i]))
			return false;
	}
	return true;
}

static bool isFloatLiteral(const std::string& literal)
{
	if (literal.empty() || literal[literal.length() - 1] != 'f')
		return false;
	std::string withoutF = literal.substr(0, literal.length() - 1);
	if (withoutF.empty())
		return false;
	size_t i = 0;
	bool hasDecimal = false;
	bool hasDigit = false;
	if (withoutF[0] == '+' || withoutF[0] == '-')
		i++;
	if (i == withoutF.length())
		return false;
	for (; i < withoutF.length(); i++)
    {
		if (withoutF[i] == '.')
        {
			if (hasDecimal)
				return false;
			hasDecimal = true;
		}
        else if (std::isdigit(withoutF[i]))
        {
			hasDigit = true;
		}
        else
        {
			return false;
		}
	}
	return hasDecimal && hasDigit;
}

static bool isDoubleLiteral(const std::string& literal)
{
	if (literal.empty())
		return false;
	size_t i = 0;
	bool hasDecimal = false;
	bool hasDigit = false;
	if (literal[0] == '+' || literal[0] == '-')
		i++;
	if (i == literal.length())
		return false;
	for (; i < literal.length(); i++)
    {
		if (literal[i] == '.')
        {
			if (hasDecimal)
				return false;
			hasDecimal = true;
		}
        else if (std::isdigit(literal[i]))
        {
			hasDigit = true;
		}
        else
        {
			return false;
		}
	}
	return hasDecimal && hasDigit;
}

static bool isPseudoLiteral(const std::string& literal)
{
	return (literal == "nan" || literal == "nanf" ||
			literal == "+inf" || literal == "-inf" ||
			literal == "+inff" || literal == "-inff" ||
			literal == "inf" || literal == "inff");
}

static void printChar(double value, bool impossible)
{
	std::cout << "char: ";
	if (impossible || std::isnan(value) || std::isinf(value))
    {
		std::cout << "impossible" << std::endl;
	}
    else if (value < 0 || value > 127)
    {
		std::cout << "impossible" << std::endl;
	}
    else
    {
		int intVal = static_cast<int>(value);
		if (intVal < 32 || intVal > 126)
        {
			std::cout << "Non displayable" << std::endl;
		}
        else
        {
			std::cout << "'" << static_cast<char>(intVal) << "'" << std::endl;
		}
	}
}

static void printInt(double value, bool impossible)
{
	std::cout << "int: ";
	if (impossible || std::isnan(value) || std::isinf(value))
    {
		std::cout << "impossible" << std::endl;
	}
    else if (value < static_cast<double>(INT_MIN) || 
			   value > static_cast<double>(INT_MAX))
    {
		std::cout << "impossible" << std::endl;
	}
    else
    {
		std::cout << static_cast<int>(value) << std::endl;
	}
}

static void printFloat(double value, const std::string& literal)
{
	std::cout << "float: ";
	
	if (literal == "nan" || literal == "nanf")
    {
		std::cout << "nanf" << std::endl;
	}
    else if (literal == "+inf" || literal == "+inff" || 
			   literal == "inf" || literal == "inff")
    {
		std::cout << "+inff" << std::endl;
	}
    else if (literal == "-inf" || literal == "-inff")
    {
		std::cout << "-inff" << std::endl;
	}
    else
    {
		float f = static_cast<float>(value);
		std::cout << std::fixed << std::setprecision(1) << f << "f" << std::endl;
	}
}

static void printDouble(double value, const std::string& literal)
{
	std::cout << "double: ";
	
	if (literal == "nan" || literal == "nanf")
    {
		std::cout << "nan" << std::endl;
	}
    else if (literal == "+inf" || literal == "+inff" || 
			   literal == "inf" || literal == "inff")
    {
		std::cout << "+inf" << std::endl;
	}
    else if (literal == "-inf" || literal == "-inff")
    {
		std::cout << "-inf" << std::endl;
	}
    else
    {
		std::cout << std::fixed << std::setprecision(1) << value << std::endl;
	}
}

void ScalarConverter::convert(const std::string& literal)
{
	if (literal.empty())
    {
		std::cout << "Error: empty input" << std::endl;
		return;
	}
	double value = 0.0;
	bool impossible = false;
	if (isPseudoLiteral(literal))
    {
		if (literal == "nan" || literal == "nanf")
        {
			value = std::numeric_limits<double>::quiet_NaN();
        }
        else if (literal == "+inf" || literal == "+inff" || 
				   literal == "inf" || literal == "inff")
        {
			value = std::numeric_limits<double>::infinity();
		}
        else if (literal == "-inf" || literal == "-inff")
        {
			value = -std::numeric_limits<double>::infinity();
		}
		impossible = true;
	}
	else if (isCharLiteral(literal))
    {
		value = static_cast<double>(literal[0]);
	}
	else if (isIntLiteral(literal))
    {
		long long ll = std::atoll(literal.c_str());
		if (ll < INT_MIN || ll > INT_MAX)
        {
			impossible = true;
		}
		value = static_cast<double>(ll);
	}
	else if (isFloatLiteral(literal))
    {
		std::string withoutF = literal.substr(0, literal.length() - 1);
		value = std::atof(withoutF.c_str());
	}
	else if (isDoubleLiteral(literal))
    {
		value = std::atof(literal.c_str());
	}
	else
    {
		std::cout << "Error: invalid literal" << std::endl;
		return;
	}
	printChar(value, impossible);
	printInt(value, impossible);
	printFloat(value, literal);
	printDouble(value, literal);
}
