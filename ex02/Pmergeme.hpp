/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pmergeme.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 22:18:51 by aziyani           #+#    #+#             */
/*   Updated: 2024/01/07 19:48:38 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream> // Include the necessary header file to be able to use cout, cin, etc.
# include <fstream> // Include the necessary header file to be able to use ifstream
# include <string> // Include the necessary header file to be able to use string functions
# include <map> // Include the necessary header file to be able to use map functions
# include <sstream>// Include the necessary header file to be able to use stringstream functions
# include <algorithm>
#include <vector> // Include the necessary header file to be able to use vector

typedef std::vector<int> vector;
typedef std::vector<vector> vectorOfvectors;
typedef std::vector<std::pair<vector, vectorOfvectors::iterator> > pend;

class Pmergeme
{
	public:
		Pmergeme();        
		void init(char *input);
		void mergeSort();
		void copy_arr_to_holder(vectorOfvectors arr);
		bool more_than_one_pair(vectorOfvectors arr);
		vectorOfvectors make_array_of_vectors();
		void insert_vector();
		void sort_pairs(vectorOfvectors &);
		void  insert_pendchain();
		void  create_mainchain_penchain(vectorOfvectors arr); //
	
	private:
		vector          holder;
		size_t          elementsize;
		vector          rest;
		vectorOfvectors mainchain;
		pend            pendchain;
};

#endif