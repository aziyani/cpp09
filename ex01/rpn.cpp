/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:23:10 by aziyani           #+#    #+#             */
/*   Updated: 2024/01/05 21:36:07 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rpn.hpp"

rpn::rpn()
{
}

int rpn::evaluated(const std::string& expression)
{
	std::stringstream ss(expression);
	std::stack<int> stack;
	std::string token;

	while (ss >> token) // The while loop is used here to iterate over each token in the string stream ss.
	{
		if (isdigit(token[0]))
			stack.push(std::atoi(token.c_str()));
		else
		{
			if (stack.size() < 2)
				return 1;

			int first = stack.top(); stack.pop();
			int second = stack.top(); stack.pop();
		
			if (token == "+")
				stack.push(first + second);
			else if (token == "-")
				stack.push(second - first);
			else if (token == "*")
				stack.push(first * second);
			else if (token == "/")
			{
				if (second == 0)
				{
					std::cerr << "Error: division by zero" << std::endl;
					return (1);
				}
				stack.push(second / first);
			}
			else
				return (1);
		}
	}
	if (stack.size() != 1)
	{
		std::cerr << "Error: Invalid stack size" << std::endl;
		return (1);
	}
	return (stack.top());
}
