/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pmergeme.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 22:18:51 by aziyani           #+#    #+#             */
/*   Updated: 2024/01/22 01:54:56 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <fstream>
# include <string>
# include <map>
# include <sstream>
# include <algorithm>
# include <vector>
# include <list>

// ---------------------------VECTOR-------------------------------------------
typedef std::vector<int> vector;											// |
typedef std::vector<vector> vectorOfvectors;								// |
typedef std::vector<std::pair<vector, vectorOfvectors::iterator> > pend;	// |
// ----------------------------LIST-----------------------------------------// |
typedef std::list<int> list;												// |
typedef std::list<list> listOflists;										// |
typedef std::list<std::pair<list, listOflists::iterator> > pendL;			// |
// ----------------------------VECTOR---------------------------------------// |
class Pmergeme																// |
{																			// |
	public:																	// |
		Pmergeme();        													// |
		Pmergeme(const Pmergeme& obj);										// |
		Pmergeme& operator=(const Pmergeme&);								// |
		~Pmergeme();														// |
		void			puts() const;										// |
		void			init(char **input, int size);						// |
		void			mergeSort();										// |
		void			copy_arr_to_holder(vectorOfvectors arr);			// |
		bool			more_than_one_pair(vectorOfvectors arr);			// |
		vectorOfvectors	make_array_of_vectors();							// |
		void			insert_vector();									// |
		void			sort_pairs(vectorOfvectors &);						// |
		void 			insert_pendchain();									// |
		void 			create_mainchain_penchain(vectorOfvectors arr);		// |
		void			update(vectorOfvectors::iterator ins);				// |
// ---------------------------LIST------------------------------------------// |
		void			init_(char **input, int size);						// |
		void			mergeSort_();										// |
		void			copy_list_to_holder_(listOflists arr);				// |
		bool			more_than_one_pair_(listOflists arr);				// |
		listOflists		make_list_of_lists_();								// |
		void			insert_list_();										// |
		void			sort_pairs_(listOflists &);							// |
		void 			insert_pendchain_();								// |
		void 			create_mainchain_penchain_(listOflists arr);		// |
		size_t			numberOfelements;									// |
// ---------------------------VECTOR----------------------------------------// |
	private:																// |
		list		holder_;												// |
		size_t			elementsize;										// |
		vector			rest;												// |
		vectorOfvectors	mainchain;											// |
		pend			pendchain;											// |
// ---------------------------LIST------------------------------------------// |
		vector			holder;												// |
		size_t		elementsize_;											// |
		list		rest_;													// |
		listOflists	mainchain_;												// |
		pendL		pendchain_;												// |
};																			// |
// ----------------------------------------------------------------------------

#endif