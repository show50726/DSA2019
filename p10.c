#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define MAXN 50010
#define ll long long

typedef struct pancake{
	int val, pancakeId, count;
	struct node* next;
	int level[110];
}pancake;

typedef struct node{
	int val;
	struct node* next;
}node;

typedef struct bfsNode{
	int index;
	int nowlevel;
	int cost;
}bfsNode;

pancake list[MAXN];
bool visit[MAXN];
bfsNode queue[MAXN*200];
int head = -1, tail = -1;

void push(int id, int level, int cost){
	queue[++tail].index = id;
	queue[tail].nowlevel = level;
	queue[tail].cost = cost;
}

int isEmpty(){
	return (head==tail);
}

void pop(){
	head++;
	if(head==tail){
        head = -1;
        tail = -1;
	}
}

bfsNode getHead(){
	return queue[head+1];
}

bfsNode getTail(){
	return queue[tail];
}

void init(){
	memset(visit, 0, sizeof(visit));
	for(int i = 0; i < MAXN; i++){
		list[i].next = NULL;
		list[i].count = 0;
	}
}

void add(int a, int b){
	node *now = list[a].next;
	if(now==NULL){
		list[a].next = (node *)malloc(sizeof(node));
		list[a].next->val = b;
		list[a].next->next = NULL;
	}
	else{
		while(now->next!=NULL){
			now = now->next;
		}
		now->next = (node *)malloc(sizeof(node));
		now->next->val = b;
		now->next->next = NULL;
	}
}

int bfs(int v, int l){
	int nlv = 1, ans = 2147483647;
	memset(queue, 0, sizeof(queue));
	memset(visit, 0, sizeof(visit));

	for(int i = 0; i < v; i++){
		memset(list[i].level, 0, sizeof(list[i].level));
	}

	push(0, 1, 0);
	list[0].level[nlv] = 1;


	while(!isEmpty()){
		bfsNode i = getHead();
		//printf("%d %d %d %d\n", i.index, i.type, i.nowlevel, i.cost);
		if(i.nowlevel==l){
            ans = ((ans<i.cost)?ans:i.cost);
            pop();
            continue;
		}
		pop();

		pancake nowinfo = list[i.index];
		node *now = list[i.index].next;
		while(now!=NULL){
            //puts("ok");
            //printf("%d\n", now->val);
			if(list[now->val].level[i.nowlevel]==0){
                    //puts("ok");
                    //printf("for 1: %d %d\n", list[now->val].pancakeId, nowinfo.pancakeId);
				if(list[now->val].count==0){
					push(now->val, i.nowlevel, i.cost+1);
                    list[now->val].level[i.nowlevel] = 1;
                    //printf("push %d\n", now->val);
				}
				if(list[now->val].count==1&&list[now->val].pancakeId==i.nowlevel){
					push(now->val, i.nowlevel, i.cost+1);
					list[now->val].level[i.nowlevel] = 1;
					push(now->val, i.nowlevel+1, i.cost+2);
					list[now->val].level[i.nowlevel+1] = 1;
					//printf("push %d\n", now->val);
				}
			}
			//list[i.index].level[i.nowlevel] = 1;
			now = now->next;
		}
	}
	return ans==2147483647?-1:ans;
}



int main(){
	int v, e, l, g;
	scanf("%d%d%d%d", &v, &e, &l, &g);

	for(int i = 0; i < g; i++){
		int a, b;
		scanf("%d%d", &a, &b);

		if(list[a].count!=0&&list[a].pancakeId==b){}
		else{
            ++list[a].count;
            list[a].pancakeId = b;
		}
	}

	for(int i = 0; i < e; i++){
		int a, b;
		scanf("%d%d", &a, &b);
		add(a, b);
		add(b, a);
	}

	int ans = bfs(v, l);
	printf("%d\n", ans);

	return 0;
}
