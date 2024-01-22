/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:22:46 by aziyani           #+#    #+#             */
/*   Updated: 2024/01/22 02:24:32 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "RPN.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Error: Invalid number of arguments" << std::endl;
        return(1);
    }
    rpn rpn;
    int result = rpn.evaluated(av[1]);
    if (result == -1)
    {
        std::cerr << "Error" << std::endl;
        return(0);
    }
    std::cout << result << std::endl;
    return (0);
}