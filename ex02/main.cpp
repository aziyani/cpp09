/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 22:50:31 by aziyani           #+#    #+#             */
/*   Updated: 2024/01/07 15:43:38 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Pmergeme.hpp"

void printVector(std::vector<int>& vec) {
    for (std::vector<int>::const_iterator it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << '\n';
}
int main(int ac, char **av)
{
	Pmergeme merge;
	if (ac != 2)
	{
		std::cout << "Usage: ./merge [numbers]" << std::endl;
		return (1);
	}
	merge.init(av[1]);
	merge.mergeSort();
	// printVector(merge.holder);
	return (0);
}