/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 22:50:31 by aziyani           #+#    #+#             */
/*   Updated: 2024/01/17 17:35:57 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Pmergeme.hpp"

// void printVector(std::vector<int>& vec) {
//     for (std::vector<int>::const_iterator it = vec.begin(); it != vec.end(); ++it) {
//         std::cout << *it << ' ';
//     }
//     std::cout << '\n';
// }
int main(int ac, char **av)
{
	Pmergeme merge;

	if (ac < 2)
	{
		std::cout << "Usage: ./merge [numbers]" << std::endl;
		return (1);
	}
	merge.init(av, ac -1);
	merge.mergeSort();
	std::cout << std::is_sorted(merge.holder.begin(), merge.holder.end())  << std::endl;

	merge.init_(av, ac -1);
	merge.mergeSort_();
	std::cout << std::is_sorted(merge.holder_.begin(), merge.holder_.end())  << std::endl;
	return (0);
}