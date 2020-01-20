#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

//The file tests on popen,fgets,strncmp

int main()
{
  int i=0;
  char cmd[100];  //Always Remember: char value must use strcpy!!!!
  char line[30];
  char *getvalue[3];
  //getvalue[0]="juerdf";
  //getvalue[1]="23984y";
  printf("Origin_getvalue:\n%s\n%s\n",getvalue[0],getvalue[1]);
  
  sprintf(cmd,"echo 'admin';echo '123456';echo 'third'");
  printf("cmd=%s\n",cmd);

  FILE *f=popen(cmd,"r");  //execute cmd | read the stream
  
  printf("line:\n");
  if(f)
  {
    for( i=0; fgets(line, sizeof(line),f)!=NULL; i++)
    {
	printf("\ni=%d\nline=%s\n",i,line);
	//If strcpy, pointer must have malloc !!!!!!!!!!!!!
	getvalue[i]=(char *)malloc(sizeof(char)*30);
	strcpy(getvalue[i],line);
	printf("finish line\n");
	//getvalue[i]=line;	stirng copy cannot use "="
	for(int j=0;j<3;j++)
	{
	  printf("getvalue[%d]=%s\n",j,getvalue[j]);
	}
    }
    printf("\n");
    pclose(f);
    //return 0;
  }
  printf("Final_getvalue:\n");
  for(i=0;i<3;i++)
  {
    printf("getvalue[%d]=%s\n",i,getvalue[i]);
  }
}

