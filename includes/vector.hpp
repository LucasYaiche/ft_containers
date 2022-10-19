#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <string>
#include "../utils/utils.hpp"
#include "../iterators/random_access_iterator.hpp"
#include "../iterators/reverse_iterator.hpp"
namespace ft
{
	template< class T, class Allocator = std::allocator<T> > 
	class vector
	{
			//==============================/ Member types /==============================//
		public:

			typedef             T													value_type;
            typedef             Allocator											allocator_type;
            typedef typename    allocator_type::reference							reference;
            typedef typename    allocator_type::const_reference						const_reference;
            typedef typename    allocator_type::pointer								pointer;
            typedef typename    allocator_type::const_pointer						const_pointer;
            typedef typename    ft::random_access_iterator<T>						iterator;
            typedef typename    ft::random_access_iterator<const T>					const_iterator;
            typedef typename    ft::reverse_iterator<iterator> 						reverse_iterator;
            typedef typename    ft::reverse_iterator<const_iterator>				const_reverse_iterator;
            typedef typename    allocator_type::difference_type						difference_type;
            typedef typename    allocator_type::size_type							size_type;

			//==============================/ Member attributes /==============================//
		private:

			allocator_type	_alloc;
			pointer			_begin;
			size_type		_size;
			size_type		_capacity;

			//==============================/ Constructor & overlaod /==============================//
		public:

			explicit	vector(const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _begin(NULL), _size(0), _capacity(0)
			{
			};

			explicit 	vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _size(n), _capacity(n * 2) 
			{
				this->_begin = this->_alloc.allocate(this->_capacity, 0);
				for (size_type i = 0; i < this->_size; i++)
				{
					this->_alloc.construct(this->_begin + i, val);
				}
			};

			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL)
			: _alloc(alloc), _size(distance(first, last)), _capacity(distance(first, last) * 2)
			{
				this->_begin = this->_alloc.allocate(this->_capacity, 0);
				for (size_type i = 0; i < this->_size ; i++)
				{
					this->_alloc.construct(this->_begin + i, *first++);
				}
			};

			vector (const vector& x)
			: _alloc(x._alloc), _begin(x._begin), _size(x._size), _capacity(x._capacity)
			{
				this->_begin = this->_alloc.allocate(this->_capacity, 0);
				for (size_type i = 0; i < this->_size; i++)
				{
					this->_alloc.construct(this->_begin + i, *(x._begin + i));
				}
			};

			vector& operator= (const vector& x)
			{
				if (this != &x)
				{
					this->_alloc = x._alloc;
					this->_begin = x._begin;
					this->_size = x._size;
					this->_capacity = x._capacity;
				}
				return *this;
			};

			//==============================/ Destructor /==============================//

			~vector()
			{
				for (size_type i = 0; i < this->_size; i++)
				{
					this->_alloc.destroy(this->_begin + i);
				}
				this->_alloc.deallocate(this->_begin, this->_capacity);
			};

			//==============================/ Iterators /==============================//

			iterator begin()
			{
				return this->_begin;
			};

			const_iterator begin() const
			{
				return this->_begin;
			};

			iterator end()
			{
				return (this->_begin + this->_size);
			};

			const_iterator end() const
			{
				return (this->_begin + this->_size);
			};
			reverse_iterator rbegin()
			{
				return reverse_iterator(end());
			};
			const_reverse_iterator rbegin() const
			{
				return reverse_iterator(end());
			};

			reverse_iterator rend()
			{
				return reverse_iterator(begin());
			};

			const_reverse_iterator rend() const
			{
				return reverse_iterator(begin());
			};

			//==============================/ Capacity /==============================//
			
			size_type	size() const
			{
				return this->_size;
			};

			void resize (size_type n, value_type val = value_type())
			{
				size_type	dist = this->_size - n;
				if (this->_size > n)
				{
					for (size_type i = this->_size; i > dist; i++)
					{
						this->_alloc.destroy(this->_begin + i);
					}
				}
				else if (this->_size < n)
				{
					for (size_type i = this->_size; i < dist; i++)
					{
						this->_alloc.construct(this->_begin + i, val);
					}
				}
			};

			size_type capacity() const
			{
				return this->_capacity;
			};

			bool empty() const
			{
				return this->_size == 0;			
			};

			size_type max_size() const
			{
       			return _alloc.max_size();
   			}

			void reserve (size_type n)
			{
				if (n  > this->_alloc.max_size())
					throw std::length_error("vector::reserve: too high");
				if (n > this->_capacity)
				{
					pointer vec = this->_alloc.allocate(n);
					size_type old_size = this->_size;
					for (size_type i = 0; i < this->_size; i++)
						this->_alloc.construct(vec + i, this->_begin[i]);
					this->clear();
					this->_alloc.deallocate(this->_begin, this->_capacity);
					this->_begin = vec;
					this->_size = old_size;
					this->_capacity = n;
				}
			};

			//==============================/ Element access /==============================//

			reference operator[] (size_type n)
			{
				return *(this->_begin + n);
			};

			const_reference operator[] (size_type n) const
			{
				return *(this->_begin + n);
			};

			reference at (size_type n)
			{
				if (this->_size <= n)
					throw(std::out_of_range("vector"));
				return *(this->_begin + n);
			};

			const_reference at (size_type n) const
			{
				if (this->_size <= n)
					throw(std::out_of_range("vector"));
				return *(this->_begin + n);
			};

			reference front()
			{
				return *(this->_begin);
			};

			const_reference front() const
			{
				return *(this->_begin);
			};

			reference back()
			{
				return *(this->_begin + this->_size - 1);
			};

			const_reference back() const
			{
				return *(this->_begin + this->_size - 1);
			};	

			//==============================/ Modifiers /==============================//

			void assign (size_type n, const value_type& val)
			{
				this->reserve(n);
				for (size_type i = 0; i < this->_size; i++)
					*(this->_begin + i) = val;
			};

			template <class InputIterator>
  			void assign (InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL)
			{
				size_type	dist = distance(first, last);
				this->reserve(dist);
				for (size_type i = 0; i < dist; i++)
					*(this->_begin + i) = *(first + i);
			};

			void push_back (const value_type& val)
			{
				if(this->_size < this->_capacity)
				{
					this->_alloc.construct(this->_begin, val);
					this->_size += 1;
				}
				else
				{
					resize(this->_size + 1, val);
				}
			};

			void pop_back()
			{
				if (this->_size)
					this->_alloc.destroy(this->_begin + this->_size - 1);
				this->_size -= 1;
			};

			iterator insert (iterator position, const value_type& val)
			{
				insert(position, 1, val);
				return (position);
			};

			void insert (iterator position, size_type n, const value_type& val)
			{
				size_type	dist = distance(position, this->end());

				reserve(this->_size + n);
				for (size_type i = this->_size; i > dist; i--)
				{
					*(this->end() - i - 1) = *(this->end() - i);
				}
				*(position) = val;

			};

			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL)
			{
				size_type	dist = distance(position, this->end());

				reserve(this->_size + dist);
				for (size_type i = this->_size; i > dist; i--)
				{
					*(this->end() - i - 1) = *(this->end() - i);
				}
				dist = distance(first, last);
				for(InputIterator it = first; it < last; it++)
				{
					*(position++) = *(it);
				}
			};

			
			iterator erase (iterator position)
			{
				size_type i = 0;
				for (iterator it = this->_begin; it < position; it++)
					i++;
				this->_alloc.destroy(this->_begin + i);
				for (size_type j = 0; j < i; j++)
				{
					*(this->_begin + i + j) = *(this->_begin + i + j + 1);
				}
				this->_size--;
				return position;
			};

			iterator erase (iterator first, iterator last)
			{
				size_type i = 0;
				for (iterator it = this->_begin; it < first; it++)
					i++;
				size_type	dist = distance(first, last);

				for (size_type j = 0; j < dist; j++)
					this->_alloc.destroy(this->_begin + i + j);
				for (size_type j = 0; j < dist; j++)
					*(this->_begin + i + j) = *(this->_begin + i + j + 1);
				this->_size -= dist;
				return first;
			};

			
			void swap (vector& x)
			{
				allocator_type	temp_alloc = this->_alloc;
				pointer			temp_begin = this->_begin;
				size_type		temp_size = this->_size;
				size_type		temp_capacity = this->_capacity;

				this->_alloc = x._alloc;
				this->_begin = x._begin;
				this->_size = x._size;
				this->_capacity = x._capacity;

				x._alloc = temp_alloc;
				x._begin = temp_begin;
				x._size = temp_size;
				x._capacity = temp_capacity;
			};
			
			void clear()
			{
				this->_size = 0;
				for (size_type i = 0; i < this->_size; i++)
					this->_alloc.destroy(this->_begin + i);
			}


			//==============================/ Allocators /==============================//

			allocator_type get_allocator() const
			{
				return (this->_alloc);
			};

		};
	//==============================/ Other /==============================//

	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (lhs.size() != rhs.size() && equal (lhs.begin(), lhs.end(), rhs.begin()));
	};

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(lhs == rhs);
	};

	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	};

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(rhs < lhs);
	};

	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	};

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(lhs < rhs);
	};

	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	};
}

#endif