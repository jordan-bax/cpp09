#include <stdio.h>
#include <stdlib.h>

void pf(int number)
{
	int size = 250;
	int factors[size];
	int index = 0;
	int d=2;
	while(number>1)
	{

		while((number%d)==0)
		{
			factors[index] = d;
			number=number/d;
			index++;
		}
		d+=1;
	}
	printf("%d", factors[0]);
	for (int i = 1; i < index; i++)
	{
		printf("*%d", factors[i]);
	}
}

int main(int argc, char const *argv[])
{
	if (argc != 2)
		return 1;	
	pf(atoi(argv[1]));
	return 0;
}
