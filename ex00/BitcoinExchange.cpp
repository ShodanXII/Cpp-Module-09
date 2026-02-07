#include "BitcoinExchange.hpp"

/* ---- Orthodox Canonical Form ---- */

BitcoinExchange::BitcoinExchange(void) {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _data(other._data) {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
		_data = other._data;
	return *this;
}

BitcoinExchange::~BitcoinExchange(void) {}

/* ---- Helpers ---- */

bool BitcoinExchange::isLeapYear(int year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool BitcoinExchange::isValidDate(const std::string &date)
{
	if (date.length() != 10)
		return false;
	if (date[4] != '-' || date[7] != '-')
		return false;
	for (int i = 0; i < 10; i++)
	{
		if (i == 4 || i == 7)
			continue;
		if (!std::isdigit(date[i]))
			return false;
	}

	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());

	if (month < 1 || month > 12)
		return false;
	if (day < 1)
		return false;

	int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (isLeapYear(year))
		daysInMonth[1] = 29;

	if (day > daysInMonth[month - 1])
		return false;

	return true;
}

/* ---- Database loading ---- */

void BitcoinExchange::loadDatabase(void)
{
	std::ifstream file("data.csv");
	if (!file.is_open())
	{
		std::cerr << "Error: could not open database file." << std::endl;
		return;
	}
	std::string line;
	std::getline(file, line); // skip header
	while (std::getline(file, line))
	{
		std::string::size_type pos = line.find(',');
		if (pos == std::string::npos)
			continue;
		std::string date = line.substr(0, pos);
		std::string rateStr = line.substr(pos + 1);
		char *end;
		double rate = std::strtod(rateStr.c_str(), &end);
		if (*end != '\0' && *end != '\r')
			continue;
		_data[date] = rate;
	}
	file.close();
}

/* ---- Process one input line ---- */

void BitcoinExchange::processLine(const std::string &line)
{
	std::string::size_type pipePos = line.find(" | ");
	if (pipePos == std::string::npos)
	{
		std::cerr << "Error: bad input => " << line << std::endl;
		return;
	}
	std::string date = line.substr(0, pipePos);
	std::string valueStr = line.substr(pipePos + 3);
	if (!isValidDate(date))
	{
		std::cerr << "Error: bad input => " << date << std::endl;
		return;
	}
	char *end;
	double value = std::strtod(valueStr.c_str(), &end);
	if (*end != '\0' && *end != '\r')
	{
		std::cerr << "Error: bad input => " << line << std::endl;
		return;
	}
	if (value < 0)
	{
		std::cerr << "Error: not a positive number." << std::endl;
		return;
	}
	if (value > 1000)
	{
		std::cerr << "Error: too large a number." << std::endl;
		return;
	}
	// Find closest lower or equal date
	std::map<std::string, double>::iterator it = _data.lower_bound(date);
	if (it == _data.end() || it->first != date)
	{
		if (it == _data.begin())
		{
			std::cerr << "Error: bad input => " << date << std::endl;
			return;
		}
		--it;
	}
	double result = value * it->second;
	std::cout << date << " => " << value << " = " << result << std::endl;
}

/* ---- Main constructor: load DB then process input ---- */

BitcoinExchange::BitcoinExchange(const std::string &file)
{
	loadDatabase();

	std::ifstream infile(file.c_str());
	if (!infile.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}
	std::string line;
	std::getline(infile, line); // skip header
	while (std::getline(infile, line))
	{
		if (line.empty())
			continue;
		processLine(line);
	}
	infile.close();
}
