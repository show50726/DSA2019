#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "pancake_names.h"
#define MM 20000003

#define MAXN 20000003
#define ll long long

int hash[MAXN];
int start[MAXN], end[MAXN];
int sum[MAXN];

int max(int a, int b){
	return a>b?a:b;
}

int calhash(char s[], int l){
	//printf("%s\n", s);
	ll v = 0;
    for(int i = 0; i < l; i++){
        v*=29;
        if(i<strlen(s))
        	v+=(s[i]-96);
    }
    if(v<0) v+=MM;
    //printf("%lld\n", v);
    v%=MAXN;
    return (int)v;
}

int main(){
	memset(hash, 0, sizeof(hash));
	memset(sum, 0, sizeof(sum));
   	InitPancakes();
   	int maxl = -1;

	for(int i = 0; i < M; i++){
		maxl = max(strlen(Q1[i]), maxl);
		maxl = max(strlen(Q2[i]), maxl);
	}
	for(int i = 0; i < N; i++){
		maxl = max(strlen(S[i]), maxl);
	}
	//printf("l: %d\n", maxl);
   	for(int i = 0; i < M; i++){
   		start[i] = calhash(Q1[i], maxl);
   		end[i] = calhash(Q2[i], maxl);
   		//printf("%d %d\n", start[i], end[i]);
   	}

   	for(int i = 0; i < N; i++){
   		int v = calhash(S[i], maxl);
   		//printf("%d\n", v);
   		hash[v]++;
   	}

   	sum[0] = 0;
   	for(int i = 1; i < MAXN; i++){
   		sum[i] = sum[i-1]+hash[i];
   	}

   	for(int i = 0; i < M; i++){
   		int ans = sum[end[i]]-sum[start[i]-1];
   		//printf("%d\n", ans);
   		AnswerArvin(i, ans);
   	}
   	ByeArvin();

	return 0;
}
