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
	void operator()(std::vector<T>& value)
	{
		for (auto i = value.begin(); i != value.end(); i++)
		{
			if (*i == value_)
			{
				i = value.erase(i);
				i == value.end() ? i-- : i;
				i == value.begin() ? i++ : i;
				i--;
			}
		}
	}

	// Destructor 
	~Solution()
	{

	}

private:
	T value_;
};
#endif
