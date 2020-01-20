#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

//The file tests on popen,fgets,strncmp

int main()
{
  char cmd[20];
  char line[10];
  int getvalue[2]={0};
  printf("Origin_getstring=%d\n",getvalue[0]);
  
  sprintf(cmd,"echo true");	//echo true; echo false
  printf("cmd=%s\n",cmd);
  //cmd=echo "true"

  FILE *f=popen(cmd,"r");  //execute cmd | read the stream
  
  printf("line[]:\n");
  if(f)
  {
    for( int i=0; fgets(line, sizeof(line),f)!=NULL; i++)
    {
	printf("\ni=%d\nline=%s\n",i,line);
	if(strncmp(line,"true",4) == 0)
	{ getvalue[i]=4; }
	else if(strncmp(line,"false",5) == 0)
	{ getvalue[i]=9; }
	else
	{ printf("NULL");}
	printf("getvalue[%d]=%d\n",i,getvalue[i]);
	printf("%d\n",getvalue[0]);
    }
    printf("\n");
    
    printf("Final_getvalue:\n%d\n%d\n",getvalue[0],getvalue[1]);
    pclose(f);
    //return 0;
  }

}

