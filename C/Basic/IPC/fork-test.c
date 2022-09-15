#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
 

void lx_handler(int signal)
{
	switch(signal){
		case 1:
			printf("Get signal -- [SIGHUP]\n");
			break;
		case 2:
			printf("Get signal -- [SIGINT]\n");
			break;
		case 3:
			printf("Get signal -- [SIGQUIT]\n");
			break;
		default:
			printf("Get other signal -- <%d>\n", signal);
			break;
	}
}

void Test_fork()
{
	pid_t pid;
	/*
	 Once fork() in program, it will do:
	 1) Fork a child prgram.
	 2) Return 2 values in one time: 
		- 0 --> child process.
		- N --> father process.
	 3) Excute both parent and child process.
		[start from the judgement of pid.]
	*/
	pid = fork();
	if(pid  == 0){		// child program
		/*
		 exec() API will replace original codes with new cmd.
		 So After cmd executed, child-process exit.
		*/
		//execl("/usr/bin/head", "head", "-1", "README", NULL);
		/*
		 It is better to use system() than execl().
		 Because system() will fork() a child process for us.
		*/
		sleep(3);
		system("echo child-process send signal\n");
		//kill(0, SIGINT);
		printf("child pid: %d\n", getpid());   // getpid(): this program pid.
	}else { 			// father program
		printf("pid: %d\n", pid);
		//signal(SIGINT, lx_handler);
		signal(SIGKILL, SIG_IGN);
		sleep(60);
		printf("father pid: %d\n", getpid());
	}

	printf("exit fork process...\n");
}


int main(){
	Test_fork();

	return 0;
}

