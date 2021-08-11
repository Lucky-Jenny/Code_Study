#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_XOR()
{
	char s[32] = {1};
	int i = 0;
	char *p = s;

	sprintf(s, "00000");
	for(i = 0; i < 10; i++){
		if(*p == '\0')
			printf("\\0");
		else
			printf("%c", *p);
		p++;
	}
	printf("\n");

	int a = 4, b = 5;
	i = a ^ b;
	printf("[%d] XOR [%d] = %d\n", a, b, i);
}

void test_atoi_value()
{
	char t1[] = "0x3";
	char t2[] = "2";
	int tmp1 = 0, tmp2 = 0;

	tmp1 = atoi(t1);
	tmp2 = atoi(t2);
	printf("%c:%d  %d:%d\n", t1[0], tmp1, t2[0], tmp2);

}

int main()
{
	//test_XOR();
	test_atoi_value();
	return 0;
}

