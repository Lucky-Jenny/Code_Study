#include <stdio.h>

#define WHAT 0

struct Object{
	int num;
	char *name;
	char value[128];
};
typedef struct Object Object_t;

Object_t lx[] = {
	{ 0, "xiao", "basketball" },
	{ 1, "gyj", "love" },
#if WHAT						// define will affect the length of struct.
	{ 2, "alex", "snooker" },
	{ 3, "niko", "major" },
	{ 4, "kd", "champion" },
#endif
	{ 99, NULL, 0 }
};

void Struct_3()
{
	int i = 0, len = 0;

	len = sizeof(lx)/sizeof(Object_t);
	printf("len=%d\n", len);
	for(i = 0; (i < len) && (lx[i].name); i++){
		printf("%d\t%s\t%s\n", lx[i].num, lx[i].name, lx[i].value);
	}

}

void Array_2d()
{
	int i = 0, j = 0;
	static char we[4][4] = {{"abcd"}};

	// sizeof("what")=5  because it contains "/0"
	printf("sizeof(\"what\")=%ld\n", sizeof("what"));
	//In the way of snprintf(), we[][] should be &we[][]
	i = snprintf(&we[1][0], sizeof("what"), "what");	
	if(i < 0) return;

	// If the length is beyond this line, th rest will write into next line.
	i = snprintf(&we[2][0], sizeof("whateew"), "whateew");
	if(i < 0) return;

	printf("Print the Array.\n");
	// print the result of 2d-array
	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 4; j++){
			printf("%c\t",we[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	// Struct with 3 items
	Struct_3();

	printf("=============================\n");
	// 2 Degree Array
	Array_2d();

}

