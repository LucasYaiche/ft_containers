#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{
	template< typename T >
	class random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, T>
	{
		public:

			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type			value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type		difference_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference				reference;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer				pointer;

		protected:

			pointer	_ptr;
		
		public:

			random_access_iterator(void)
			: _ptr(NULL){};

			random_access_iterator(pointer ptr)
			: _ptr(ptr){};

			random_access_iterator(const random_access_iterator& rai)
			: _ptr(rai._ptr){};

			~random_access_iterator(void){};

			random_access_iterator& operator=(const random_access_iterator& rhs)
			{
				if (this != &rhs)
				{
					rhs._ptr = this->_ptr;
				}
				return *this;
			}

			pointer base() const
			{
				return _ptr;
			}

			operator random_access_iterator<const T>() const
			{
				return (this->_ptr);
			}

			reference operator*() const
			{
				return (*this->_ptr);
			}

			pointer operator->() const
			{
				return &(operator*());
			}

			random_access_iterator& operator++()
			{
				++this->_ptr;
				return (*this);
			}

			random_access_iterator operator++(int)
			{
				random_access_iterator tmp(*this);
				operator++(); 
				return (tmp);
			}
			
			random_access_iterator& operator--()
			{
				--this->_ptr;
				return (*this);
			}

			random_access_iterator operator--(int)
			{
				random_access_iterator tmp(*this);
				operator--(); 
				return (tmp);
			}

			random_access_iterator operator+(difference_type n) const
			{
				return (random_access_iterator(this->_ptr + n));
			}

			random_access_iterator operator-(difference_type n) const
			{
				return (random_access_iterator(this->_ptr - n));
			}

			random_access_iterator& operator+=(difference_type n)
			{
				this->_ptr += n;
				return (*this);
			}

			random_access_iterator& operator-=(difference_type n)
			{
				this->_ptr -= n;
				return (*this);
			}

			reference operator[](difference_type n) const
			{
				return (this->_ptr[n]);
			}
	};
	
	template < typename IterL, typename IterR >
	bool operator==(random_access_iterator<IterL> const &lhs, random_access_iterator<IterR> const &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template < typename IterL, typename IterR >
	bool operator!=(random_access_iterator<IterL> const &lhs, random_access_iterator<IterR> const &rhs)
	{
		return (!(lhs.base() == rhs.base()));
	}

	template < typename IterL, typename IterR >
	bool operator<(random_access_iterator<IterL> const &lhs, random_access_iterator<IterR> const &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template < typename IterL, typename IterR >
	bool operator>(random_access_iterator<IterL> const &lhs, random_access_iterator<IterR> const &rhs)
	{
		return (rhs.base() < lhs.base());
	}

	template < typename IterL, typename IterR >
	bool operator<=(random_access_iterator<IterL> const &lhs, random_access_iterator<IterR> const &rhs)
	{
		return (!(rhs.base() < lhs.base()));
	}

	template < typename IterL, typename IterR >
	bool operator>=(random_access_iterator<IterL> const &lhs, random_access_iterator<IterR> const &rhs)
	{
		return (!(lhs.base() < rhs.base()));
	}

	template < typename Iterator >
	random_access_iterator<Iterator> operator+(typename random_access_iterator<Iterator>::difference_type n, random_access_iterator<Iterator> const &rhs)
	{
		return (rhs.base() + n);
	}

	template < typename IterL, typename IterR >
	typename random_access_iterator<IterL>::difference_type operator-(random_access_iterator<IterL> const &lhs, random_access_iterator<IterR> const &rhs)
	{
		return (lhs.base() - rhs.base());
	}
}

#endif