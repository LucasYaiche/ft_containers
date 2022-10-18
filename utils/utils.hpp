#ifndef UTILS_HPP
#define UTILS_HPP

# include <cstddef>
# include <string>
# include <iostream>

namespace ft
{
	struct	input_iterator_tag {};
	struct	output_iterator_tag {};
	struct	forward_iterator_tag : public input_iterator_tag {};
	struct	bidirectional_iterator_tag : public	forward_iterator_tag {};
	struct	random_access_iterator_tag : public bidirectional_iterator_tag {};

	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
  	class iterator 
	{
		public:
		
			typedef T         value_type;
			typedef Distance  difference_type;
			typedef Pointer   pointer;
			typedef Reference reference;
			typedef Category  iterator_category;
  	};

	template<class InputIt1, class InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
	{
		for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
		{
			if (*first1 < *first2)
				return true;
			if (*first2 < *first1)
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

	template<class InputIt1, class InputIt2>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!(*first1 == *first2))
			{
				return false;
			}
		}
		return true;
	}

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
	// template<class It>
	// typename iterator_traits<It>::difference_type __distance(It first, It last, input_iterator_tag)
	// {
	// 	typename iterator_traits<It>::difference_type result = 0;
	// 	while (first != last) {
	// 		++first;
	// 		++result;
	// 	}
	// 	return result;
	// }
	
	// template<class RAI>
	// typename iterator_traits<RAI>::difference_type __distance(RAI first, RAI last, random_access_iterator_tag)
	// {
	// 	return last - first;
	// }
	
	// template<class It>
	// typename iterator_traits<It>::difference_type distance(It first, It last)
	// {
	// 	return __distance(first, last, typename iterator_traits<It>::iterator_category());
	// }
}

#endif