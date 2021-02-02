/*
Char replacement practice: turn IP addr to invalid string.
E.g. 192.168.23.45
---> 192[.]168[.]23[.]45
(EZ)
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * defangIPaddr(char * address){
    char *p = address;
	char *buffer = (char *)malloc(strlen((address)+7)*sizeof(char));
	char *q = buffer;

    while(*p != '\0'){
        if(*p == '.'){
            *q++ = '[';
            *q++ = '.';
            *q++ = ']';
        }else{
            *q++ = *p;
        }
        p++;
    }
	*q = '\0';		// must add '\0' at the end!!
    return buffer;
}

int main()
{
	char IP[] = "192.168.34.200";
	char *invld_ip = NULL;

	invld_ip = defangIPaddr(IP);
	printf("%s\n", invld_ip);
}

