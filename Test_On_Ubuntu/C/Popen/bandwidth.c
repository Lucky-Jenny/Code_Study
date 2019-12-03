#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
  char cmd[20];
  char line[15];
  long getvalue=0;
  printf("Origin_getvalue=%ld\n",getvalue);
  
  sprintf(cmd,"echo 100000000000");	//echo true; echo false
  printf("cmd=%s\n",cmd);
  //cmd=echo "true"

  FILE *f=popen(cmd,"r");  //execute cmd | read the stream
  
  printf("line[]:\n");
  if(f)
  {
     if(fgets(line, sizeof(line), f) != NULL)
     {	
	printf("\nline=%s\n",line);
	getvalue=atol(line);
	printf("getvalue=%ld\n",getvalue);
     }
    printf("\n");
    
    printf("Final_getvalue:\n%ld\n",getvalue);
    pclose(f);
    //return 0;
  }

}

