#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TEST 0

/*
Parentheses Matching: Match {} [] () in right way.

E.g. {}() --> true
	 {[}  --> false
	 [{}] --> true
(EZ)

URL:
https://leetcode-cn.com/problems/valid-parentheses/
*/
bool isValid(char *s)
{
	int i = 0, len = 0, top = 0;
	char *stack = NULL;

	// Check the length. If valid, set len --> number of pairs.
	if(strlen(s) % 2 == 0)
		len = strlen(s) / 2;
	else
		return false;

	stack = (char*)malloc(sizeof(char) * (len+2));

	while(s[i] != '\0'){
		if(s[i] == '(' || s[i] == '[' || s[i] == '{')
			stack[++top] = s[i];
		else{
			if(s[i] == ')'){
				if(stack[top] != '(')
					break;
			}else if(s[i] == ']'){
				if(stack[top] != '[')
					break;
			}else if(s[i] == '}'){
				if(stack[top] != '{')
					break;
			}else{
				break;
			}
			len--;
			top--;
		}
#if TEST
		printf("s[%d]:%c top=%d\tstack--> %s\n", i, s[i], top, stack);
#endif
		i++;
	}
	free(stack);

	if(len == 0)
		return true;
	else
		return false;
}

// Test
struct Check_Object{
	char *str;
	int value;
};
typedef struct Check_Object Check_t;

Check_t vld_list[] = {
	{"()[]{}", 1},
	{"{()}", 1},
	{"()))", 0},
	{")[", 0},
	{"((", 0},
	{"(([]){})", 1},
	{NULL, -1}
};

#define TAB 20
/* Print in Aligned TAB */
print_tab(char *s, char *val)
{
	int need_tab = TAB - strlen(s);

	printf("s: %s", s);
	for(int i = 0; i < need_tab; i++) printf(" ");
	printf("\033[40;32m%s\033[0m ", val);
}

void Test_Vld_Parenthese()
{
	int i = 0, is_vld = 0, need_tab = 0;

	for(i = 0; vld_list[i].str != NULL; i++){
		is_vld = (int)isValid(vld_list[i].str);
		//print
		print_tab(vld_list[i].str, is_vld == 1? "True": "False");

		if(is_vld == vld_list[i].value)
			printf("--> right\n");
		else
			printf("--> wrong\n");
	}

}


/*
n代表生成括号的对数，返回所有可能的、有效的括号组合。

E.g. n = 3
	["((()))", "(()())", "(())()", "()(())", "()()()"]
	 n = 1
	["()"]

(Middle)

URL:
https://leetcode-cn.com/problems/generate-parentheses/
*/

#define SAMPLE 3		// not find the relation of n and len.
#define LEN 128 		// So set in defination.

int *pr_stack;			// stack of pr
int top_x = 0;			// idx of stack
int cb_size = 0;		// number of combinations
int used = 0;			// mark the number of used pr.

int Check_Pr_Stack(int *s, int n)
{
	int i = 1, a = 1, pairs = 1;
	/*
	 pairs: mark parenthese pairs.
		- pairs finally will be 0 if valid.
	 for(): pre-traverse the string to check the pairs.
	*/
	for(i = 1; i < n*2; i++){
		if(i == s[a] && a < n){
			pairs++;
			a++;
		}else{
			if(pairs == 0)
				return 0;
			pairs--;
		}
	}
	return 1;
}

void backtrace_parenthese(char **pr, int idx, int n)
{
	int i = 0, k = 0, len = 2 * n;

	if(used == n){
#if TEST
		printf("pr_stack:");
		for(i = 0; i < n; i++){
			printf("%d ", pr_stack[i]);
		}
		printf("\n");
#endif
		/* Check stack firstly */
		if(!Check_Pr_Stack(pr_stack, n))
			return;
		char *x = (char *)malloc(sizeof(char) * (len + 1));
		for(i = 0; i < len; i++){
			if(i == pr_stack[k]){
				x[i] = '(';
				k++;
			}else{
				x[i] = ')';
			}
		}
		x[i] = '\0';
		pr[cb_size++] = x;
	}else{
		for(i = idx; i < len - 1; i++){
			pr_stack[top_x++] = i;
			used++;
			backtrace_parenthese(pr, i+1, n);
			pr_stack[top_x--] = -1;
			used--;
		}
	}
	
}

char **generateParenthesis(int n, int *returnSize)
{
	char **pr = NULL;
	int len = 0, start = 0;

	if(n > 0)
		len = 2 * n;
	else{
		printf("Invalid Number!");
		return NULL;
	}

	pr = (char **)malloc(sizeof(char*) * LEN);
	pr_stack = (int *)malloc(sizeof(int) * (n+1));
	memset(pr_stack, -1, sizeof(int) * (n+1));
	// fasten the first bit.
	pr_stack[top_x++] = 0;
	used = 1;
	// lets go
	backtrace_parenthese(pr, 1, n);
	*returnSize = cb_size;

	return pr;
}


void Test_Gnrt_Parenthese()
{
	char **x;
	int i = 0, size = 0, n = SAMPLE;

	printf("n = %d\n", n);
	x = generateParenthesis(n, &size);
	//print
	printf("--> [ ");
	for(i = 0; i < size; i++){
		if(i == 0)
			printf("\"\033[40;32m%s\033[0m\" ", x[i]);
		else
			printf(",\"\033[40;32m%s\033[0m\" ", x[i]);
		free(x[i]);
	}
	printf("]\n");
	printf("Size = \033[40;32m%d\033[0m\n", size);

	free(x);
}

/*
给定只包含'('和')'的字符串，找出最长有效（格式正确且连续）括号子串的长度。

E.g. "(()"		--> 2

	 ")()())"	--> 4

(Difficult)

URL:
https://leetcode-cn.com/problems/longest-valid-parentheses/
*/

/*
 Dynamic Programming 动态规划
*/
int longestValidParentheses(char *s)
{
	int result = 0, i = 0, lastPrephsis = 0, top = -1;
	int *dp;

	dp = (int *)malloc(sizeof(int) * strlen(s));
	memset(dp, 0, sizeof(int) * strlen(s));

	/* Mark the longest valid pr length of current index */
	for(i = 0; i < strlen(s); i++){
		if(s[i] == ')'){
			if(i == 0)
				continue;
			if(s[i-1] == '('){
				dp[i] = (i >= 2? dp[i-2]: 0) + 2;
			}else{
				/*
				  dp[i-1] = valid pr-length of [i-1].
				  i - dp[i-1] = index of [i-1] pre-perenthese "(".
					---> (...........)   )
					   i-dp[i-1     i-1  i
				*/
				lastPrephsis = i - dp[i-1];
				if(lastPrephsis > 0 && s[lastPrephsis-1] == '('){
					dp[i] = dp[i-1] +
						(lastPrephsis >= 2? dp[lastPrephsis-2]: 0) + 2;
				}
			}
			result = (dp[i] > result)? dp[i]: result;
		}
	}
	free(dp);

	return result;
}

// Test

Check_t count_list[] = {
	{")(()())", 6},
	{"))", 0},
	{"()))", 2},
	{")(", 0},
	{"(())(", 4},
	{")()())()()(", 4},
	{NULL, -1}
};

void Test_Longest_Pr()
{
	int i = 0, isVld = 0;
	char val[4] = {0};

	for(i = 0; count_list[i].str != NULL; i++){
		snprintf(val, sizeof(val), "%d", count_list[i].value);
		// print
		print_tab(count_list[i].str, val);

		if(longestValidParentheses(count_list[i].str) == count_list[i].value)
			printf("--> right\n");
		else
			printf("--> \033[40;31mwrong\033[0m\n");
	}
}

int main()
{
	printf("\033[40;34m[Judge Valid Parenthese str]\033[0m\n");
	Test_Vld_Parenthese();
	printf("\033[40;34m[Generate Parentheses according to Num]\033[0m\n");
	Test_Gnrt_Parenthese();
	printf("\033[40;34m[Count the length of Longest Valid Parenthese]\033[0m\n");
	Test_Longest_Pr();
}
