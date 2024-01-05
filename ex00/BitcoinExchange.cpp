/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:13:58 by aziyani           #+#    #+#             */
/*   Updated: 2024/01/05 13:10:48 by aziyani          ###   ########.fr       */
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
    while (getline(data, line)) // line = "date, value"
    {
        size_t pos = line.find(',');
        if (pos == std::string::npos)
            return;
        std::string date = line.substr(0, pos); // date = "2017-01-01"
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

// ========================================================================

int BitcoinExchange::check(char **av)
{
    std::string holder;
    float value;
    std::string copyDate;

    std::ifstream file(av[1]); // Open the file for reading
    if (!file)                 // Check if the file is open
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
    if (mapIterator->first != date)
    {
        if (mapIterator != database.begin())
            mapIterator--;
    }
    std::cout << date << " => " << value << " = " << mapIterator->second * value << std::endl;
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
        // std::cout << "\n[" << date << "]\n";
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
    if (buffer.length() != 2)
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
    if (buffer.length() != 3)
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
