/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:23:10 by aziyani           #+#    #+#             */
/*   Updated: 2024/01/23 22:34:48 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "RPN.hpp"

rpn::rpn()
{
}

rpn::rpn(const rpn& obj)
{
	*this = obj;
}

rpn rpn::operator=(const rpn& obj)
{
	(void)obj;
	return (*this);
}

rpn::~rpn()
{
}

int rpn::evaluated(const std::string& expression)
{
    std::stack<int> stack;
    std::string number;

    for (std::string::const_iterator it = expression.begin(); it != expression.end(); ++it)
    {
        char c = *it;
        if (isdigit(c) && (it + 1 == expression.end() || !isdigit(*(it + 1))))
        {
            number += c;
        }
        else
        {
            if (!number.empty())
            {
                stack.push(std::atoi(number.c_str()));
                number.clear();
            }

            if (c == '+' || c == '-' || c == '*' || c == '/')
            {
                if (stack.size() < 2)
                    return -1;

                int first = stack.top(); stack.pop();
                int second = stack.top(); stack.pop();

                if (c == '+')
                    stack.push(first + second);
                else if (c == '-')
                    stack.push(second - first);
                else if (c == '*')
                    stack.push(first * second);
                else if (c == '/')
                {
                    if (second == 0)
                        return (-1);
                    stack.push(second / first);
                }
            }
			else if (!isspace(c))
				return (-1);
        }
    }
	if (!number.empty())
		stack.push(std::atoi(number.c_str()));
    if (stack.size() != 1)
        return (-1);
    return (stack.top());
}
