/*
给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合(可任意顺序)。
数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。

   1(!@#)  2(abc)  3(def)
   4(ghi)  5(jkl)  6(mno)
   7(pqrs) 8(tuv)  9(wxyz)

E.g."23" ---> ["ad","ae","af","bd","be","bf","cd","ce","cf"]
	"2"  ---> ["a","b","c"]
	""   ---> []

[URL]
https://leetcode-cn.com/problems/letter-combinations-of-a-phone-number/
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define TEST 0
#define USE_MY_CODE 0		// My method is unhandy.

static char phone[8][5] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

#if USE_MY_CODE
char **letterCombinations(char *digits, int returnSize)
{
	char *p = digits, *q = NULL;
	char tmp[2] = {0};
	char **comb = NULL;
	int i = 0, j = 0, n = 0, step = 0, next = 0, head = 0;

	comb = (char **)malloc(sizeof(char *) * returnSize);
	for(i = 0; i < returnSize; i++){
		comb[i] = (char *)malloc(sizeof(char) * (strlen(digits)+1));
		// initialization should be in char*.
		memset(comb[i], 0, sizeof(char) * (strlen(digits)+1));
	}

	next = returnSize;
	while(*p != '\0'){
		n = *p - '2';	// '3' ==> phone[1] = "def"
		/*
		 next----Location to put next charactor.
			It should be correspond to strlen(phone[n]).
			E.g. 3*3*4=36   (1) 36/3  (2) 12/3  (3) 4/4

		 step----The next series to put the same charactor.
			E.g. (ab)*(cd) ==> put 'a' [ a a _ _ a a _ _ ]
		*/
		step = next;
		next /= strlen(phone[n]);
		for(i = 0; i < returnSize; i++){
			head = i * next;
			if(phone[n][i] == '\0')
				break;
			/* Make sure the step location not overflow */
			while(head < returnSize){
				for(j = head; j < head+next; j++){
					q = comb[j] + strlen(comb[j]);
					*q = phone[n][i];
#if TEST
			printf("comb[%d] %s\n", j, comb[j]);
#endif
				}
				head += step;
			}
		}
		p++;
	}
	return comb;
}
#else
/*
回朔法: 选优搜索法，按选优向前搜索，以达到目的。当达到某处不满足条件，退回一步。
中心思想 ----> DFS
[使用场景]
	1. 排列组合问题;

*/
char *cmb_tmp = NULL;		// Temp store cmb-str. [Important!!!]
int index_tmp = 0;			// Index of tmp.
int digit_size = 0; 		// length of digits
int cmb_size = 0;			// record size of cmb.

void backtrace_phone(char **cmb, int index, char *digits)
{
	int i = 0, n = 0;
#if TEST
	printf("idx_tmp=%d cmb_tmp:%s\n", index_tmp, cmb_tmp);
#endif
	if(index == digit_size){
		char *x = (char *)malloc(sizeof(char) * (digit_size + 1));
		memcpy(x, cmb_tmp, sizeof(char) * (digit_size + 1));
		cmb[cmb_size++] = x;
	}else{
		n = digits[index] - '2';
		for(i = 0; i < strlen(phone[n]); i++){
			cmb_tmp[index_tmp++] = phone[n][i];
			backtrace_phone(cmb, index+1, digits);
			cmb_tmp[index_tmp--] = '\0';
		}
	}
}

char **letterCombinations(char *digits, int *returnSize)
{
	char **cmb;
	int i = 0, len = 1;

	digit_size = strlen(digits);
	if(digit_size == 0)
		return cmb;

	for(i = 0; i < digit_size; i++){
		if(digits[i] == '7' || digits[i] == '9')
			len *= 4;
		else
			len *= 3;
	}
	cmb = (char **)malloc(sizeof(char*) * len);
	cmb_tmp = (char *)malloc(sizeof(char) * (digit_size + 1));

	backtrace_phone(cmb, 0, digits);
	*returnSize = cmb_size;
	return cmb;
}
#endif

void Print_Letters(int num)
{
	char s[8] = {0};
	char **ret;
	int i = 0, size = 1;

	printf("[Num] %d\n", num);
	snprintf(s, sizeof(s), "%d", num);
#if USE_MY_CODE
	for(i = 0; i < strlen(s); i++){
		if(s[i] == '7' || s[i] == '9')
			size *= 4;
		else
			size *= 3;
	}
	ret = letterCombinations(s, size);
#else
	ret = letterCombinations(s, &size);
#endif
	printf("size=%d\n==> [ ", size);
	for(i = 0; i < size; i++){
		printf("%s ", ret[i]);
		free(ret[i]);
	}
	printf("]\n");
	//free
	free(ret);
}

int main()
{
	int n1 = 23;
	int n2 = 49;
	int n3 = 294;
	// sample here
	int x = n2;

	Print_Letters(x);
}


