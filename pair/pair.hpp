#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft
{
	template< class T1, class T2 >
	struct pair
	{
		typedef	T1	first;
		typedef	T2	second;

		T1	first;
		T2	second;

		pair();

		pair( const T1& x, const T2& y );
		
		template< class U1, class U2 >
		pair( const pair<U1, U2>& p );

		pair& operator=( const pair& other );
	};
}

#endif