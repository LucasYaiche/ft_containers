#ifndef REB_BLACK_TREE_HPP
#define REB_BLACK_TREE_HPP

#include <iostream>
#include <string>

namespace ft
{
	template< class T >
	struct Node
	{
		T		data; // truc avex pair
		Node	*parent;
		Node	*left;
		Node	*right;
		int		color;
	};


	template< class T >
	class RedBlackTree
	{
		public:

			typedef Node *NodePtr;

		private:



	}
}



#endif