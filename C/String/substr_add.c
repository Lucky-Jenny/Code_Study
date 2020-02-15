#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *addstr(char str[], char *substr)
{
	int i=0, j=0;
	char p[100];
	char *f, *res;
	// All values should be defined at first, which means "initialization" !!!
	strcpy(p, str);
	f = p;
	while(p[i++]){
		f++;
	}
	strcpy(f, substr);
	j = strlen(substr);
	f[j] = '\0';
	res = p;	// if 'char *res = p;', then printf("%s") will show nothing.
	return res;
}


int main()
{
	char p[] = "Who are you? ";
	char q[] = "My name is LX.";
	printf("%s\n%s\n", p, q);
	// add q to the tail of p.
	printf("=>\n%s\n", addstr(p, q));
}

/* 这里遇到了非常离奇的问题：编译器没有报错，逻辑都正确，但是printf就是打印不出字符串。
   关键：addstr()中若直接'char *res = p;'，则printf中的'%s'获取不到字符串。
   在线网站的C编译器显示的则是乱码，说明变量的初始化时很重要要的！！！
*/

