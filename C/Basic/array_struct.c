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
#if WHAT		// Macro affect struct.
	{ 2, "alex", "snooker" },
	{ 3, "niko", "major" },
	{ 4, "kd", "champion" },
#endif
	{ -1, NULL, 0 }
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
	static char we[4][8] = {{0}, {0}, {0}, {"abcd"}};

	// sizeof("what")=5  because it contains "/0"
	printf("sizeof(\"what\")=%ld\n", sizeof("what"));
	i = snprintf(we[0], sizeof(we[0]), "what");	
	if(i < 0)
		return;

	i = snprintf(we[1], sizeof(we[1]), "whateew");
	if(i < 0)
		return;

	printf("Print Array: \n");
	// print the result of 2d-array
	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 8; j++){
			printf("%c ",we[i][j]);
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

