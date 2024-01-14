/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pmergeme.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 22:13:30 by aziyani           #+#    #+#             */
/*   Updated: 2024/01/14 15:27:41 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pmergeme.hpp"

// ===========================================================================

Pmergeme::Pmergeme(){
    elementsize = 1; // element size of vector
}

void Pmergeme::init(char **input, int size)
{
    // store the numbers from the input to the holder vector 
    std::string token;
    for (int i = 1; i <= size; ++i){
        std::stringstream ss(input[i]);
        while (ss >> token){
            holder.push_back(std::strtod(token.c_str(), NULL));
        }
    }
        // holder.push_back(std::strtod(token.c_str(), NULL));

    // while (std::getline(ss, token, ' '))
        // holder.push_back(std::atoi(token.c_str()));
}

// ===========================================================================

vectorOfvectors Pmergeme::make_array_of_vectors()
{
    // create a vector of vectors from holder each vector holding elementsize number of elements
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

void Pmergeme::sort_pairs(vectorOfvectors& arr){ 
    // compare the last element of the first vector with the last element of the second vector if the first vector is bigger than the second vector swap them.
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

void Pmergeme::copy_arr_to_holder(vectorOfvectors arr){ 
    // copyy arr to holder vector
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

bool Pmergeme::more_than_one_pair(vectorOfvectors arr){ // pair = two vectors
    // check if the array contains more than one 4 vectors and the 4 vectors size are equal elementsize number of elements
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
    // if (count > 1 && arr[i].size() == elementsize && arr[i + 1].size() != elementsize)
    //     return false;
    // else if (count > 1 &&arr[i].size() == elementsize && arr[i + 1].size() != elementsize)
    //     return true;
    // return false;
}

// ===========================================================================

void printVectorOfVectors(const std::vector<std::vector<int> >& vec) {
    std::cout << "start vecofvec\n";
    for (std::vector<std::vector<int> >::const_iterator it = vec.begin(); it != vec.end(); ++it) {
        std::cout << "[ ";
        for (std::vector<int>::const_iterator innerIt = it->begin(); innerIt != it->end(); ++innerIt) {
            std::cout << *innerIt << " ";
        }
        std::cout << " ]\n";
    }
    std::cout << "\n\nend vecofvec\n";
}
// ===========================================================================

void Pmergeme::create_mainchain_penchain(vectorOfvectors arr){
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

bool compare(vector first, vector second){ 
    return (first.back() < second.back());
}

// ===========================================================================

void     Pmergeme::update(vectorOfvectors::iterator ins){
    pend::iterator it;

    it = pendchain.begin();
    for (; it != pendchain.end(); ++it)
    {
        if (it->second >= ins)
            it->second++;
    }
    
}

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
            pos = std::lower_bound(mainchain.begin(), start->second, start->first, compare); // we should not pass the end of the mainchain we should pass the pendchain.second?
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

    arr = make_array_of_vectors();
    printVectorOfVectors(arr);
    sort_pairs(arr);
    copy_arr_to_holder(arr);
    if (more_than_one_pair(arr))
    {
        elementsize *= 2;
        mergeSort();
    }
    insert_vector();
}

// =======================================================================================================================================================================
// list

// ===========================================================================

// Pmergeme::Pmergeme(){
//     elementsize = 1; // element size of vector
// }

// void Pmergeme::init(char **input, int size)
// {
//     // store the numbers from the input to the holder vector 
//     std::string token;
//     for (int i = 1; i <= size; ++i){
//         std::stringstream ss(input[i]);
//         while (ss >> token){
//             holder.push_back(std::strtod(token.c_str(), NULL));
//         }
//     }
// }

// // ===========================================================================

// vectorOfvectors Pmergeme::make_array_of_vectors()
// {
//     // create a vector of vectors from holder each vector holding elementsize number of elements
//     vectorOfvectors arr;
//     vector temp;
//     size_t i = 0;
    
//     while (i < holder.size())
//     {
//         for (size_t j = 0; j < elementsize && i < holder.size(); ++j)
//         {
//             temp.push_back(holder[i]);
//             ++i;
//         }
//         arr.push_back(temp);
//         temp.clear();
//     }
//     return arr;
// }

// // ===========================================================================

// void Pmergeme::sort_pairs(vectorOfvectors& arr){ 
//     // compare the last element of the first vector with the last element of the second vector if the first vector is bigger than the second vector swap them.
    
//     size_t i = 0;
//     while (i + 1 < arr.size())
//     {
//         if (arr[i][arr[i].size() - 1] > arr[i + 1][arr[i + 1].size() - 1])
//             std::swap(arr[i], arr[i + 1]);
//         i += 2;
//     }
// }

// // ===========================================================================

// void Pmergeme::copy_arr_to_holder(vectorOfvectors arr){ 
//     // copyy arr to holder vector
//     holder.clear();
//     size_t i = 0;
//     while (i < arr.size())
//     {
//         size_t j = 0;
//         while (j < arr[i].size())
//         {
//             holder.push_back(arr[i][j]);
//             j++;
//         }
//         i++;
//     }
// }

// // ===========================================================================

// bool Pmergeme::more_than_one_pair(vectorOfvectors arr){ // pair = two vectors
//     // check if the array contains more than one 4 vectors and the 4 vectors size are equal elementsize number of elements
//     size_t i = 0;
//     size_t count = 0;
//     while (i < arr.size() - 1)
//     {
//         if (arr[i].size() == elementsize && (i + 1 < arr.size() && arr[i + 1].size() == elementsize))
//             count++;
//         i += 2;
//     }
//     if (count > 1)
//         return true;
//     return false;
//     // if (count > 1 && arr[i].size() == elementsize && arr[i + 1].size() != elementsize)
//     //     return false;
//     // else if (count > 1 &&arr[i].size() == elementsize && arr[i + 1].size() != elementsize)
//     //     return true;
//     // return false;
// }

// // ===========================================================================

// void printVectorOfVectors(const std::vector<std::vector<int> >& vec) {
//     std::cout << "start vecofvec\n";
//     for (std::vector<std::vector<int> >::const_iterator it = vec.begin(); it != vec.end(); ++it) {
//         std::cout << "[ ";
//         for (std::vector<int>::const_iterator innerIt = it->begin(); innerIt != it->end(); ++innerIt) {
//             std::cout << *innerIt << " ";
//         }
//         std::cout << " ]\n";
//     }
//     std::cout << "\n\nend vecofvec\n";
// }
// // ===========================================================================

// void Pmergeme::create_mainchain_penchain(vectorOfvectors arr){
//     std::pair<vector, vectorOfvectors::iterator> pair;

//     if (arr.back().size() != elementsize)
//     {
//         rest = arr.back();
//         arr.pop_back();
//     }
    
//     mainchain.clear();
//     pendchain.clear();

//     mainchain.reserve(arr.size());
//     pendchain.reserve(arr.size());
    
//     mainchain.insert(mainchain.end(), arr[0]);
//     mainchain.insert(mainchain.end(), arr[1]);
    
//     for (size_t i = 2; i < arr.size();)
//     {
//         pair.first = arr[i];
//         pair.second = mainchain.end();
//         ++i;
//         if (i < arr.size())
//             pair.second = mainchain.insert(mainchain.end(), arr[i]); // we use insert here because it is return an iterator of the position of the inserted element
//         ++i;
//         pendchain.push_back(pair);
//     }   
// }

// // ===========================================================================

// bool compare(vector first, vector second){ 
//     return (first.back() < second.back());
// }

// // ===========================================================================

// // void     Pmergeme::update(vectorOfvectors::iterator ins){
// //     pend::iterator it;

// //     it = pendchain.begin();
// //     for (; it != pendchain.end(); ++it)
// //     {
// //         if (it->second >= ins)
// //             it->second++;
// //     }
    
// // }

// void Pmergeme::insert_pendchain()
// {
//     vectorOfvectors::iterator pos;
//     vectorOfvectors::iterator ins;
//     pend::iterator it;
//     pend::iterator start;
//     pend::iterator end;
//     unsigned long jac[] = {2, 2, 6, 10, 22, 42, 86, 170, 342, 682, 1366,
//         2730, 5462, 10922, 21846, 43690, 87382, 174762, 349526, 699050,
//         1398102, 2796202, 5592406, 11184810, 22369622, 44739242, 89478486,
//         178956970, 357913942, 715827882, 1431655766, 2863311530, 5726623062,
//         11453246122, 22906492246, 45812984490};
//     int j = 0;
//     while (pendchain.size())
//     {
//         start = pendchain.begin();
//         end = pendchain.begin();
//         for (size_t i = 0; i < jac[j] - 1 && start != pendchain.end(); i++)
//             start++;
//         if (start == pendchain.end())
//             start--;
//         while (true)
//         {
//             pos = std::lower_bound(mainchain.begin(), start->second, start->first, compare); // we should not pass the end of the mainchain we should pass the pendchain.second?
//             ins = mainchain.insert(pos, start->first);
//             // update(ins);
//             pendchain.erase(start);
//             if (start == end)
//                 break;
//             start--;
//         }
//         j++;
//     }
//     if (rest.size())
//     {
//         mainchain.push_back(rest);
//         rest.clear();    
//     }
// }

// // ===========================================================================

// void Pmergeme::insert_vector()
// {
//     vectorOfvectors arr;

//     arr = make_array_of_vectors();
//     create_mainchain_penchain(arr);
//     insert_pendchain();
//     copy_arr_to_holder(mainchain);
//     elementsize /= 2;
// }
// // ===========================================================================

// void Pmergeme::mergeSort()
// {
//     vectorOfvectors arr;

//     arr = make_array_of_vectors();
//     sort_pairs(arr);
//     copy_arr_to_holder(arr);
//     if (more_than_one_pair(arr))
//     {
//         elementsize *= 2;
//         mergeSort();
//     }
//     insert_vector();
//      printVectorOfVectors(arr);

// }

// // ===========================================================================
