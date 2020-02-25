#include "stdio.h"
#include "stdlib.h"

void test(int a[], int size)
{
	for(int i=0;i<size;i++) {
		printf("test, a[%d]: %d\n", i, a[i]);
	}
}

void test_p(int *a, int size)
{
	for(int i=0;i<size;i++) {
		printf("test_p, a[%d]: %d\n", i, a[i]);
	}
}

int main()
{
	int a[10] = {0,1,2,3,4,5,6,7,8,9};

	printf("a: %p, &a[0]: %p\n", a, &a[0]);

	test(a, 10);
	test(&a[3], 7);

	test_p(a, 10);
	test_p(&a[3], 7);
}
