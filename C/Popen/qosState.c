#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
  char cmd[40];
  char line[8];
  int getvalue=0;
  printf("Origin_getstring=%d\n",getvalue);
  
  sprintf(cmd,"echo \\\"true\\\" | awk -F \\\" '{print $2}'");	//echo true; echo false
					  //record:must have escape symbol
  printf("cmd=%s\n",cmd);
  //cmd=echo "true"

  FILE *f=popen(cmd,"r");  //execute cmd | read the stream
  
  if(f)
  {
     if(fgets(line, sizeof(line), f) != NULL)
     {	
	printf("\nline=%s\n",line);
	if(strncmp(line,"true",4) == 0)
	 getvalue=4; 
	else if(strncmp(line,"false",5) == 0)
	 getvalue=9; 
	else
	{ printf("ERROR!!\n");}
	printf("getvalue=%d\n",getvalue);
     }
    printf("\n");
    
    printf("Final_getvalue:\n%d\n",getvalue);
    pclose(f);
    //return 0;
  }

}

