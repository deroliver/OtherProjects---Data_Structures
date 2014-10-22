#include <iostream>
#include <stdexcept>
#include <string>



int Valid_Input(const std::string &prompt, int low, int high)
{
	if (low >= high)
		throw std::invalid_argument("Invalid Range Of Choices");

	std::cin.exceptions(std::ios_base::failbit);
	int numb = 0;
	while (true)
	{
		try
		{
			while (true)
			{
				std::cout << prompt;
				std::cin >> numb;
				if (numb >= low && numb <= high){
					std::cout << std::endl;
					return numb;
				}
			}
		}
		catch (std::ios_base::failure)
		{
			std::cout << "\n\n*Invalid String passed* -- Please Try Again\n\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');
		}
	}
}