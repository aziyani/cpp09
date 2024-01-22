/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:14:14 by aziyani           #+#    #+#             */
/*   Updated: 2024/01/21 12:06:20 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
	BitcoinExchange btc;
	
	if (ac != 2)
	{
		std::cout << "Error: could not open file." << std::endl;
		return (1);
	}
	btc.check(av);
	return (0);
}