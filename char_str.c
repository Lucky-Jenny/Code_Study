#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

//The file tests fuction popen,fgets,sprintf. 
//The result——>Only chars turned into intergers can be printed.(Why??)

int main()
{
   char cmd[100];
   char line[20];
   char *getstring[20];
   printf("Origin_getstring=%s\n",getstring[0]);
   char strcmd[100] = "echo 'dhwuehgrf';echo '23y72y32';echo '3u848234'"; 
   sprintf(cmd,strcmd);    //put "ls -l" into cmd
   printf("cmd=%s\n",cmd);
   //cmd=ls -l
   FILE *f=popen(cmd,"r");  //execute cmd | read the stream
   //printf("f:\n%s\n",&f);
   printf("line[]:\n");
   if(f)
   {
     for( int i=0; fgets(line, sizeof(line),f)!=NULL; i++)
     {
         printf("-------\ni=%d\nline=%s\n",i,line);
	 getstring[i]=(char *)malloc(sizeof(char)*30);
         strcpy(getstring[i],line);	//You must use strcpy() for char
         printf("getstring[%d]=%s\n",i,getstring[i]);
     }
     printf("\n");
     for(int j; j<4; j++)
     {
	printf("Fianl_getstring[%d]:%s\n",j,getstring[j]);
     }
     pclose(f);
     //return 0;
  }

}
