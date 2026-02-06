#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <map>
#include <string>

class BitcoinExchange
{
private:
	std::map<std::string, double> _data;

	void loadDatabase(void);
	void processLine(const std::string &line);

	static bool isValidDate(const std::string &date);
	static bool isLeapYear(int year);

public:
	BitcoinExchange(void);
	BitcoinExchange(const std::string &file);
	BitcoinExchange(const BitcoinExchange &other);
	BitcoinExchange &operator=(const BitcoinExchange &other);
	~BitcoinExchange();
};
