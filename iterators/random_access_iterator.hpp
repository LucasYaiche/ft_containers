#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{
	template< typename T >
	class random_access_iterator : public ft::iterator<random_access_iterator_tag, T>
	{
		public:

			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type			value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::diffenrence_type		diffenrence_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference				reference;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer				pointer;

		protected:

			pointer	_ptr;
		
		public:

			random_access_iterator(void)
			: _ptr(NUll){};

			random_access_iterator(pointer ptr)
			: _ptr(ptr){};

			random_access_iterator(const random_access_iterator& rai)
			: _ptr(rai.other){};

			random_access_iterator& operator=(const random_access_iterator& rhs)
			{
				if (this != &rhs)
				{
					rhs._ptr = this->_ptr;
				}
				return *this;
			}


	};
}

#endif