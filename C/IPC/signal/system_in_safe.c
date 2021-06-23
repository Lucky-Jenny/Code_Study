#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_ARG 20
#define W_NORMAL 0
#define W_STDERR 1
#define W_APPEND 2

/*
 Description
 - output: Redirect the ouput to specified file. (If NULL, default to console)
 - method: The way to redirect the output
	* W_NORMAL: log > file
	* W_STDERR: log > file 2>&1
	* W_APPEND: log >> file
 - cmdpath: Absolute path of cmd.
 - ...: the arguments of behind the cmd. Must end with "NULL"

Exp:
	1. 
*/
int safe_system(const char *output, unsigned char method, const char *cmdpath, ...)
{
	int fd = 0, appd = 0, wait_val = 0;
	pid_t pid;

	if((pid = vfork()) < 0){
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		signal(SIGCHLD, SIG_DFL);
		return -1;
	}
	if(pid == 0){
		va_list args;
		char *argv[MAX_ARG] = {0};
		char *p = NULL;

		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		signal(SIGCHLD, SIG_DFL);

		argv[0] = (char *)cmdpath;

		va_start(args, cmdpath);
		for(int i = 1;;){
			p = va_arg(args, char *);
			if(p == NULL || i > MAX_ARG){
				if(i > MAX_ARG)
					printf("The length of arguments is beyond limination.\n");
				break;
			}
			argv[i++] = p;
		}
		va_end(args);

		if(output){
			if(!(method & W_APPEND))
				unlink(output);

			appd = (method & W_APPEND) ? W_APPEND : 0;
			if((fd = open(output, O_WRONLY | O_CREAT | appd, 0666)) < 0){
				printf("Can't open %s [Errno]:%s\n", output, strerror(errno));
				_exit(127);
			}
			/*
			 Set file fd to ENV STD value:
				- STDIN_FILENO   0   Standard input
				- STDOUT_FILENO  1   Standard output
				- STDERR_FILENO  2   Standard Error output
			*/
			if(method & W_STDERR)
				/* dup2(A,B) --> Set B to the same file with A. */
				dup2(fd, STDERR_FILENO);
			else
				dup2(fd, STDOUT_FILENO);
			close(fd);
		}

		execve(cmdpath, argv, __environ);
		_exit(127);
	}
	/* Signals for vfork. */
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);

	if(wait4(pid, &wait_val, 0, 0) == -1)
		wait_val = -1;

	return wait_val;
}

void Test_safe_system()
{
	int x = 0;

	/* Correct example */
	x = safe_system("TST", W_NORMAL, "/bin/ls", "-l", ".", NULL);
	printf("return %s\n", strerror(x));

	/* Wrong trying */
	x = safe_system("TST", W_APPEND, "/ls", "-l", "l", NULL);
	printf("return %s\n", strerror(x));

}


int main()
{
	Test_safe_system();
	return 0;
}

