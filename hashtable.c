/*HashTable implementation*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

#define SIZE 31

typedef struct Node{
	int32_t key;
	int32_t val;
	struct Node *next;
}Node;

Node *hashtable[SIZE];

void initialize(void){
	for(int8_t i=0;i<SIZE;i++)
		hashtable[i]=NULL;
}

int8_t hashcode(int32_t key)
{
	int64_t newcode=pow(2,62)+key;
	return newcode%SIZE;
}

int insert(int32_t key, int32_t val)
{
	Node *tmp=(Node *)malloc(sizeof(Node));//Check memory return
	tmp->key=key;
	tmp->val=val;
	tmp->next=NULL;
	int8_t index=hashcode(key);
	Node *cur=hashtable[index];
	if(cur==NULL)
		hashtable[index]=tmp;
	else{
		while(cur->next!=NULL)
			cur=cur->next;
		cur->next=tmp;
	}
	return 0;
}

int search(int64_t key, int64_t *ptr){
	int8_t index=hashcode(key);
	Node *cur=hashtable[index];
	while(cur!=NULL)
	{
		if(cur->key==key){
			*ptr=cur->val;
			return 1;
		}
		else
			cur=cur->next;
	}
	return 0;
}

int delete(int64_t key, int64_t *val)
{
	int8_t index=hashcode(key);
        Node *cur=hashtable[index];
	if(cur==NULL)
		return 0;
	if(cur->next==NULL && cur->key!=key)
		return 0;
	if(cur->next==NULL && cur->key==key){
		*val=cur->val;
		hashtable[index]=NULL;
		return 1;
	}
	Node *prev=cur;
        while(cur!=NULL)
        {
                if(cur->key==key){
                        *val=cur->val;
                        prev->next=cur->next;
			free(cur);
			return 1;
                }
                else{
			prev=cur;
                        cur=cur->next;
		}
        }
        return 0;
}

void printHashTable(void)
{
	for(int8_t i=0;i<SIZE;i++)
	{
		Node *cur=hashtable[i];
		while(cur!=NULL)
		{
			printf("key:%d val:%d ",cur->key, cur->val); 
			cur=cur->next;
		}
		printf("\n");
	}
}

int main(void)
{
	initialize();
	printf("Before inserting...\n");
	printHashTable();
	insert(6,98);
	insert(7,99);
	insert(8,100);
	printf("After inserting 3 elements...\n");
	printHashTable();
	int64_t val;
	delete(7, &val);
	printf("After deleting key:7 val:%ld element...\n", val);
	printHashTable();
	return 0;
}
