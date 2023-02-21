#ifndef SOLUTION_HPP
#define SOLUTION_HPP
template <typename T>
class Solution
{
public:

	// Constructor
	Solution(T value) : value_(value)
	{

	}

	// Template Operator "()"
	template<typename T>
	T operator()(T value)
	{
		return value + value_;
	}

	// Destructor 
	~Solution()
	{

	}

private:
	const T value_;
};
#endif
