#include "RPN.hpp"

int	ft_stringSet(char const *src, char const *set)
{
	int		n;
	int		index;

	index = 0;
	n = 0;
	while (src[index])
	{
		while (set[n] != src[index])
		{
			if (!set[n])
				return (0);
			n++;
		}
		n = 0;
		index++;
	}
	return (1);
}

void fill_Stack(std::stack<char> & stack, char const *input){
	while (*input)
	{
		if (*input != ' ')
			stack.push(*input);
		input++;
	}
}

int main(int argc, char const *argv[])
{
	std::stack<char> stack;
	if (argc != 2)
	{
		std::cout << FG_RED << "Error, this program need only 1 argument string"
			", one characters sepperated with spaces" << FG_DEFAULT << std::endl;
		return 1;
	}
	if (!ft_stringSet(argv[1], "0123456789+-*/ "))
	{
		std::cout << FG_RED << "Error, this programs only valid input seperated by spaces are >"
			FG_CYAN" */0123456789+- " << FG_DEFAULT << std::endl;
		return 1;
	}
	fill_Stack(stack, argv[1]);
	if (stack.empty())
	{
		std::cout << FG_RED << "Error, empty stack" <<FG_DEFAULT << std::endl;
		return 1;
	}
	RPN(stack);
	return 0;
}
