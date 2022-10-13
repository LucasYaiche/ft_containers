#include <vector>
#include <iostream>

// #include "includes/vector.hpp"

void	show_vector(std::vector<int>::iterator	first, std::vector<int>::iterator	last)
{
	for(size_t i = 0; first + i < last; i++)
		std::cout << *(first + i) << " ";
	std::cout << std::endl;
}

int main(void)
{
	std::vector<int> test;
	
	test.assign(7, 1);
	show_vector(test.begin(), test.end());
	test.assign(6,2);
	show_vector(test.begin(), test.end());
	test.assign(7,3);
	show_vector(test.begin(), test.end());

	return 0;
}