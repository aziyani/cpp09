/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pmergeme.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 22:13:30 by aziyani           #+#    #+#             */
/*   Updated: 2024/01/23 20:30:15 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pmergeme.hpp"

// ===========================================================================

Pmergeme::Pmergeme()
{
	elementsize = 1;
	elementsize_ = 1;
}

Pmergeme::Pmergeme(const Pmergeme& obj)
{
	*this = obj;
}

Pmergeme& Pmergeme::operator=(const Pmergeme& obj)
{
	(void)obj;
	return *this;
}

Pmergeme::~Pmergeme()
{
}

// ===========================================================================

void	Pmergeme::puts() const
{
	vector::const_iterator it = holder.begin();
	while ( it != holder.end())
	{
		std::cout << *it << " ";
		it++;
	}
	std::cout << std::endl;
}


// ===========================================================================

int isDigit(std::string str)
{
	for (size_t i = 0; i < str.length(); ++i)
	{
		if (!isdigit(str[i]))
			return (0);
	}
	return (1);
}

// ===========================================================================

void Pmergeme::init(char **input, int size)
{
	int token;
	for (int i = 1; i <= size; ++i){
		std::stringstream ss(input[i]);
		if (ss >> token && isDigit(input[i]))
			holder.push_back(token);
		else
		{
			std::cout << "Error: Invalid input" << std::endl;
			exit(1);
		}
	}
	numberOfelements = holder.size();
}

// ===========================================================================

vectorOfvectors Pmergeme::make_array_of_vectors()
{
	vectorOfvectors arr;
	vector temp;
	size_t i = 0;
	
	while (i < holder.size())
	{
		for (size_t j = 0; j < elementsize && i < holder.size(); ++j)
		{
			temp.push_back(holder[i]);
			++i;
		}
		arr.push_back(temp);
		temp.clear();
	}
	return arr;
}

// ===========================================================================

void Pmergeme::sort_pairs(vectorOfvectors& arr)
{ 
	vector first, scnd;
	size_t i = 0;
	while (i  < arr.size() - 1)
	{
		first = arr[i];
		scnd = arr[i + 1];
		if (scnd.size() != elementsize)
			break ;
		if (first.back() > scnd.back())
			std::swap(arr[i], arr[i + 1]);
		i += 2;
	}
}

// ===========================================================================

void Pmergeme::copy_arr_to_holder(vectorOfvectors arr)
{ 
	holder.clear();
	size_t i = 0;
	while (i < arr.size())
	{
		size_t j = 0;
		while (j < arr[i].size())
		{
			holder.push_back(arr[i][j]);
			j++;
		}
		i++;
	}
}

// ===========================================================================

bool Pmergeme::more_than_one_pair(vectorOfvectors arr)
{
	size_t i = 0;
	size_t count = 0;
	while (i < arr.size())
	{
		if (arr[i].size() == elementsize && (i + 1 < arr.size() && arr[i + 1].size() == elementsize))
			count++;
		i += 2;
	}
	if (count > 1)
		return true;
	return false;
}

// ===========================================================================

void Pmergeme::create_mainchain_penchain(vectorOfvectors arr)
{
	std::pair<vector, vectorOfvectors::iterator> pair;

	if (arr.back().size() != elementsize)
	{
		rest = arr.back();
		arr.pop_back();
	}
	
	mainchain.clear();
	pendchain.clear();

	mainchain.reserve(arr.size());
	pendchain.reserve(arr.size());
	
	mainchain.insert(mainchain.end(), arr[0]);
	mainchain.insert(mainchain.end(), arr[1]);
	
	for (size_t i = 2; i < arr.size();)
	{
		pair.first = arr[i];
		pair.second = mainchain.end();
		++i;
		if (i < arr.size())
			pair.second = mainchain.insert(mainchain.end(), arr[i]); // we use insert here because it is return an iterator of the position of the inserted element
		++i;
		pendchain.push_back(pair);
	}   
}

// ===========================================================================

void     Pmergeme::update(vectorOfvectors::iterator ins)
{
	pend::iterator it;

	it = pendchain.begin();
	for (; it != pendchain.end(); ++it)
	{
		if (it->second >= ins)
			it->second++;
	}
	
}

// ===========================================================================

bool compare(vector first, vector second)
{
	return (first.back() < second.back());
}
// ===========================================================================

void Pmergeme::insert_pendchain()
{
	vectorOfvectors::iterator pos;
	vectorOfvectors::iterator ins;
	pend::iterator it;
	pend::iterator start;
	pend::iterator end;
	unsigned long jac[] = {2, 2, 6, 10, 22, 42, 86, 170, 342, 682, 1366,
		2730, 5462, 10922, 21846, 43690, 87382, 174762, 349526, 699050,
		1398102, 2796202, 5592406, 11184810, 22369622, 44739242, 89478486,
		178956970, 357913942, 715827882, 1431655766, 2863311530, 5726623062,
		11453246122, 22906492246, 45812984490};
	int j = 0;
	while (pendchain.size())
	{
		start = pendchain.begin();
		end = pendchain.begin();
		for (size_t i = 0; i < jac[j] - 1 && start != pendchain.end(); i++)
			start++;
		if (start == pendchain.end())
			start--;
		while (true)
		{
			pos = std::lower_bound(mainchain.begin(), start->second, start->first, compare); // (costum comparition)
			ins = mainchain.insert(pos, start->first);
			update(ins);
			pendchain.erase(start);
			if (start == end)
				break;
			start--;
		}
		j++;
	}
	if (rest.size())
	{
		mainchain.push_back(rest);
		rest.clear();    
	}
}

// ===========================================================================

void Pmergeme::insert_vector()
{
	vectorOfvectors arr;

	arr = make_array_of_vectors();
	create_mainchain_penchain(arr);
	insert_pendchain();
	copy_arr_to_holder(mainchain);
	elementsize /= 2;
}
// ===========================================================================

void Pmergeme::mergeSort()
{
	vectorOfvectors arr;

	if (holder.size() == 1)
		return ;
	arr = make_array_of_vectors();
	sort_pairs(arr);
	copy_arr_to_holder(arr);
	if (more_than_one_pair(arr))
	{
		elementsize *= 2;
		mergeSort();
	}
	insert_vector();
}

// ==================================================================================================================================================================================================

int isDigit_(std::string str)
{
	for (size_t i = 0; i < str.length(); ++i)
	{
		if (!isdigit(str[i]))
			return (0);
	}
	return (1);
}

// ===========================================================================

void Pmergeme::init_(char **input, int size)
{
	int token;
	for (int i = 1; i <= size; ++i)
	{
		std::stringstream ss(input[i]);
		if (ss >> token && isDigit_(input[i]))
			holder_.push_back(token);
		else
		{
			std::cout << "Error: Invalid input" << std::endl;
			exit(1);
		}
	}
}

// ===========================================================================

listOflists Pmergeme::make_list_of_lists_()
{
	listOflists arr;
	list::iterator it = holder_.begin();
	while (it != holder_.end())
	{
		list temp;
		for (size_t j = 0; j < elementsize_ && it != holder_.end(); ++j)
		{
			temp.push_back(*it);
			++it;
		}
		arr.push_back(temp);
	}
	return arr;
}

// ===========================================================================

void Pmergeme::sort_pairs_(listOflists& arr)
{ 
	listOflists::iterator it = arr.begin();
	while (it != arr.end())
	{
		listOflists::iterator nextIterator = it;
		++nextIterator;
		if (nextIterator == arr.end())
            break;
		if (nextIterator->size() != elementsize_)
			break ;
		if (it->back() > nextIterator->back())
			std::iter_swap(it, nextIterator);
		std::advance(it, 2);
	}
}

// ===========================================================================

void Pmergeme::copy_list_to_holder_(listOflists arr)
{ 
	holder_.clear();
	listOflists::iterator it = arr.begin();
	while (it != arr.end())
	{

		list::iterator innerIt = it->begin();
		while (innerIt != it->end())
		{
			holder_.push_back(*innerIt);
			++innerIt;
		}
		++it;
	}
}

// ===========================================================================

bool Pmergeme::more_than_one_pair_(listOflists arr)
{
	listOflists::iterator it = arr.begin();
	size_t count = 0;
	while (it != arr.end())
	{
		listOflists::iterator nextIterator = it;
		++nextIterator;
		if (it->size() == elementsize_ && (nextIterator != arr.end() && nextIterator->size() == elementsize_))
			count++;
		if (nextIterator != arr.end())
            std::advance(it, 2);
        else
            break;
	}
	if (count > 1)
		return true;
	return false;
}

// ===========================================================================

void Pmergeme::create_mainchain_penchain_(listOflists arr)
{
	std::pair<list, listOflists::iterator> pair;

	if (arr.back().size() != elementsize_)
	{
		rest_ = arr.back();
		arr.pop_back();
	}
	
	mainchain_.clear();	
	pendchain_.clear();
	
	listOflists::iterator it = arr.begin();
	mainchain_.push_back(*it);
	++it;
	mainchain_.push_back(*it);
	++it;
	
    while (it != arr.end())
    {
        pair.first = *it;
        pair.second = mainchain_.end();
        ++it;
        if (it != arr.end()){
            pair.second = mainchain_.insert(mainchain_.end(), *it);
        	++it;
		}

       	pendchain_.push_back(pair);
    }     
}

// ===========================================================================

bool compare_(list first, list second)
{
	return (first.back() < second.back());
}
// ===========================================================================

void Pmergeme::insert_pendchain_()
{
	listOflists::iterator pos;
	listOflists::iterator ins;
	pendL::iterator it;
	pendL::iterator start;
	pendL::iterator tmp;
	pendL::iterator end;
	unsigned long jac[] = {2, 2, 6, 10, 22, 42, 86, 170, 342, 682, 1366,
		2730, 5462, 10922, 21846, 43690, 87382, 174762, 349526, 699050,
		1398102, 2796202, 5592406, 11184810, 22369622, 44739242, 89478486,
		178956970, 357913942, 715827882, 1431655766, 2863311530, 5726623062,
		11453246122, 22906492246, 45812984490};
	int j = 0;
	while (pendchain_.size())
	{
		start = pendchain_.begin();
		end = pendchain_.begin();
		for (size_t i = 0; i < jac[j] - 1 && start != pendchain_.end(); i++)
			start++;
		if (start == pendchain_.end())
			start--;
		while (true)
		{
			pos = std::lower_bound(mainchain_.begin(), start->second, start->first, compare_);
			mainchain_.insert(pos, start->first);
			tmp = start;
			--tmp;
			
			pendchain_.erase(start);
			if (start == end)
				break ;
			start = tmp;
		}
		j++;
	}
	if (rest_.size())
	{
		mainchain_.push_back(rest_);
		rest_.clear();    
	}
}

// ===========================================================================

void Pmergeme::insert_list_()
{
	listOflists arr;

	arr = make_list_of_lists_();
	create_mainchain_penchain_(arr);
	insert_pendchain_();
	copy_list_to_holder_(mainchain_);
}
// ===========================================================================

void Pmergeme::mergeSort_()
{
	listOflists arr;
	
	if (holder_.size() == 1)
		return ;
	arr = make_list_of_lists_();
	bool	shouldDoInsertion = (arr.size() > 3) || ( arr.size() == 3 && arr.back().size() == elementsize_);
	
	sort_pairs_(arr);
	copy_list_to_holder_(arr);
	if (more_than_one_pair_(arr))
	{
		elementsize_ *= 2;
		mergeSort_();
		elementsize_ /= 2;
	}
	if (shouldDoInsertion)
		insert_list_();
}

// ===========================================================================