#include <vector>
#include <iostream>

#include "includes/vector.hpp"

void	show_vector(std::vector<int>::iterator	first, std::vector<int>::iterator	last)
{
	for(size_t i = 0; first + i < last; i++)
		std::cout << *(first + i) << " ";
	std::cout << std::endl;
}

int main(void)
{
	ft::vector<int> first;                                
	ft::vector<int> second (4,100);                       
	ft::vector<int> third (second.begin(),second.end());  
	ft::vector<int> fourth (third);
	

	std::cout << first.size() << std::endl;
	std::cout << second.size() << std::endl;
	std::cout << third.size() << std::endl;
	std::cout << fourth.size() << std::endl;

	return 0;
}