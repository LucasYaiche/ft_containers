#ifndef UTILS_HPP
#define UTILS_HPP

# include <cstddef>
# include <string>
# include <iostream>
# include "../iterators/iterator_traits.hpp"
# include "pair.hpp"
# include "../utils/utils.hpp"

namespace ft
{
	template<bool B, class T = void>
	struct enable_if {};
 
	template<class T>
	struct enable_if<true, T> 
	{ 
		typedef T type; 
	};

	template <typename T, T val>
	struct integral_constant
	{
		static const	T							value = val;
		typedef			T							value_type;
		typedef			integral_constant<T, val>	type;
	};

	template<typename T, T val>
	const T integral_constant<T, val>::value;

	typedef integral_constant<bool, true>	true_type;
	typedef integral_constant<bool, false>	false_type;

	template <typename>
	struct is_integral : public false_type {};

	template <>
	struct is_integral<bool> : public true_type {};
	template <>
	struct is_integral<char> : public true_type {};
	template <>
	struct is_integral<char16_t> : public true_type {};
	template <>
	struct is_integral<char32_t> : public true_type {};
	template <>
	struct is_integral<wchar_t> : public true_type {};
	template <>
	struct is_integral<signed char> : public true_type {};
	template <>
	struct is_integral<unsigned char> : public true_type {};
	template <>
	struct is_integral<short> : public true_type {};
	template <>
	struct is_integral<unsigned short> : public true_type {};
	template <>
	struct is_integral<int> : public true_type {};
	template <>
	struct is_integral<unsigned int> : public true_type {};
	template <>
	struct is_integral<long> : public true_type {};
	template <>
	struct is_integral<unsigned long> : public true_type {};
	
	template<class It>
	typename iterator_traits<It>::difference_type __distance(It first, It last, input_iterator_tag)
	{
		typename iterator_traits<It>::difference_type result = 0;
		while (first != last) 
		{
			++first;
			++result;
		}
		return result;
	};
	
	template<class RAI>
	typename iterator_traits<RAI>::difference_type __distance(RAI first, RAI last, random_access_iterator_tag)
	{
		return last - first;
	};
	
	template<class It>
	typename iterator_traits<It>::difference_type distance(It first, It last)
	{
		return __distance(first, last, typename iterator_traits<It>::iterator_category());
	};

	template <class InputIterator1, class InputIterator2>
  	bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
	{
		while (first1!=last1) {
			if (!(*first1 == *first2))
				return false;
			++first1; ++first2;
		}
		return true;
	};
}

#endif