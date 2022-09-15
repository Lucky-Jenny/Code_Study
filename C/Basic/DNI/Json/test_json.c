#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "cJSON.h"


cJSON *getJSONcode(char *filename)
{
	FILE *tfp;
	cJSON *root;
	int flen=0;
	char *json_buf;

	root=NULL;
	if((tfp = fopen(filename, "r")) == NULL)
		return NULL;

	fseek(tfp,0L,SEEK_END);
	flen=ftell(tfp);
	json_buf=(char *)malloc(flen+1);
	fseek(tfp,0L,SEEK_SET);
	fread(json_buf,flen,1,tfp);
	json_buf[flen]='\0';
	fclose(tfp);
	root = cJSON_Parse(json_buf);
	return root;
}

char *getobjectvalue(cJSON *object,const char *string)
{
	cJSON *c;
	c=object;

	while(c && strcmp(c->string, string)) {
		if(c->next)
			c = c->next;
		else
			return "";
	}
	return c->valuestring;
}

int getobjectvalueint(cJSON *object, const char *string)
{
	cJSON *c;
	c=object;
	while(c && strcmp(c->string, string)){
		if(c->next)
			c = c->next;
		else
			return 0;
	}
	return c->valueint;
}

char *get_device_Name(char *ipaddr)
{
	int i = 0, num = 0;
	static char name[64] = {0};
	cJSON *dataArray, *Item, *Device, *IP;

	if((dataArray = getJSONcode("A.txt"))!=NULL)
	{
		num = cJSON_GetArraySize(dataArray);
		for(i=0; i<num; i++){
			Item  = cJSON_GetArrayItem(dataArray, i);
			Device  = cJSON_GetArrayItem(Item, 0);
			strcpy(name, getobjectvalue(Device, "name"));

			while(Device->next){
				if(!strcmp(Device->string, "ips")){
					IP = cJSON_GetArrayItem(Device, 0);
					if(!strcmp(IP->valuestring, ipaddr))
						printf("IP[%s]\n", IP->valuestring);
						return name;
				}
				Device = Device->next;
			}
		}
		cJSON_Delete(dataArray);
	}
	return "";
}


int main()
{
	char *name;
	char ipaddr[64] = {0};

	strcpy(ipaddr, "192.168.1.2");
	name = get_device_Name(ipaddr);
	printf("Get Name:%s\n", name);
}

