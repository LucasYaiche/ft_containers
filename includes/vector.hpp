#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <string>
#include "../iterators/random_access_iterator.hpp"
#include "../iterators/reverse_iterator.hpp"
namespace ft
{
	template< class T, class Allocator = std::allocator<T> > 
	class vector
	{
			//==============================/ Member types /==============================//
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
			: _alloc(alloc), _begin(NULL), _size(0), _capacity(0), {};

			explicit 	vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _size(n), _capacity(n * 2) 
			{
				this->_begin = this->_alloc.allocate(this->_capacity, 0);
				for (int i = 0; i < this->_size; i++)
				{
					this->_alloc.construct(this->_begin + i, val);
				}
			};

			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) 
			: _alloc(alloc), _size(last - first), _capacity(n * 2)
			{
				this->_begin = this->_alloc.allocate(this->_capacity, 0);
				for (int i = 0; i < this->_size ; i++)
				{
					this->_alloc.construct(this->_begin + i, *first++);
				}
			};

			vector (const vector& x) : _alloc(x._alloc), _begin(x._begin), _size(x._size), _capacity(x._capacity)
			{
				this->_begin = this->_alloc.allocate(this->_capacity, 0);
				for (int i = 0; i < this->_size; i++)
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
				for (int i = 0; i < this->_size; i++)
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

			void resize (size_type n, value_type val = value_type());

			size_type capacity() const
			{
				return this->_capacity;
			};

			bool empty() const
			{
				if (this->_size)
					return false;
				return true;			
			};

			void reserve (size_type n);

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
				if (this->_size < n)
					throw(std::out_of_range("vector"));
				return *(this->_begin + n);
			};

			const_reference at (size_type n) const
			{
				if (this->_size < n)
					throw(std::out_of_range("vector"));
				return *(this->_begin + n);
			};

			reference front()
			{
				return *(this->_size);
			};

			const_reference front() const
			{
				return *(this->_size);
			};

			reference back()
			{
				return *(this->_begin + this->_size - 1);
			};

			const_reference back() const
			{
				return *(this->_begin);
			};

			value_type* data();

			const value_type* data() const;		

			//==============================/ Modifiers /==============================//

			void assign (size_type n, const value_type& val)
			{
				this->_size(n);
				if (n > this->_capacity)
					this->_capacity = n;
				//rajouter la partie qui clear le vector
			};

			template <class InputIterator>
  			void assign (InputIterator first, InputIterator last)
			{

			};

			void push_back (const value_type& val)
			{
				if(this->_size < this->_capacity)
				{
					this->_alloc.construct(this->_begin + 1, val);
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
					this->_alloc.destroy(this->_begin + (this->_size - 1));
				this->_size -= 1;
			
			};

			iterator insert (iterator position, const value_type& val);
			void insert (iterator position, size_type n, const value_type& val);
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last);
			
			iterator erase (iterator position);
			iterator erase (iterator first, iterator last);
			
			void swap (vector& x);
			
			void clear();

			//==============================/ Allocators /==============================//

			allocator_type get_allocator() const
			{
				return (this->_alloc);
			};


			//==============================/ Other /==============================//

			template <class T, class Alloc>
			bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
			template <class T, class Alloc>
			bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
			template <class T, class Alloc>
			bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
			template <class T, class Alloc>
			bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
			template <class T, class Alloc>
			bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
			template <class T, class Alloc>
 			bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
			template <class T, class Alloc>
			void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);
	};
}

#endif