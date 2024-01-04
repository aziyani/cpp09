/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:14:08 by aziyani           #+#    #+#             */
/*   Updated: 2024/01/04 16:43:20 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream> // Include the necessary header file to be able to use cout, cin, etc.
# include <fstream> // Include the necessary header file to be able to use ifstream
# include <string> // Include the necessary header file to be able to use string functions
# include <map> // Include the necessary header file to be able to use map functions
# include <sstream>// Include the necessary header file to be able to use stringstream functions
# include <algorithm>

class BitcoinExchange
{
	private:
		std::map<std::string, std::string> _map;
		std::map<std::string, std::string> database;
	public:
		BitcoinExchange();
		int checkDate(std::string date);
		int checkValue(std::string value);
		int check(char **av);
		void print_equivalent(std::string date, std::string value);
};

#endif