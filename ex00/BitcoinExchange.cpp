/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:13:58 by aziyani           #+#    #+#             */
/*   Updated: 2024/01/23 22:54:39 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

// ========================================================================

BitcoinExchange::BitcoinExchange()
{
	std::ifstream data("data.csv");

	if (!data.is_open())
	{
		std::cout << "Error: could not open file" << std::endl;
		return;
	}
	std::string line;
	float fLine;
	getline(data, line);
	while (getline(data, line))
	{
		size_t pos = line.find(',');
		if (pos == std::string::npos)
			return;
		std::string date = line.substr(0, pos);
		std::stringstream valueStream(line.substr(pos + 1, line.length()));
		if (valueStream >> fLine)
		{
			database[date] = fLine;
		}
		else
		{
			std::cout << "Error: invalid file format" << std::endl;
			return;
		}
	}
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& obj)
{
	*this = obj;
}

BitcoinExchange BitcoinExchange::operator=(const BitcoinExchange& obj)
{
	(void)obj;
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
	
}

// ========================================================================

int BitcoinExchange::check(char **av)
{
	std::string holder;
	float value;
	std::string copyDate;

	std::ifstream file(av[1]);
	if (!file)
	{
		std::cout << "Error: could not open file" << std::endl;
		return (1);
	}
	if (!std::getline(file, holder))
	{
		std::cout << "Error: could not read file" << std::endl;
		return (1);
	}
	if (holder.compare("date | value") != 0)
	{
		std::cout << "Error: invalid file format" << std::endl;
		return (1);
	}
	while (std::getline(file, holder))
	{
		std::string date;
		int i = 0;

		if (holder.empty())
			continue;
		while (holder[i] != '|' && holder[i] != '\0')
		{
			date += holder[i];
			i++;
		}
		if (holder[i] == '|')
			i++;
		else
		{
			std::cerr << "Error: bad input => " << holder << std::endl;
			continue;
		}
		std::stringstream vvalue(&holder[i]);
		if (!(vvalue >> value))
		{
			std::cout << "Error: invalid file format" << std::endl;
			continue;
		}
		if (!checkDate(date) && !checkValue(value))
			print_equivalent(date, value);
		value = 0;
	}
	return (0);
}

// ========================================================================

void BitcoinExchange::print_equivalent(std::string date, float value)
{
	std::map<std::string, float>::iterator mapIterator;
	mapIterator = database.lower_bound(date);
	if (mapIterator == database.begin() && mapIterator->first != date)
	{
		std::cerr << "Error: date not found." << std::endl;
		return;
	}
	else
	if (mapIterator == database.end())
		mapIterator--;
	else if (mapIterator->first != date)
	{
		if (mapIterator != database.begin())
			mapIterator--;
	}
	std::cout << date << " => " << value << " = " << mapIterator->second * value << std::endl;
}

// ========================================================================

bool BitcoinExchange::isLeapYear(int year)
{
    if (year % 4 != 0) // if not divisible by 4 then not a leap year
    {
        return false;
    }
    else if (year % 100 != 0)
    {
        return true;
    }
    else if (year % 400 != 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

int BitcoinExchange::checkDate(std::string date)
{
	int year, month, day, hyphen;
	std::stringstream ss(date);
	std::string buffer;

	std::time_t currentTime = std::time(0);

	std::tm* timeInfo = std::localtime(&currentTime);

	hyphen = 0;
	for (int i = 0; date[i]; i++)
	{
		if (date[i] == '-')
			hyphen++;
	}
	if (hyphen != 2)
	{
		std::cerr << "Error: invalid date1" << std::endl;
		return (1);
	}
	hyphen = 0;
	std::getline(ss, buffer, '-');
	year = std::strtod(buffer.c_str(), NULL);
	if (year < 2009 || year > 1900 + timeInfo->tm_year)
	{
		std::cerr << "Error: invalid date2" << std::endl;
		return (1);
	}
	std::getline(ss, buffer, '-');
	if (buffer.length() != 2)
	{
		std::cerr << "Error: invalid date3" << std::endl;
		return (1);
	}
	month = std::strtod(buffer.c_str(), NULL);
	if (month < 1 || month > 12)
	{
		std::cerr << "Error: invalid date4" << std::endl;
		return (1);
	}
	std::getline(ss, buffer, ' ');
	if (buffer.length() != 2)
	{
		std::cerr << "Error: invalid date5" << std::endl;
		return (1);
	}
	day = std::strtod(buffer.c_str(), NULL);
	if (day < 1 || day > 31)
	{
		std::cerr << "Error: invalid date6" << std::endl;
		return (1);
	}
	if (month == 2 && day > 28 && !isLeapYear(year))
	{
		std::cerr << "Error: invalid date7" << std::endl;
		return (1);
	}
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
	{
		std::cerr << "Error: invalid date8" << std::endl;
		return (1);
	}
	if (year == 1900 + timeInfo->tm_year && (month >  1 + timeInfo->tm_mon || day > timeInfo->tm_mday))
	{
		std::cerr << "Error: invalid date9" << std::endl;
		return (1);
	}
	return (0);
}

// ========================================================================

int BitcoinExchange::checkValue(float value)
{
	if (value < 0)
	{
		std::cerr << "Error: not a positive number." << std::endl;
		return (1);
	}
	if (value > 1000)
	{
		std::cerr << "Error: too large a number." << std::endl;
		return (1);
	}
	return (0);
}

// ========================================================================
