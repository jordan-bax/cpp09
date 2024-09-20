#include <stdio.h>
int jacobsthal(int n){
	// first base case
	if (n == 0)
		return 0;

	// second base case
	if (n == 1)
		return 1;

	// recurse!
	return jacobsthal(n - 1) + 2 * jacobsthal(n - 2);
}
int main(void)
{
	for (int i = 0; i < 20; i++)
	{
		printf("%d - %d  ", jacobsthal(i), i);
	}
	return 0;
}
