#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FILENAME "./tmp/dmesg.txt"

char *Get_Cmd_Output()
{
	static char output[256] = {0};
	char temp[128], iwtemp[128], df[64], db[64];
	char *iwp = NULL, *iwq = NULL, *iwm = NULL;
	FILE *fp = NULL;

	if((fp = fopen(FILENAME, "r")) != NULL){
		while(fgets(temp, sizeof(temp), fp) != NULL){
			if(strstr(temp, ":")){
				iwp = strtok(temp, ":");
				iwq = strtok(NULL, ":");
				iwm = iwp;
				while(*iwm != '\t'){
					iwm++;
				}
				while(*iwq != '\0'){
					if(*iwq != '\t')
						break;
					iwq++;
				}
				strncpy(df, iwp, iwm-iwp);
				strcpy(db, iwq);
				sprintf(iwtemp, "%s:%s\n", df, db);
				strcat(output, iwtemp);
				memset(df, 0, sizeof(df));
				memset(db, 0, sizeof(db));
			}

		}
	}
	return output;
}

int main()
{
	char *p = NULL;

	p = Get_Cmd_Output();
	printf("%s\n", p);
}

