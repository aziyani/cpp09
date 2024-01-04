/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:14:14 by aziyani           #+#    #+#             */
/*   Updated: 2024/01/04 15:57:01 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
	BitcoinExchange btc;
	
	std::string holder;
	
	if (ac != 2)
	{
		std::cout << "Usage: ./btc [file]" << std::endl;
		return (1);
	}
	btc.check(av);
	return (0);
}