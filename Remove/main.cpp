#include <iostream>
#include <vector>
#include "Solution.h"

// Initialize vector with values
void Init(std::vector<int>& Vector)
{
	for (size_t i = 1; i < 6; i++)
	{
		Vector.push_back(i);
	}
}

// Display vector to screen
void Show(std::vector<int>& Vector)
{
	for (size_t i = 0; i < Vector.size(); i++)
	{
		std::cout << Vector[i] << " ";
	}
	std::cout << "\n";
}

// Solution Using Functor 
void Solutions(std::vector<int>& Vector)
{
	std::cout << "Enter Number: \n";
	int value;
	std::cin >> value;
	Solution<int> temp(value);
	temp(Vector);
}

int main()
{
	std::vector<int> Temp;
	Init(Temp);
	Temp.push_back(5);
	Temp.push_back(5);
	Show(Temp);
	Solutions(Temp);
	Show(Temp);
}