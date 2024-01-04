/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:13:58 by aziyani           #+#    #+#             */
/*   Updated: 2024/01/04 16:47:07 by aziyani          ###   ########.fr       */
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
        return ;
    }
    std::string line;
    getline(data, line);
    while (getline(data, line)){
        size_t pos = line.find(',');
        if (pos == std::string::npos)
            return ;
        std::string date = line.substr(0, pos);
        std::string value = line.substr(pos + 1, line.length());
        database[date] = value;
    }
}

// ========================================================================

int BitcoinExchange::check(char **av)
{
	std::string holder;
	std::string date;
	std::string value;
    std::string copyDate;

	std::ifstream file(av[1]); // Open the file for reading
	if (!file) // Check if the file is open
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
		int i = 0;
		while (holder[i] != '|' && holder[i] != '\0')
		{
			date += holder[i];
			i++;
		}
		if (holder[i] == '|')
			i++;
		else
		{
			std::cerr << "Error: invalid file format" << std::endl;
			return (1);
		}
		while (holder[i] != '\n' && holder[i] != '\0')
		{
			value += holder[i];
			i++;
		}
		checkDate(date);
		checkValue(value);
        print_equivalent(date, value);
        // _map[date] = value;
        date.clear();
        value.clear();
	}
    return (0);
}

// ========================================================================

void BitcoinExchange::print_equivalent(std::string date, std::string value)
{
    std::map<std::string, std::string>::iterator it = database.lower_bound(date);
    std::cout << it->first << ", " << it->second << std::endl;
    // double dValue = std::strtod(value.c_str(), NULL);
    // double dValue2 = std::strtod(database[date].c_str(), NULL);
    // double result = dValue * dValue2;
    // std::cout << date << " | " << result << std::endl;
}

// ========================================================================

int BitcoinExchange::checkDate(std::string date)
{
	int year, month, day, hyphen;
    std::stringstream ss(date);
    std::string buffer;

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
    year = std::strtod(buffer.c_str(), NULL); // convert string to double
    if (year < 2009 || year > 2024)
    {
        std::cerr << "Error: invalid date2" << std::endl;
        return (1);
    }
    std::getline(ss, buffer, '-');
    if  (buffer.length() != 2)
    {
        std::cerr << "Error: invalid date3" << std::endl;
        return (1);
    }
    month = std::strtod(buffer.c_str(), NULL); // convert string to double
    if (month < 1 || month > 12)
    {
        std::cerr << "Error: invalid date4" << std::endl;
        return (1);
    }
    std::getline(ss, buffer, '-');
    if  (buffer.length() != 3)
    {
        std::cerr << "Error: invalid date5" << std::endl;
        return (1);
    }
    day = std::strtod(buffer.c_str(), NULL); // convert string to double
    if (day < 1 || day > 31)
    {
        std::cerr << "Error: invalid date6" << std::endl;
        return (1);
    }
    if (month == 2 && day > 28)
	{
		std::cerr << "Error: invalid date7" << std::endl;
		return (1);
	}
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
	{
		std::cerr << "Error: invalid date8" << std::endl;
		return (1);
	}
    return (0);
}

// ========================================================================

int BitcoinExchange::checkValue(std::string value)
{
    double dValue = std::strtod(value.c_str(), NULL);
    if(value[0] != 0 && dValue == 0)
    {
        std::cerr << "Error: invalid value" << std::endl;
        return (1);
    }
    if (dValue < 0 || dValue > 1000)
    {
        std::cerr << "Error: invalid value" << std::endl;
        return (1);
    }
    return (0);
}

// ========================================================================


// ========================================================================