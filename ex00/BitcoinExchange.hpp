/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:14:08 by aziyani           #+#    #+#             */
/*   Updated: 2024/01/19 12:36:08 by aziyani          ###   ########.fr       */
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
# include <chrono>
# include <ctime>

class BitcoinExchange
{
	private:
		std::map<std::string, float> database; // should explain why I chose this container and not another one
	public:
		BitcoinExchange();
		int checkDate(std::string date);
		int checkValue(float value);
		int check(char **av);
		void print_equivalent(std::string date, float value);
};

#endif