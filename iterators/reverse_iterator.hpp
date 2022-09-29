#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{
	template< class Iter >
	class reverse_iterator
	{
		public:

			typedef				Iter										iterator_type;
			typedef	typename	iterator_traits<Iter>::value_type			value_type;
			typedef	typename	iterator_traits<Iter>::difference_type		difference_type;
			typedef	typename	iterator_traits<Iter>::pointer				pointer;
			typedef	typename	iterator_traits<Iter>::reference			reference;				
	};
}

#endif