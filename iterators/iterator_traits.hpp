#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include "../utils/utils.hpp"

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

    template <class Iterator>
        struct iterator_traits
        {
            public :
                typedef typename Iterator::difference_type 		difference_type;
                typedef typename Iterator::value_type 			value_type;
                typedef typename Iterator::pointer 				pointer;
                typedef typename Iterator::reference 			reference;
                typedef typename Iterator::iterator_category 	iterator_category;
        };
    template <class T>
        struct iterator_traits<T*>
        {
            public :
                typedef ptrdiff_t 						difference_type;
                typedef T 								value_type;
                typedef T* 								pointer;
                typedef T& 								reference;
                typedef random_access_iterator_tag 		iterator_category;
        };
    template <class T>
        struct iterator_traits<T* const>
        {
            public :
                typedef ptrdiff_t 						difference_type;
                typedef T 								value_type;
                typedef const T* 						pointer;
                typedef const T& 						reference;
                typedef random_access_iterator_tag 		iterator_category;
        };
}

#endif