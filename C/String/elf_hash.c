#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int uint32;
//This is ELF_hash, which translate string to a Hash_Address.
static uint32 name_hash(char *name)
{
	uint32 h=0,g;
	while(*name){
		h= (h<<4) + *name++;
		if((g = (h & 0xf0000000)))
			h ^= g>>24;
		h &= ~g;
	}
	return h & (255);
}
//print integer in format of binary.
void Binary_printf(uint32 t)
{
	if(t) 	{ Binary_printf(t/2); }
	else	{ return; }
	printf("%d",t%2);
}

int main()
{
	char *p;
	p = malloc(200);
	uint32 x;
	int j=0;
	int i= sprintf(p,"iam=lx");
	printf("string:\niam=lx\n");
	while(j<i){
		x= *p++;
		Binary_printf(x);
		j++;
	}
	p -= i;
	printf("\n\nAfter hash:\n");	
	x = name_hash(p);
	Binary_printf(x);
	printf("\n");

}


