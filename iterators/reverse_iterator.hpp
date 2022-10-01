#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{
	template< class Iterator >
	class reverse_iterator
	{
		public:

			typedef				Iterator									iterator_type;
			typedef	typename	iterator_traits<Iter>::iterator_category	iterator_category;
			typedef	typename	iterator_traits<Iter>::value_type			value_type;
			typedef	typename	iterator_traits<Iter>::difference_type		difference_type;
			typedef	typename	iterator_traits<Iter>::pointer				pointer;
			typedef	typename	iterator_traits<Iter>::reference			reference;

		protected:

			iterator_type	_it;

		public:

			reverse_iterator() 
			: it() {};

			explicit reverse_iterator(iterator_type it)
			: _it(it) {};

			template< typename Iter >
			reverse_iterator(reverse_iterator<Iter> const &rev_it)
			: it(rev_it.base()) {}

			iterator_type base() const
			{
				return this->_it;
			}

			operator reverse_iterator<const Iterator>() const 
			{ 
				return this->_it; 
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