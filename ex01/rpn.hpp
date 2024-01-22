/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpn.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:23:19 by aziyani           #+#    #+#             */
/*   Updated: 2024/01/21 22:04:42 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <stack>
# include <sstream>
# include <iostream>

class rpn
{
    public:
        rpn();
        rpn(const rpn& obj);
        rpn operator=(const rpn& obj);
        ~rpn();
        int evaluated(const std::string& expression);
};

#endif