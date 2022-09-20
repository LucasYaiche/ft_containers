#include <vector>
#include <iostream>

int main(void)
{
	std::vector<int>	first(49, 1);

	std::cout << first.size() << std::endl;
	std::cout << first.capacity()<< std::endl;
	
	first.assign(7, 100);

	std::cout << first.size() << std::endl;
	std::cout << first.capacity()<< std::endl;

}