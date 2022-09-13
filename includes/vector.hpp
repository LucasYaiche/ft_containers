#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <string>

namespace ft
{
	template< class T, class Allocator = std::allocator<T> > 
	class vector
	{
			//==============================/ Member types /==============================//
		public:
			
			typedef typename	size_t												size_type;
			typedef typename	std::allocator<value_type>							allocator_type;
		
		protected:

			typedef typename	T													value_type;
			typedef typename	std::allocator_type::reference						reference;
			typedef typename	std::allocator_type::const_reference				const_reference;
			typedef typename	std::allocator_type::pointer						pointer;
			typedef typename	std::allocator_type::const_pointer					const_pointer;
			typedef typename	ft::stack::container_type::iterator					iterator;
			typedef typename	ft::stack::container_type::const_iterator			const_iterator;
			typedef typename	ft::stack::container_type::reverse_iterator			reverse_iterator;
			typedef typename	ft::stack::container_type::const_reverse_iterator	const_reverse_iterator;
			typedef typename	std::iterator_traits<iterator>::difference_type		difference_type;

			//==============================/ Member attributes /==============================//
		private:

			size_type	_size;
			size_type	_max_size;
			size_type	_capacity;
			bool		_empty;

			//==============================/ Constructor & overlaod /==============================//
		public:

			explicit	vector(const allocator_type& alloc = allocator_type());
			explicit 	vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
			vector (const vector& x);
			vector& operator= (const vector& x);

			//==============================/ Destructor /==============================//

			~vector();

			//==============================/ Iterators /==============================//

			iterator begin();
			const_iterator begin() const;
			iterator end();
			const_iterator end() const;
			reverse_iterator rbegin();
			const_reverse_iterator rbegin() const;
			reverse_iterator rend();
			const_reverse_iterator rend() const;
			const_iterator cbegin() const noexcept;
			const_iterator cend() const noexcept;
			const_reverse_iterator crbegin() const noexcept;
			const_reverse_iterator crend() const noexcept;

			//==============================/ Capacity /==============================//
			
			size_type	size() const
			{
				return this->_size;
			};
			
			size_type	size() const
			{
				return this->_capacity;
			};

			void resize (size_type n, value_type val = value_type());

			size_type capacity() const;

			bool empty() const;

			void reserve (size_type n);

			void shrink_to_fit();

			//==============================/ Element access /==============================//

			reference operator[] (size_type n);
			const_reference operator[] (size_type n) const;
			reference at (size_type n);
			const_reference at (size_type n) const;
			reference front();
			const_reference front() const;
			reference back();
			const_reference back() const;
			value_type* data() noexcept;
			const value_type* data() const noexcept;		

			//==============================/ Modifiers /==============================//

			template <class InputIterator>
  			void assign (InputIterator first, InputIterator last);
			void assign (size_type n, const value_type& val);
			void push_back (const value_type& val);
			void pop_back();
			ft::iterator insert (ft::iterator position, const value_type& val);
			void insert (ft::iterator position, size_type n, const value_type& val);
			template <class InputIterator>
			void insert (ft::iterator position, InputIterator first, InputIterator last);
			ft::iterator erase (ft::iterator position);
			ft::iterator erase (ft::iterator first, ft::iterator last);
			void swap (vector& x);
			void clear();
			template <class... Args>
			ft::iterator emplace (ft::const_iterator position, Args&&... args);
			template <class... Args>
			void emplace_back (Args&&... args);

			//==============================/ Allocators /==============================//

			allocator_type get_allocator() const;


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