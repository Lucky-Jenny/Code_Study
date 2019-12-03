#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct config_hd
{
	int magic;
	int len;
	int crc;
};

int main()
{
	int i;
	char *p;
	struct config_hd *hd;	//struct_pointer must malloc!!!	
	hd=malloc(20*(sizeof(struct config_hd)));
	//if hd
	hd->magic=3998;
	hd->len=5555;
	hd->crc=6666;
	p=(char *)&hd[0];
	printf("p=hd[0]\naddr=%p\np=%d\n\n",p,*p);
	
	
	while(p<(char *)&hd[1])
	{	
		printf("addr=%p , p=%d\n",p,*p);
		p++;
	}
	hd->magic=4;
	p=(char *)&hd[1];
	printf("\np=hd[1]\naddr=%p , p=%d\n",p,*p);
	//free(p);
}


