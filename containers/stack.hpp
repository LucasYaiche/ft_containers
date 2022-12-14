#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{

	template <class T, class Container = ft::vector<T> >
	class stack
	{
			//==============================/ Member types /==============================//
		public :

			typedef Container 							container_type;
			typedef typename Container::value_type 		value_type;
			typedef typename Container::size_type 		size_type;
			typedef typename Container::reference 		reference;
			typedef typename Container::const_reference const_reference;

			//==============================/ Member attributes /==============================//
		protected :

			Container c;

			//==============================/ Constructor /==============================//
		public :
			explicit stack (const container_type& ctnr = container_type()) 
			: c(ctnr) 
			{
			};

			//==============================/ Capacity /==============================//
			bool empty() const 
			{
				return this->c.empty();
			};

			size_type size() const 
			{
				return this->c.size();
			};

			//==============================/ Element access /==============================//
			value_type& top() 
			{
				return this->c.back();
			};
			
			const value_type& top() const 
			{
				return this->c.back();
			};

			//==============================/ Modifiers /==============================//
			void push (const value_type& val) 
			{
				this->c.push_back(val);
			};

			void pop() 
			{
				this->c.pop_back();
			};
		
			//==============================/ Operator overloads /==============================//
			friend bool	operator==(const stack &lhs, const stack &rhs)
			{
				return lhs.c == rhs.c;
			};

			friend bool	operator!=(const stack &lhs, const stack &rhs)
			{
				return !(lhs == rhs);
			};

			friend bool	operator<(const stack &lhs, const stack &rhs)
			{
				return lhs.c < rhs.c;
			};

			friend bool	operator>(const stack &lhs, const stack &rhs)
			{
				return rhs < lhs;
			};

			friend bool	operator<=(const stack &lhs, const stack &rhs)
			{
				return !(lhs > rhs);
			};

			friend bool	operator>=(const stack &lhs, const stack &rhs)
			{
				return !(lhs < rhs);
			};
	};
}

#endif