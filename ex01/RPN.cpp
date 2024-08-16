#include "RPN.hpp"
//if operator calls recursice operator function then or else sets sum
static bool	what_RPN(std::stack<char> & stack, int & sum);
static void	RPN_is_Empty(std::stack<char> & stack)
{
	if (stack.empty())
	{
		std::cout << FG_RED << "Error, the stack ran empty in the middle of a calculation."
			" remember you can't use negetive numbers" << FG_DEFAULT << std::endl;
		exit(1);
	}
}

static int		RPN_multiplacation(std::stack<char> & stack)
{
	int	left_sum;
	int	right_sum;
	

	RPN_is_Empty(stack);
	what_RPN(stack, right_sum);
	RPN_is_Empty(stack);
	what_RPN(stack, left_sum);
	return left_sum * right_sum;
}
static int		RPN_division(std::stack<char> & stack)
{
	int	left_sum;
	int	right_sum;
	

	RPN_is_Empty(stack);
	what_RPN(stack, right_sum);
	RPN_is_Empty(stack);
	what_RPN(stack, left_sum);
	if (right_sum == 0 && left_sum == 0)//NaN
	{
		std::cout << FG_LGREEN << "NaN" << FG_DEFAULT << std::endl;
		exit(0);
	}
	if (right_sum == 0)//infinity
	{
		std::cout << FG_LGREEN << "infinity" << FG_DEFAULT << std::endl;
		exit(0);
	}
	if (left_sum == 0)
		return 0;
	return left_sum / right_sum;
}
static int		RPN_minus(std::stack<char> & stack)
{
	int	left_sum;
	int	right_sum;
	

	RPN_is_Empty(stack);
	what_RPN(stack, right_sum);
	RPN_is_Empty(stack);
	what_RPN(stack, left_sum);
	return left_sum - right_sum;
}
static int		RPN_plus(std::stack<char> & stack)
{
	int	left_sum;
	int	right_sum;
	

	RPN_is_Empty(stack);
	what_RPN(stack, right_sum);
	RPN_is_Empty(stack);
	what_RPN(stack, left_sum);
	return left_sum + right_sum;
}


static bool	what_RPN(std::stack<char> & stack, int & sum)
{
	char	top;

	top = stack.top();
	if (top == '+')
	{
		stack.pop();
		sum = RPN_plus(stack);
		return true;
	}
	if (top == '-')
	{
		stack.pop();
		sum = RPN_minus(stack);
		return true;
	}
	if (top == '/')
	{
		stack.pop();
		sum = RPN_division(stack);
		return true;
	}
	if (top == '*')
	{
		stack.pop();
		sum = RPN_multiplacation(stack);
		return true;
	}
	sum = top - '0';
	stack.pop();
	return 0;
}

int	RPN(std::stack<char> & stack)
{
	int		sum = 0;

	if (!what_RPN(stack, sum))
	{
		std::cout << FG_RED << "Error, this program found a number left in the stack without an"
			" operator to make a calculation. remember the numbers can't be higher than 9" << FG_DEFAULT << std::endl;
		return 0;
	}
	if (!stack.empty())
	{
		std::cout << FG_RED << "Error, this program found a number left in the stack without an"
			" operator to make a calculation. remember the numbers can't be higher than 9" << FG_DEFAULT << std::endl;
		return 1;
	}

	std::cout << FG_LGREEN << sum << FG_DEFAULT << std::endl;
	return 0;
}