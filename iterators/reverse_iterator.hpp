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
			typedef	typename	iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef	typename	iterator_traits<Iterator>::value_type			value_type;
			typedef	typename	iterator_traits<Iterator>::difference_type		difference_type;
			typedef	typename	iterator_traits<Iterator>::pointer				pointer;
			typedef	typename	iterator_traits<Iterator>::reference			reference;

		protected:

			iterator_type	_it;

		public:

			reverse_iterator() 
			: _it() {};

			explicit reverse_iterator(iterator_type it)
			: _it(it) {};

			template< typename Iter >
			reverse_iterator(reverse_iterator<Iter> const &rev_it)
			: _it(rev_it.base()) {}

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
				iterator_type tmp(this->_it);
				return (*--tmp);
			}

			pointer operator->() const
			{
				return &(operator*());
			}

			reverse_iterator& operator++()
			{
				--this->_it;
				return *this;
			}

			reverse_iterator operator++(int)
			{
				reverse_iterator tmp(*this);
				--this->_it; 
				return tmp;
			}
			
			reverse_iterator& operator--()
			{
				++this->_it;
				return *this;
			}

			reverse_iterator operator--(int)
			{
				reverse_iterator tmp(*this);
				++this->_it; 
				return tmp;
			}

			reverse_iterator operator+(difference_type n) const
			{
				return (reverse_iterator(this->_it - n));
			}

			reverse_iterator operator-(difference_type n) const
			{
				return (reverse_iterator(this->_it + n));
			}

			reverse_iterator& operator+=(difference_type n)
			{
				this->_it -= n;
				return (*this);
			}

			reverse_iterator& operator-=(difference_type n)
			{
				this->_it += n;
				return (*this);
			}

			reference operator[](difference_type n) const
			{
				return *(*this + n);
			}
	};

	template < typename IterL, typename IterR >
	bool operator==(reverse_iterator<IterL> const &lhs, reverse_iterator<IterR> const &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template < typename IterL, typename IterR >
	bool operator!=(reverse_iterator<IterL> const &lhs, reverse_iterator<IterR> const &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template < typename IterL, typename IterR >
	bool operator<(reverse_iterator<IterL> const &lhs, reverse_iterator<IterR> const &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template < typename IterL, typename IterR >
	bool operator>(reverse_iterator<IterL> const &lhs, reverse_iterator<IterR> const &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template < typename IterL, typename IterR >
	bool operator<=(reverse_iterator<IterL> const &lhs, reverse_iterator<IterR> const &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template < typename IterL, typename IterR >
	bool operator>=(reverse_iterator<IterL> const &lhs, reverse_iterator<IterR> const &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template < typename Iterator >
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, reverse_iterator<Iterator> const &rhs)
	{
		return (reverse_iterator<Iterator>(rhs.base() - n));
	}

	template < typename IterL, typename IterR >
	typename reverse_iterator<IterL>::difference_type operator-(reverse_iterator<IterL> const &lhs, reverse_iterator<IterR> const &rhs)
	{
		return (rhs.base() - lhs.base());
	}
}

#endif