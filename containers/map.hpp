#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <string>
// #include "../iterators/map_iterator.hpp"
#include "../utils/utils.hpp"
#include "../utils/pair.hpp"
#include "../iterators/reverse_iterator.hpp"

namespace ft
{

	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator< ft::pair<const Key,T> > >
	class map
	{
			//==============================/ Node /==============================//
		public :
			struct node
			{
				node 					*left;
				node 					*right;
				node 					*parent;
				ft::pair<const Key, T> 	data;

				node()
				: right(NULL), left(NULL), parent(NULL) 
				{
				};

				node(ft::pair<const Key, T> data)
				: left(NULL), right(NULL), parent(NULL), data(data) 
				{
				};
			};


			//==============================/ Map iterator /==============================//
			template <bool is_const>
			class map_iterator
			{
					//==============================/ Map iterator /==============================//
				public :

					typedef ft::pair<const Key, T> 													pair_type;
					typedef typename std::conditional<is_const, const pair_type, pair_type>::type 	value_type;
					typedef typename std::conditional<is_const, const node, node>::type 			node_type;
					typedef ft::bidirectional_iterator_tag 											iterator_category;
					typedef std::ptrdiff_t 															difference_type;
					typedef size_t 																	size_type;
					typedef value_type* 															pointer;
					typedef value_type& 															reference;

					//==============================/ Member attributes /==============================//
				private:

					node_type *_first;
					node_type *_end;
				
					//==============================/ Constructor & overlaod /==============================//
				public:
				
					map_iterator() : _first(NULL), _end(NULL) 
					{
					};

					map_iterator(node_type *first) : _first(first), _end(NULL) 
					{
					};

					map_iterator(node_type *first, node_type *end) : _first(first), _end(end) 
					{
					};

					map_iterator(const map_iterator<is_const> &src) : _first(src.getFirst()), _end(src.getEnd()) 
					{
					};

					template <bool B>
					map_iterator (const map_iterator<B> & src, typename std::enable_if<!B>::type* = 0) 
					: _first(src.getFirst()), _end(src.getEnd()) 
					{
					};

					map_iterator &operator=(const map_iterator &rhs) 
					{
						if (this != &rhs)
						{
							this->_first = rhs.getFirst();
							this->_end = rhs.getEnd();
						}
						return *this;
					};

					//==============================/ Getters /==============================//
					node_type	*getFirst() const
					{
						return this->_first;
					};
					
					node_type	*getEnd() const
					{
						return this->_end;
					};


					node_type *base() const 
					{
						return this->_first;
					};



					//==============================/ Operator overloads /==============================//
					value_type& operator*() const 
					{
						return this->_first->data;
					};

					value_type* operator->() const 
					{
						return &this->_first->data;
					};

					map_iterator &operator++() 
					{
						if (this->_first == NULL)
							return *this;
						else if (!this->_first->parent && !this->_first->right)
						{
							this->_end = this->_first;
							this->_first = NULL;
						}
						else if (this->_first->right)
							this->_first = down_bigger_node();
						else
							this->_first = up_bigger_node(this->_first);
						return *this;
					};

					map_iterator operator++(int) 
					{
						map_iterator tmp = *this;
						this->operator++();
						return tmp;
					};

					map_iterator &operator--() 
					{
						if (this->_first == NULL)
						{
							if(_end)
								this->_first = this->_end;
						}
						else if (!this->_first->parent && !this->_first->left)
							this->_first = NULL;
						else if (_first->left)
							this->_first = down_smallest_node();
						else
							this->_first = up_smallest_node(this->_first);
						return *this;
					};

					map_iterator operator--(int) 
					{
						map_iterator tmp = *this;
						this->operator--();
						return tmp;
					};


					bool operator==(const map_iterator rhs) const 
					{
						return this->_first == rhs.getFirst();
					};

					bool operator!=(const map_iterator rhs) const 
					{
						return this->_first != rhs.getFirst();
					};

					//==============================/ Others /==============================//
				private :

					node_type *up_bigger_node(node_type *node)
					{
						node_type *next;

						if (!node->right)
						{
							next = node;
							if (next->parent->right != next && next != next->parent->left)
								return (NULL);
							while (next->parent != NULL && next == next->parent->right)
								next = next->parent;
							next = next->parent;
						}
						else
						{
							next = node->right;
							while (next->left)
								next = next->left;
						}
						return (next);
					};

					node_type *down_bigger_node()
					{
						node_type *next = this->_first->right;

						while (next->left)
							next = next->left;
						return next;
					};

					node_type *up_smallest_node(node_type *node)
					{
						node_type	*prev;

						if (!node->left || !node->left)
						{
							prev = node;
							while (prev->parent != NULL && prev == prev->parent->left)
								prev = prev->parent;
							prev = prev->parent;
						}
						else
						{
							prev = node->left;
							while (prev->right != NULL)
								prev = prev->right;
						}
						return (prev);
					};

					node_type *down_smallest_node()
					{
						node_type *next = this->_first->left;

						while (next->right)
							next = next->right;
						return next;
					};
			};

				//==============================/ Member types /==============================//
			public:

				typedef	Key												key_type;
				typedef	T												mapped_type;
				typedef	ft::pair<const key_type, mapped_type>			value_type;
				typedef	Compare											key_compare;

				//==============================/ Value compare /==============================//
			class value_compare
			{   
				friend class map;
				protected:

					Compare comp;
					value_compare (Compare c) : comp(c)
					{
					};

				public:

					typedef bool 		result_type;
					typedef value_type 	first_argument_type;
					typedef value_type 	second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					};
			};

				//==============================/ Member types /==============================//
				typedef typename Alloc::template rebind<node>::other		allocator_type;
				typedef	typename allocator_type::reference				reference;
				typedef	typename allocator_type::const_reference		const_reference;
				typedef	typename allocator_type::pointer				pointer;
				typedef	typename allocator_type::const_pointer			const_pointer;
				typedef map_iterator<false>								iterator;
				typedef map_iterator<true>								const_iterator;
				typedef ft::reverse_iterator<iterator>					reverse_iterator;
				typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
				typedef typename allocator_type::size_type				size_type;

				//==============================/ Member attributes /==============================//
			private:

				allocator_type 	_alloc;
				node			*_root;
				key_compare		_comp;

				//==============================/ Constructor & overload /==============================//
			public:

				explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
				: _alloc(alloc), _root(NULL), _comp(comp)
				{
				};

				template <class InputIterator>  
				map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
				:  _alloc(alloc), _root(NULL), _comp(comp)
				{
					insert(first, last);
				};
				
				map (const map& x)
				: _alloc(x._alloc), _root(NULL), _comp(x._comp)
				{
					this->clear();
					this->insert(x.begin(), x.end());
				};

				map& operator=(const map& rhs)
				{
					if (this != &rhs)
					{
						this->clear();
						this->insert(rhs.begin(), rhs.end());
						this->_alloc = rhs._alloc;
						this->_comp = rhs._comp;
					}
					return *this;
				};

				//==============================/ Destructor /==============================//
				~map()
				{
					this->clear();
				};

				allocator_type get_allocator() const
				{
					return this->_alloc;
				};

				//==============================/ Element access /==============================//
				mapped_type& at( const Key& key )
				{
					iterator	it;

					if(count(key))
					{
						it = find(key);
						return it.base().second;
					}
					else
						throw std::out_of_range("map");
				};

				const mapped_type& at( const Key& key ) const
				{
					return at(key);
				};

				mapped_type& operator[]( const Key& key )
				{
					(*((this->insert(ft::make_pair(key, mapped_type()))).first));
					return find(key)->second;
				};

				//==============================/ Iterators /==============================//
				iterator begin() 
				{
					iterator it(search_highest(this->_root));

					return it;
				};

				const_iterator begin() const 
				{
					return const_iterator(search_highest(this->_root));
				};

				iterator end() 
				{
					return iterator(NULL, search_lowest(this->_root));
				};

				const_iterator end() const 
				{
					return const_iterator(NULL, search_lowest(this->_root));
				};

				reverse_iterator rbegin() 
				{
					return reverse_iterator(end());
				};
				
				const_reverse_iterator rbegin() const 
				{
					return const_reverse_iterator(end());
				};

				reverse_iterator rend() 
				{
					return reverse_iterator(begin());
				};
				
				const_reverse_iterator rend() const 
				{
					return const_reverse_iterator(begin());
				};

				//==============================/ Capacity /==============================//
				bool empty() const 
				{
					return begin() == end();
				};

				size_type	size() const
				{
					return tree_len();
				};

				size_type max_size() const
				{
					return _alloc.max_size();
				};

				//==============================/ Modifiers /==============================//
				void clear()
				{
					if(this->_root)
						this->delete_tree(this->_root);
						this->_root = NULL;
				};

				pair<iterator,bool> insert(const value_type& value)
				{
					iterator	it(this->find(value.first));

					if(it == this->end())
					{
						this->add_node(value);
						it = this->find(value.first);
						return pair<iterator,bool>(it, true);
					}
					return pair<iterator, bool>(it, false);
				};

				iterator insert( iterator position, const value_type& value )
				{
					(void)position;
					return insert(value).first;
				};

				template< class InputIt >
				void insert( InputIt first, InputIt last )
				{
					for(; first != last; first++)
						this->insert(*first);
				};

				void erase( iterator pos )
				{
					if (pos != this->end())
						delete_node(pos.base());
				};

				size_type erase( const Key& key )
				{
					size_type returned = 0;

					if(count(key))
					{
						this->erase(this->find(key));
						returned = 1;
					}
					return returned;
				};

				void erase( iterator first, iterator last )
				{
					while(first != last)
						erase((first++).base());
				};

				void swap( map& x )
				{
					allocator_type	temp_alloc = this->_alloc;
					node 			*temp_root = this->_root;
					Compare 		temp_cmp = this->_comp;

					this->_alloc = x._alloc;
					this->_root = x._root;
					this->_comp = x._comp;

					x._alloc = temp_alloc;
					x._root = temp_root;
					x._comp = temp_cmp;
				};

				//==============================/ Lookup /==============================//
				size_type count( const Key& key ) const
				{
					size_type n = 1;

					if(find(key) == end())
						n = 0;
					return n;
				};

				iterator find( const Key& key )
				{
					node	*n = search_node(this->_root, key);
					if (n)
						return iterator(n);
					return this->end();
				};
				const_iterator find( const Key& key ) const
				{
					node	*n = search_node(this->_root, key);
					if (n)
						return const_iterator(n);
					return this->end();
				};

				pair<iterator,iterator> equal_range( const Key& key )
				{
					return ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
				};
				
				pair<const_iterator,const_iterator> equal_range( const Key& key ) const
				{
					return ft::pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));
				};

				iterator lower_bound( const Key& key )
				{
					iterator	it = this->begin();

					for (; it != this->end(); it++)
					{
						if (!(this->_comp(it->first, key)))
							break ;
					}
					return (it);
				};

				const_iterator lower_bound( const Key& key ) const
				{
					const_iterator	it = this->begin();

					for (; it != this->end(); it++)
					{
						if (!(this->_comp(it->first, key)))
							break ;
					}
					return (it);
				};

				iterator upper_bound( const Key& key )
				{
					iterator	it = this->begin();

					for (; it != this->end(); it++)
					{
						if (this->_comp(key, it->first))
							return it;
					}
					return (it);
				};

				const_iterator upper_bound( const Key& key ) const
				{
					const_iterator	it = this->begin();

					for (; it != this->end(); it++)
					{
						if (this->_comp(key, it->first))
							return it;
					}
					return (it);
				};

				//==============================/ Observers /==============================//
				key_compare key_comp() const
				{
					return this->_comp;
				};

				value_compare value_comp() const
				{
					return value_compare(this->_comp);
				};

					//==============================/ BST functions /==============================//
				private : 

					node	*add_node(const	value_type &n)
					{
						node	*new_node = this->_alloc.allocate(1);

						this->_alloc.construct(new_node, n);
						if (!this->_root)
							this->_root = new_node;
						else
						{
							node	*current = this->_root;

							while(current)
							{
								if(this->_comp(current->data.first, n.first))
								{
									if(!current->right)
									{
										current->right = new_node;
										current->right->parent = current;
										break;
									}
									current = current->right;
								}
								else
								{
									if(!current->left)
									{
										current->left = new_node;
										current->left->parent = current;
										break; // a changer
									}
									current = current->left;
								}
							}
							new_node->parent = current;
						}
						return new_node;
					};

					void delete_node(node *n) 
					{
						node 	*tmp = n;
						node	*next = n->left;
						node	*old = n;

						if(!n->left || !n->right)
						{
							if(!n->left)
								next = n->right;
							if (!old->parent)
								this->_root = next;
							else if (old == old->parent->left)
								old->parent->left = next;
							else
								old->parent->right = next;
							if (next)
								next->parent = old->parent;
						}
						else if(n->right && n->left)
						{
							tmp = search_highest(n->right);
							if(tmp->parent == n && tmp->right)
								tmp->right->parent = tmp;
							else
							{
								if (!tmp->parent)
									this->_root = tmp->right;
								else if (tmp == tmp->parent->left)
									tmp->parent->left = tmp->right;
								else
									tmp->parent->right = tmp->right;
								if (tmp->right)
									tmp->right->parent = tmp->parent;
								tmp->right = n->right;
								if(tmp->right)
									tmp->right->parent = tmp;
							}
							if (!n->parent)
								this->_root = tmp;
							else if (n == n->parent->left)
								n->parent->left = tmp;
							else
								n->parent->right = tmp;
							if (tmp)
								tmp->parent = n->parent;
							tmp->left = n->left;
							if(tmp->left)
								tmp->left->parent = tmp;
						}
						_alloc.destroy(n);
						_alloc.deallocate(n, 1);
					};

					void	delete_tree(node *n)
					{
						std::allocator<node> tmp_alloc;

						if (n->left)
							delete_tree(n->left);
						if (n->right)
							delete_tree(n->right);
						tmp_alloc.destroy(n);
						tmp_alloc.deallocate(n, 1);
						n = NULL;
					};


					node	*search_highest(node *root) const
					{
						node	*tmp = root;

						if (!tmp)
							return NULL;
						while(tmp && tmp->left)
							tmp = tmp->left;
						return tmp;
					};
					
					node	*search_lowest(node *root) const
					{
						node	*tmp = root;

						if (!tmp)
							return NULL;
						while(tmp && tmp->right)
							tmp = tmp->right;
						return tmp;
					};

					node	*search_node(node *root, const Key &key) const
					{
						node	*tmp = root;

						while(tmp && tmp->data.first != key)
						{
							if (this->_comp(key, tmp->data.first))
								tmp = tmp->left;
							else
								tmp = tmp->right;
						}
						return tmp;
					};

					size_type	tree_len() const
					{
						size_type	i = 0;
						for (const_iterator it = begin(); it != end(); it++)
							i++;
						return i;
					};
	};
	
	//==============================/ Operator overloads /==============================//
	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) 
	{
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	};
	
	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) 
	{
		return !(lhs == rhs);
	};
	
	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) 
	{
		return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	};
	
	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) 
	{
		return !(rhs < lhs);
	};
	
	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) 
	{
		return rhs < lhs;
	};
	
	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) 
	{
		return !(lhs < rhs);
	};
	
	template< class Key, class T, class Compare, class Alloc >
	void swap( ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs ) 
	{
		lhs.swap(rhs);
	};
}

#endif