/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:14:08 by aziyani           #+#    #+#             */
/*   Updated: 2024/01/22 02:42:34 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <fstream>
# include <string>
# include <map>
# include <sstream>
# include <algorithm>
# include <chrono>
# include <ctime>

class BitcoinExchange
{
	private:
		std::map<std::string, float> database;
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& obj);
		BitcoinExchange operator=(const BitcoinExchange& obj);
		~BitcoinExchange();
		bool isLeapYear(int year);
		int checkDate(std::string date);
		int checkValue(float value);
		int check(char **av);
		void print_equivalent(std::string date, float value);
};

#endif