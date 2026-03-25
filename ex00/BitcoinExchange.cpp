#include "BitcoinExchange.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>


BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _db(other._db) {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
		_db = other._db;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

bool	BitcoinExchange::_isLeapYear(int year) const
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool	BitcoinExchange::_isValidDate(const std::string &date) const
{
	if (date.size() != 10)
		return false;
	if (date[4] != '-' || date[7] != '-')
		return false;
	for (int i = 0; i < 10; ++i)
	{
		if (i == 4 || i == 7) continue;
		if (date[i] < '0' || date[i] > '9')
			return false;
	}
	int year  = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day   = std::atoi(date.substr(8, 2).c_str());
	if (year < 1 || month < 1 || month > 12 || day < 1)
		return false;
	int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (_isLeapYear(year))
		daysInMonth[1] = 29;
	return day <= daysInMonth[month - 1];
}

float	BitcoinExchange::_getRate(const std::string &date) const
{
	std::map<std::string, float>::const_iterator it = _db.lower_bound(date);

	if (it == _db.end() || it->first != date)
	{
		if (it == _db.begin())
			return -1.0f;
		--it;
	}
	return it->second;
}

bool	BitcoinExchange::_loadDatabase(const std::string &csvFile)
{
	std::ifstream file(csvFile.c_str());
	if (!file.is_open())
		return false;
	std::string line;
	std::getline(file, line);
	while (std::getline(file, line))
	{
		if (line.empty()) continue;
		std::istringstream ss(line);
		std::string date;
		std::string rateStr;
		if (!std::getline(ss, date, ',') || !std::getline(ss, rateStr))
			continue;
		float rate = static_cast<float>(std::atof(rateStr.c_str()));
		_db[date] = rate;
	}
	return !_db.empty();
}

bool	BitcoinExchange::loadDatabase(const std::string &csvFile)
{
	return _loadDatabase(csvFile);
}

void	BitcoinExchange::processInput(const std::string &inputFile) const
{
	std::ifstream file(inputFile.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}
	std::string line;
	std::getline(file, line);
	while (std::getline(file, line))
	{
		if (line.empty()) continue;
		size_t sep = line.find(" | ");
		if (sep == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}
		std::string date  = line.substr(0, sep);
		std::string valStr = line.substr(sep + 3);
		if (!_isValidDate(date))
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}
		char *end;
		float value = std::strtof(valStr.c_str(), &end);
		if (end == valStr.c_str() || *end != '\0')
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}
		if (value < 0.0f)
		{
			std::cerr << "Error: not a positive number." << std::endl;
			continue;
		}
		if (value > 1000.0f)
		{
			std::cerr << "Error: too large a number." << std::endl;
			continue;
		}
		float rate = _getRate(date);
		if (rate < 0.0f)
		{
			std::cerr << "Error: bad input => " << date << " (date out of range)" << std::endl;
			continue;
		}
		std::cout << date << " => " << value << " = " << value * rate << std::endl;
	}
}
