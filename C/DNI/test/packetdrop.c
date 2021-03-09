#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
  char cmd[20];
  char line[15];
  int getvalue=3;
  printf("Origin_getvalue=%d\n",getvalue);
  
  sprintf(cmd,"echo 0");	//echo true; echo false
  printf("cmd=%s\n",cmd);
  //cmd=echo "true"

  FILE *f=popen(cmd,"r");  //execute cmd | read the stream
  
  if(f)
  {
     if(fgets(line, sizeof(line), f) == NULL)
     {	
	printf("wrong!");
     }
     getvalue=atoi(line);
     printf("getvalue=%d\n",getvalue);
     
    printf("\n");
    			  //If this is %s, there will be:(null)
    printf("Final_getvalue:%d\n",atoi(line));
    pclose(f);
    //return 0;
  }

}

