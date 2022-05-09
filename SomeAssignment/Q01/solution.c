#include <stdio.h>

int times_two(int value);

int main(void)
{
	int value;
	scanf("%d", &value);

	printf("%d", times_two(value));
	return 0;
}

int times_two(int value)
{
	return value * 2;
}

