#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TEST 1

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
	int i = 0, top = 0;
	char *stack = NULL;
	int len = strlen(s);

	// Check the length. If valid, set len --> number of pairs.
	if(len % 2 == 0)
		len /= 2;
	else
		return false;

	stack = (char*)malloc(sizeof(char) * (len+2));

	while(s[i] != '\0'){
		if(s[i] == '(' || s[i] == '[' || s[i] == '{')
			stack[++top] = s[i];
		else{
			if(s[i] == ')'){
				if(stack[top] != '(')
					return false;
			}else if(s[i] == ']'){
				if(stack[top] != '[')
					return false;
			}else if(s[i] == '}'){
				if(stack[top] != '{')
					return false;
			}else{
				return false;
			}
			len--;
			top--;
		}
#if TEST
		printf("s[%d]:%c top=%d\tstack--> %s\n", i, s[i], top, stack);
#endif
		i++;
	}

	if(len == 0)
		return true;
	else
		return false;
}

// Test
struct Check_Object{
	char *sample;
	bool vld;
};
typedef struct Check_Object Check_t;

Check_t check_list[] = {
	{"()[]{}", true},
	{"{()}", true},
	{"()))", false},
	{")[", false},
	{"((", false},
	{"(([]){})", true},
	{NULL, NULL}
};

void Test_Vld_Parenthese()
{
	int i = 0, isVld = 0;

	for(i = 0; check_list[i].sample != NULL; i++){
		printf("s:%s\n", check_list[i].sample);
		if(isValid(check_list[i].sample) == check_list[i].vld)
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

	printf("n=%d\t\n", n);
	x = generateParenthesis(n, &size);
	//print
	printf("Parentheses_str_Size=%d\n[ ", size);
	for(i = 0; i < size; i++){
		if(i == 0)
			printf("\"%s\" ", x[i]);
		else
			printf(",\"%s\" ", x[i]);
		free(x[i]);
	}
	printf("]\n");
	free(x);
}

/*
给定只包含'('和')'的字符串，找出最长有效（格式正确且连续）括号子串的长度。

E.g. "(()"
	--> 2

	 ")()())"
	--> 4

(Difficult)

URL:
https://leetcode-cn.com/problems/longest-valid-parentheses/
*/

#if 0
// My code: works but is not effect
int longestValidParentheses(char *s)
{
	int result = 0, i = 0, j = 0, mark = 0;

	for(i = 0; i < strlen(s); i++){
		if(s[i] == ')')
			continue;

		mark = 1;
		for(j = i+1; j < strlen(s); j++){
			if(s[j] == '(')
				mark++;
			else
				mark--;
#if TEST
			printf("i=%d j=%d mark=%d\ttmp: ", i, j, mark);
			for(int u = i; u <= j; u++)
				printf("%c", s[u]);
			printf("\n");
#endif
			if(mark == 0){
				result = (j-i+1 > result)? j-i+1: result;
			}
		}
	}
	return result;
}
#endif

/*
 Dynamic Programming 动态规划
*/
int longestValidParentheses(char *s)
{
	int result = 0, i = 0, lastPrephsis = 0, top = -1;
	int *dp = (int *)malloc(sizeof(int) * strlen(s));

	/* Mark the longest valid pr length of current index */
	for(i = 0; i < strlen(s); i++){
		if(s[i] == ')'){
			if(i == 0)
				continue;
			if(s[i-1] == '('){
				dp[i] = ((i >= 2)? dp[i-2]: 0) + 2;
			}else{
				/* dp[i-1] = valid length of sub-pr
				   So i - dp[i-1] = last index of current pre-perenthese.
				*/
				lastPrephsis = i - dp[i-1];
				if(lastPrephsis > 0 && s[lastPrephsis-1] == '(')
					dp[i] = dp[i-1] + 
						(lastPrephsis >= 2? dp[lastPrephsis-2]: 0) + 2;
			}
			result = (dp[i] > result)? dp[i]: result;
		}
	}
	return result;
}

// Test
struct Check_Prs{
	char *str;
	int len;
};
typedef struct Check_Prs Check_p;

Check_p check_pr[] = {
	{")(()())", 6},
	{"))", 0},
	{"()))", 2},
	{")(", 0},
	{"(())(", 4},
	{")()())()()(", 4},
	{NULL, 0}
};

void Test_Longest_Pr()
{
	int i = 0, isVld = 0;

	for(i = 0; check_pr[i].str != NULL; i++){
		printf("s:%s\n", check_pr[i].str);
		if(longestValidParentheses(check_pr[i].str) == check_pr[i].len){
			printf("%d --> \033[40;32mright\033[0m\n", check_pr[i].len);
		}else{
			printf("[%d] but return %d", check_pr[i].len, longestValidParentheses(check_pr[i].str));
			printf("--> \033[40;31mwrong\033[0m\n");
		}
	}
}

int main()
{
	//Test_Vld_Parenthese();
	//Test_Gnrt_Parenthese();
	Test_Longest_Pr();
}
