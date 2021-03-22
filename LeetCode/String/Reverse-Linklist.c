#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST 1
#define LEN 10
/* 
  whether has head node.
  To test in convenience, set 0.
*/
#define HEAD_NODE 0

struct ListNode{
	int val;
	struct ListNode *next;
};
typedef struct ListNode LNode;
typedef struct ListNode *slink;

LNode *Create_LNode();				// Initial List
void Print_LNode(LNode *L); 		// Travel List
void Free_LNode(LNode *L);			// Empty List

/*
反转一个单链表。

E.g.
1. 1->2->3->4->5->6->NULL
	6->5->4->3->2->1->NULL

[URL]
https://leetcode-cn.com/problems/reverse-linked-list/
*/

LNode *reverseList(LNode *head)
{
	if(head == NULL || head->next == NULL)
		return head;

	LNode *L = reverseList(head->next);
	head->next->next = head;
	head->next = NULL;

	return L;
}

void Test_Reverse_all()
{
	LNode *A, *reverse_all;

	A = Create_LNode();
	Print_LNode(A);

	reverse_all = reverseList(A);
	printf("\033[40;32m");
	Print_LNode(reverse_all);
	printf("\033[0m");

	Free_LNode(reverse_all);
	/* No need to free(A) because reverse change it. */
}


/*
反转从位置 m 到 n 的链表。请使用一趟扫描完成反转。

E.g.
1. 1->2->3->4->5->6->NULL  m = 2  n = 5
	1->5->4->3->2->6->NULL

[URL]
https://leetcode-cn.com/problems/reverse-linked-list-ii/
*/
int end = 0;
int start = 0;
LNode *tail;

LNode *reversePart(LNode *head, int idx)
{
	if(idx == end){
		tail = head->next;
		return head;
	}
	LNode *L = reversePart(head->next, idx+1);
	head->next->next = head;
	if(idx == start)
		head->next = tail;

	return L;
}

LNode *reverseBetween(LNode *head, int left, int right)
{
	int i = 1;
	LNode *L = head;

	start = left;
	end = right;
	/* If start from the head,  */
	if(left == 1){
		L = reversePart(head, 1);
	}else{
		LNode *pre;

		for(i = 1; i < left; i++){
			pre = head;
			head = head->next;
		}
		pre->next = reversePart(head, i);
	}
	return L;
}

void Test_Reverse_part()
{
	LNode *A, *reverse_part;

	A = Create_LNode();
	Print_LNode(A);

	reverse_part = reverseBetween(A, 5, 10);
	// color
	printf("\033[40;32m");
	Print_LNode(reverse_part);
	printf("\033[0m");

	Free_LNode(reverse_part);
}

int main()
{
	Test_Reverse_all();
	Test_Reverse_part();
}

/* ----------------------------- */

void Print_LNode(LNode *L)
{
	LNode *p;

	if(L == NULL)
		return;
#if HEAD_NODE
	p = L->next;
	printf("[Head]->");
#else
	p = L;
#endif
	while(p != NULL){
		printf("%d->", p->val);
		p = p->next;
	}
	printf("NULL\n");
}

LNode *Create_LNode()
{
	LNode *L, *p, *s = NULL;

	L = (LNode *)malloc(sizeof(LNode));
	p = L;
	for(int i = 1; i <= LEN; i++){
#if HEAD_NODE
		/* s is ready for this round */
		s = (LNode *)malloc(sizeof(LNode));
		s->val = i;
		s->next = NULL;
#else
		/* s is ready for next round */
		p->val = i;
		if(i == LEN)
			s = NULL;
		else
			s = (LNode *)malloc(sizeof(LNode));
#endif
		p->next = s;
		p = s;
	}

	return L;
}

void Free_LNode(LNode *L)
{
	LNode *p = L;

	while(p != NULL){
		LNode *q = p;
		p = p->next;
		free(q);
	}
}

