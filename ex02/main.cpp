/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 22:50:31 by aziyani           #+#    #+#             */
/*   Updated: 2024/01/20 13:11:02 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Pmergeme.hpp"

int main(int ac, char **av)
{
	Pmergeme merge;

	if (ac < 2)
	{
		std::cout << "Usage: ./merge [numbers]" << std::endl;
		return (1);
	}
	merge.init(av, ac -1);
	std::cout << "Before: ";
	merge.puts();
	unsigned long start = std::clock();
	merge.mergeSort();
	unsigned long end = std::clock();
	std::cout << "After: ";
	merge.puts();
	std::cout << "Time to process a range of " << merge.numberOfelements << " elements with std::vector : " \
		<< (end - start) / (double)(CLOCKS_PER_SEC / 1000000) << " us" << std::endl;
	// std::cout << std::is_sorted(merge.holder.begin(), merge.holder.end())  << std::endl;

	merge.init_(av, ac -1);
	start = std::clock();
	merge.mergeSort_();
	end = std::clock();
	std::cout << "Time to process a range of " << merge.numberOfelements << " elements with std::list : " \
		<< (end - start) / (double)(CLOCKS_PER_SEC / 1000000) << " us" << std::endl;
	// std::cout << std::is_sorted(merge.holder_.begin(), merge.holder_.end())  << std::endl;
	return (0);
}